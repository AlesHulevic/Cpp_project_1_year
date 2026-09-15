////#pragma once


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

class Date
{
private:
	int day = 0, month = 0, year = 0;

	int Define_Month(int month, int year)
	{
		if (month > 12)
		{
			month = month - 12;
			year = year + 1;
		}
		switch (month)
		{
		case 1:
			return 31;
		case 2:
			if (year % 4 == 0)
				return 29;
			else
				return 28;
		case 3:
			return 31;
		case 4:
			return 30;
		case 5:
			return 31;
		case 6:
			return 30;
		case 7:
			return 31;
		case 8:
			return 31;
		case 9:
			return 30;
		case 10:
			return 31;
		case 11:
			return 30;
		case 12:
			return 31;
		default:
			return -1;
		}
	}
public:
	Date()
	{
		this->day = 0;
		this->month = 0;
		this->year = 0;
	}

	Date(string date)
	{
		string saver;
		saver.append(date, 0, 2);
		this->day = stoi(saver);
		saver.clear();
		saver.append(date, 3, 2);
		this->month = stoi(saver);
		saver.clear();
		saver.append(date, 6, 2);
		this->year = stoi(saver);
	}

	void operator =(const Date& other)
	{
		this->day = other.day;
		this->month = other.month;
		this->year = other.year;
	}
	bool operator ==(const Date& other)
	{
		if (this->year != other.year)
			return false;
		if (this->month != other.month)
			return false;
		if (this->day != other.day)
			return false;
		return true;
	}
	bool operator !=(const Date& other)
	{
		if (this->year != other.year)
			return true;
		if (this->month != other.month)
			return true;
		if (this->day != other.day)
			return true;
		return false;
	}
	bool operator < (const Date& other)
	{
		if (this->year < other.year)
			return true;
		if (this->year != other.year)
			return false;
		if (this->month < other.month)
			return true;
		if (this->month != other.month)
			return false;
		if (this->day < other.day)
			return true;
		if (this->day != other.day)
			return false;
		return false;
	}
	bool operator > (const Date& other)
	{
		if (this->year > other.year)
			return true;
		if (this->year != other.year)
			return false;
		if (this->month > other.month)
			return true;
		if (this->month != other.month)
			return false;
		if (this->day > other.day)
			return true;
		if (this->day != other.day)
			return false;
		return false;
	}

	void SetDate(string str)
	{
		int i = 0;
		string sday, smounth, syear;

		for (; str[i] != '.'; i++) sday.push_back(str[i]);
		this->day = stoi(sday);
		i++;
		for (; str[i] != '.'; i++) smounth.push_back(str[i]);
		this->month = stoi(smounth);
		i++;
		for (; str[i] != ' '; i++) syear.push_back(str[i]);
		this->year = stoi(syear);
	}

	int SetDate()
	{
		cout << "увядзіце дзень, месяц і год праз прабел:\n";
		cin >> this->day >> this->month >> this->year;
		cin.clear();
		if (this->month > 12 || this->day > Define_Month(this->month, this->year))
			return -1;
		if (this->month < 1 || this->day < 1)
			return -1;
		return 0;
	}
	string GetDate()
	{
		string date = to_string(this->day) + "." + to_string(this->month) + "." + to_string(this->year);
		return date;
	}

};

