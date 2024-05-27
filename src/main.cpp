#include <iostream>
#include "chat.h"

int main()
{
	setlocale(LC_ALL, "ru");
	std::cout << "Hello! Привет!" << std::endl;

	Chat chat;
	chat.reg((char*)"Sasha", (char*)"abv12", 5);
	chat.reg((char*)"Masha1", (char*)"abv13", 5);
	chat.reg((char*)"Dasha2", (char*)"abv14", 5);
	chat.reg((char*)"Glasha3", (char*)"abv15", 5);
	chat.print();
	chat.reg((char*)"Stepasha4", (char*)"abv16", 5);
	//chat.print();
	//chat.reg((char*)"Gha5", (char*)"abv17", 5);
	//chat.print();
	chat.reg((char*)"Jasha6", (char*)"abv18", 5);
	//chat.print();
	chat.reg((char*)"Dash7a", (char*)"abv19", 5);
	chat.reg((char*)"Jksha8", (char*)"abv20", 5);
	chat.reg((char*)"TDha9", (char*)"abv21", 5);
	chat.print();
	
	
	return 0;
}