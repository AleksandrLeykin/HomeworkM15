#pragma once

#include "sha1.h"

#include "string.h"

#define SIZE 10
#define LOGINLENGTH 10

class Chat {
    public:
        Chat();
        ~Chat();
        void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
        bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);
        void print();
                        
    private:
        enum enDataStatus {
            free, // свободен
            engaged, //занят
            deleted //удален
        };
        struct AuthData {
            AuthData()
                : login("")
                , pass_sha1_hash(0)
                , status(enDataStatus::free) {}

            ~AuthData() {
                if(pass_sha1_hash != 0 )
                    delete [] pass_sha1_hash;
            }
            AuthData(char _login[LOGINLENGTH], uint* sh1) : status(enDataStatus::engaged) {
                strcpy_s(login, _login);
                pass_sha1_hash = sh1;               
            }

            AuthData& operator = (const AuthData& other) {
                strcpy_s(login, other.login);
                status = other.status;
                if(pass_sha1_hash != 0)
                    delete [] pass_sha1_hash;

                pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];                
                memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);                
                return *this;
            }       

            bool operator == (const AuthData& other) {
                return status == other.status && (status != enDataStatus::engaged ||
                    (!strcmp(login, other.login) && pass_sha1_hash == other.pass_sha1_hash));
            }

            char login[LOGINLENGTH];            
            uint* pass_sha1_hash;  
            // состояние ячейки
            enDataStatus status;
        };

    int hash_func(const char* login, int offset);
    void resize();

    AuthData* data;
    int data_count;
    int mem_size;
};