class Item
{
private:
	string name = "";
	int coast = 0;
	string dangrous_cl = "";
	int weight = 0;
public:
	virtual void Create_Item()
	{
		cout << "увядзіце найменне: ";
		cin >> this->name;
		while (this->name[0] == '1' || this->name[0] == '2' || this->name[0] == '3' || this->name[0] == '4' || this->name[0] == '5' || this->name[0] == '6' || this->name[0] == '7' || this->name[0] == '8' || this->name[0] == '9' || this->name[0] == '0')
		{
			cout << "першы сімбал не можа быць лічбай";
			cin >> this->name;
		}
		cout << "увядзіце кошт: ";
		this->coast = input_and_check(0, 1000000);
		cout << "увядзіце клас небяспечнасці: ";
		cin >> this->dangrous_cl;
		while (this->dangrous_cl[0] == '1' || this->dangrous_cl[0] == '2' || this->dangrous_cl[0] == '3' || this->dangrous_cl[0] == '4' || this->dangrous_cl[0] == '5' || this->dangrous_cl[0] == '6' || this->dangrous_cl[0] == '7' || this->dangrous_cl[0] == '8' || this->dangrous_cl[0] == '9' || this->dangrous_cl[0] == '0')
		{
			cout << "першы сімбал не можа быць лічбай";
			cin >> this->dangrous_cl;
		}
		cout << "увядзіце вагу: ";
		this->weight = input_and_check(0, 1000000);
	}
	virtual void From_file_to_massiv(string name, int coast, string dangrous_cl, int weight)
	{
		this->name = name;
		this->coast = coast;
		this->dangrous_cl = dangrous_cl;
		this->weight = weight;
	}
	void spr(ofstream& file);
	virtual void show();
	virtual void Save_to_file()
	{
		ofstream file;
		file.open("Sklad.txt", ofstream::app);
		if (!file.is_open()) cout << "памылка";
		file << this->name << " " << this->coast << " " << this->dangrous_cl << " " << this->weight << " ";
		file.close();
	}
	void SetItem(string name, int coast, string dangrous_cl, int weight)
	{
		this->name = name;
		this->coast = coast;
		this->dangrous_cl = dangrous_cl;
		this->weight = weight;
	}
	int Geter_weight()
	{
		return this->weight;
	}
	int Geter_coast()
	{
		return this->coast;
	}
	string Geter_name()
	{
		return this->name;
	}
	string Geter_danger()
	{
		return this->dangrous_cl;
	}
};

class Goods /*: public Item*/
{
private:
	int value = 0;
	Date date;
	Item item;
public:
	virtual void Create_Good()
	{
		system("cls");
		cout << "________________________________________________________________________________________________________________\n";
		cout << "|                                Увод дадзеных новага тавару                                                  |\n";
		cout << "|______________________________________________________________________________________________________________|\n";
		this->item.Create_Item();
		cout << "увядзіце колькасць тавараў: ";
		this->value = input_and_check(0, 1000000);
		this->date.SetDate();
	}
	virtual void From_file_to_massiv(Item item, int value, Date date)
	{
		this->value = value;
		this->item = item;
		this->date = date;
	}
	void spr(ofstream& file);
	virtual void show();
	virtual void Save_to_file()
	{
		ofstream file;
		file.open("Sklad.txt", ofstream::app);
		if (!file.is_open()) cout << "памылка";
		this->item.Save_to_file();
		file << this->value << " " << this->date.GetDate() << " " << endl;
		file.close();
	}
	Date Geter_date()
	{
		return this->date;
	}
	string geter1()
	{
		return this->item.Geter_name();
	}
	int geter2()
	{
		return this->item.Geter_coast();
	}
	int geter3()
	{
		return this->item.Geter_weight();
	}
	int geter4()
	{
		return this->value;
	}
	string geter5()
	{
		return this->item.Geter_danger();
	}
	string geter6()
	{
		return this->date.GetDate();
	}
	virtual void Back()/* = 0*/;
};


template <class T>
class Transaction
{
private:
	std::shared_ptr<T> previous;
	std::shared_ptr<T> current;
public:
	Transaction(T object)
	{
		this->current.reset(new T(object));
		this->previous = NULL;
	}
	void Update(T object)
	{
		this->previous = current;
		this->current.reset(new T(object));
	}
	std::shared_ptr<T> Get_previous_state()
	{
		return this->previous;
	}
	std::shared_ptr<T> Get_current_state()
	{
		return this->current;
	}
	void Go_back()
	{
		this->current.~shared_ptr();
		this->current = this->previous;
	}
	T* Return_current()
	{
		return current.get();
	}
	T* Return_previous()
	{
		return previous.get();
	}
	~Transaction()
	{
		this->current.~shared_ptr();
		this->previous.~shared_ptr();
	}
};


void Show_g(shared_ptr<shared_ptr<Goods>[]>* mas, int size_of_mas);
void delete_g(shared_ptr<shared_ptr<Goods>[]>* mas, int& size_of_mas);

void Find(shared_ptr<shared_ptr<Goods>[]>* mas, int size_of_mas);
void Filt(shared_ptr<shared_ptr<Goods>[]>* mas, int size_of_mas);
void Sort(shared_ptr<shared_ptr<Goods>[]>* mas, int size_of_mas);

