//#pragma once


#include <iostream>
#include <fstream>
#include <Windows.h>
#include <memory>
#include <conio.h>
#include <string>
#include <iomanip>

using namespace std;

int input_and_check(int a, int b);
void authorisation();
void Adm_menu1();
void Adm_menu2();
void User_menu();

class User
{
protected:
	string login = "";
	string password = "";
	bool role = 0;
public:
	User() {};
	User(string login, string password, bool role)
	{
		this->login = login;
		this->password = password;
		this->role = role;
	}

	virtual void show();
	virtual void From_file_to_massiv(string log, string pas, bool role)
	{
		this->login = log;
		this->password = pas;
		this->role = role;
	}

	virtual void Set_User()
	{
		system("cls");
		cout << "________________________________________________________________________________________________________________\n";
		cout << "|                                Увод дадзеных новага карыстальніка                                            |\n";
		cout << "|______________________________________________________________________________________________________________|\n";
		cout << "увядзіце лагін: ";
		cin >> this->login;
		while (this->login[0] == '1' || this->login[0] == '2' || this->login[0] == '3' || this->login[0] == '4' || this->login[0] == '5' || this->login[0] == '6' || this->login[0] == '7' || this->login[0] == '8' || this->login[0] == '9' || this->login[0] == '0')
		{
			cout << "першы сімбал не можа быць лічбай";
			cin >> this->login;
		}
		cout << "увядзіце пароль: ";
		cin >> this->password;
	}

	virtual void Save_to_file()
	{
		ofstream file;
		file.open("UserFile.txt", ofstream::app);
		if (!file.is_open()) cout << "памылка";
		for (int i = 0; this->password[i] != '\0'; i++) { this->password[i] = this->password[i] + 3; }
		file <<"Лагін: " << this->login << ", Пароль: "  << this->password << ", Роля: ";
		if(role==1) file << "адміністратар;" << endl;
		else file << "карыстальнік;" << endl;
		file.close();
	}
};

class Admin : public User
{
public:
	virtual void Set_User() override
	{
		this->User::Set_User();
		this->role = 1;
	}
};

class Simp : public User
{
public:
	virtual void Set_User() override
	{
		this->User::Set_User();
		this->role = 0;
	}
};

void Show_ac(shared_ptr<shared_ptr<User>[]>* mas, int size_of_mas);
void delete_s(shared_ptr<shared_ptr<User>[]>* mas, int& size_of_mas);
void redact_user(shared_ptr<shared_ptr<User>[]>* mas, int& size_of_mas);


