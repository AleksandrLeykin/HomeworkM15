#include "chat.h"
#include "iostream"
#include "string.h"

Chat::Chat() {
    data_count = 0;
    mem_size = 8;
    data = new AuthData[mem_size];
}
Chat::~Chat()
{
    delete[] data;
}
// регистрация
void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {    
    int index = -1, i = 0;
    // находим место
    for(;  i < mem_size; ++i)
    {
        index = hash_func(_login, i);
        if (data[index].status != enDataStatus::engaged)
            break;
    }
    if (i >= mem_size) //return; 
    resize();

     data[index] = AuthData(_login, sha1(_pass, pass_length));
     data_count++;
}
// вход по логину и паролю
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // Ваш код
    // Нужно вернуть true в случае успешного логина
	 int index = -1, i = 0;
    for(; i < mem_size; ++i) {        
        index = hash_func(_login, i);
        AuthData& ad = data[index];
        if (!strcmp(ad.login, _login)) {
            break;
        }
    }
    if(i >= mem_size) return false;
    
    uint* digest = sha1(_pass, pass_length);
    
    bool cmpHashes = !memcmp(data[index].pass_sha1_hash, digest, SHA1HASHLENGTHBYTES);
    delete[] digest;
    
    return cmpHashes;
}

int Chat::hash_func(const char* login, int offset)
{
    int res = 0, i = 0;
    for (; i < strlen(login); ++i)
        res *= login[i];
    return (res % mem_size + offset * offset) % mem_size;
}

void Chat::resize()
{
    AuthData* saveData = data;
    int oldSize = mem_size;

    // увеличиваем размер в два раза 
    mem_size = mem_size * 2;
    //обнуляем количество элементов
    data_count = 0;
    // выделяем новую память
    data = new AuthData[mem_size];
    int j = 0;
    //переносим данныу в новый мвссив
    for (int i = 0; i < oldSize; ++i) {
        AuthData& current = saveData[i];
       
            if (current.status == enDataStatus::engaged) {
                int index = hash_func(current.login, j);
                if (data[index].status != enDataStatus::engaged) {
                    data[index] = current;
                    data_count++;
                    data[index].status = enDataStatus::engaged;
                }
                else
                {
                    j++;
                    int index = hash_func(current.login, j);
                    data[index] = current;
                    data_count++;
                    data[index].status = enDataStatus::engaged;
                }
            }
    }
}
