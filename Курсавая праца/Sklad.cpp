#include "Header.h"

void create()
{
	ofstream new_file;
	new_file.open("Sklad.txt");
	if (!new_file.is_open())
		cout << "памылка";
	else cout << "файл створан\n";
	new_file.close();
}

shared_ptr<Goods> From_file_to_massiv(Item item, int value, Date date)
{
	shared_ptr<Goods> goods(new Goods);
	goods->From_file_to_massiv(item, value, date);
	return goods;
}

shared_ptr<Goods> Create_Goods()
{
	shared_ptr<Goods> good(new Goods);
	good->Create_Good();
	return good;
}

void Goods::Back()
{
	char a; int switcher;
	Transaction<Goods> transaction(*this);

	while (true)
	{
		system("cls");
		cout << "________________________________________________________________________________________________________________\n";
		cout << "|                                             Меню рэдагавання                                                 |\n";
		cout << "|1. рэдагаваць                                                                                                +|\n";
		cout << "|2. вярнуць да мінулага стану                                                                                 +|\n";
		cout << "|3. выхад                                                                                                     +|\n";
		cout << "|______________________________________________________________________________________________________________|\n";
		cin.clear();
		switcher = input_and_check(1, 3);
		switch (switcher)
		{
		case 1:
		{
			system("cls");
			cout << "________________________________________________________________________________________________________________\n";
			cout << "|                                Увод дадзеных новага тавару                                                   |\n";
			cout << "|______________________________________________________________________________________________________________|\n";
			this->item.Create_Item();
			cout << "увядзіце колькасць тавараў: ";
			this->value = input_and_check(0, 1000000);
			this->date.SetDate();
			transaction.Update(*this);
			break;
		}
		case 2:
		{
			system("cls");
			if (transaction.Get_previous_state() == transaction.Get_current_state())
			{
				cout << "Адсутнічае ранейшы варыянт аб'екта";
				break;
			}
			transaction.Go_back();
			cout << "Націсніце нешта";
			a = _getch();
			system("cls");
			break;
		}
		case 3:
		{
			(*this) = (*transaction.Return_current());
			return;
		}
		default:
			break;
		}
	}
}

void User_menu()
{
	int switcher = -1;
	int size_of_mas = 0;
	char a;
	shared_ptr<shared_ptr<Goods>[]> mas(new shared_ptr<Goods>[100]);


	ifstream file;
	file.open("Sklad.txt");
	if (!file.is_open())
	{
		cout << "памылка, файл немагчыма прачытаць і працяг працы немагчымы, альбо закрыйце праграму, альбо націсніце нешта, каб стварыць новы файл";
		a = _getch();
		create();
	}

	system("cls");

	while (file)
	{
		string str;

		string name;
		string scoast; int coast;
		string dangerous_cl;
		string sweight; int weight;
		string svalue; int value;
		string sdate;
		Date date;
		Item item;


		getline(file, str);
		if (str == "") break;

		int j = 0;
		for (; str[j] != ' '; j++) name.push_back(str[j]);
		j++;
		for (; str[j] != ' '; j++) scoast.push_back(str[j]);
		j++; coast = stoi(scoast);
		for (; str[j] != ' '; j++) dangerous_cl.push_back(str[j]);
		j++;
		for (; str[j] != ' '; j++) sweight.push_back(str[j]);
		j++; weight = stoi(sweight);
		for (; str[j] != ' '; j++) svalue.push_back(str[j]);
		j++; value = stoi(svalue);
		for (; str[j] != ' '; j++) sdate.push_back(str[j]);
		sdate.push_back(' ');
		date.SetDate(sdate);
		item.SetItem(name, coast, dangerous_cl, weight);
		mas[size_of_mas] = From_file_to_massiv(item, value, date);
		size_of_mas++;
	}
	file.close();


	while (switcher != 0)
	{
		system("cls");
		cout << "________________________________________________________________________________________________________________\n";
		cout << "|                                             Меню карыстальніка                                               |\n";
		cout << "|Заўвага!!! Праца ў меню карыстальніка не змяняе файл-першакрыніцу, усе вашыя \"сартыроўкі\" бачыце выключна вы, |\n";
		cout << "|пасля сканчэння працы ў дадзеным меню, файл не зменіцца.                                                      |\n";
		cout << "|1. сартыроўкі                                                                                                +|\n";
		cout << "|2. праглядзець змесціва складу                                                                               +|\n";
		cout << "|3. пошук                                                                                                     +|\n";
		cout << "|4. прагляд з фільтрам                                                                                        +|\n";
		cout << "|0. выхад                                                                                                     +|\n";
		cout << "|______________________________________________________________________________________________________________|\n";
		cin.clear();
		switcher = input_and_check(0, 4);
		switch (switcher)
		{
		case 1:
		{
			Sort(&mas, size_of_mas);
			break;
		}
		case 2:
		{
			Show_g(&mas, size_of_mas);
			break;
		}
		case 3:
		{
			Find(&mas, size_of_mas);
			break;
		}
		case 4:
		{
			Filt(&mas, size_of_mas);
			break;
		}
		case 6:
		{
		}
		default:
		{break; }
		}
	}
}

void Adm_menu2()
{

	int switcher = -1;
	int size_of_mas = 0;
	char a;
	shared_ptr<shared_ptr<Goods>[]> mas(new shared_ptr<Goods>[100]);


	ifstream file;
	file.open("Sklad.txt");
	if (!file.is_open())
	{
		cout << "памылка, файл немагчыма прачытаць і працяг працы немагчымы, альбо закрыйце праграму, альбо націсніце нешта, каб стварыць новы файл";
		a = _getch();
		create();
	}
	system("cls");

	while (file)
	{
		string str;

		string name;
		string scoast; int coast;
		string dangerous_cl;
		string sweight; int weight;
		string svalue; int value;
		string sdate;
		Date date;
		Item item;


		getline(file, str);
		if (str == "") break;

		int j = 0;
		for (; str[j] != ' '; j++) name.push_back(str[j]);
		j++;
		for (; str[j] != ' '; j++) scoast.push_back(str[j]);
		j++; coast = stoi(scoast);
		for (; str[j] != ' '; j++) dangerous_cl.push_back(str[j]);
		j++;
		for (; str[j] != ' '; j++) sweight.push_back(str[j]);
		j++; weight = stoi(sweight);
		for (; str[j] != ' '; j++) svalue.push_back(str[j]);
		j++; value = stoi(svalue);
		for (; str[j] != ' '; j++) sdate.push_back(str[j]);
		sdate.push_back(' ');
		date.SetDate(sdate);
		item.SetItem(name, coast, dangerous_cl, weight);
		mas[size_of_mas] = From_file_to_massiv(item, value, date);
		size_of_mas++;
	}
	file.close();


	while (switcher != 0 && switcher != 5)
	{
		system("cls");
		cout << "________________________________________________________________________________________________________________\n";
		cout << "|                                             Меню адміністратара 2                                            |\n";
		cout << "|1. дадаць прадукцыю на склад                                                                                 +|\n";
		cout << "|2. праглядзець змесціва складу                                                                               +|\n";
		cout << "|3. адрэдагаваць змесціва складу                                                                              +|\n";
		cout << "|4. прыбраць прадукт са складу                                                                                +|\n";
		cout << "|5. прыбраць усё са складу                                                                                    +|\n";
		cout << "|0. выхад  (захоўвае змены, не ігнаруйце яго)                                                                 +|\n";
		cout << "|______________________________________________________________________________________________________________|\n";
		cin.clear();
		switcher = input_and_check(0, 5);
		switch (switcher)
		{
		case 1:
		{
			system("cls");
			cout << "Увядзіце колькасць ствараемых тавараў: ";
			int size;
			cin >> size;
			for (int i = 0; i < size; i++)
			{

				mas[size_of_mas] = Create_Goods();
				size_of_mas++;
			}
			break;
		}
		case 2:
		{
			Show_g(&mas, size_of_mas);
			break;
		}
		case 3:
		{
			system("cls");
			Show_g(&mas, size_of_mas);
			cout << "абярыце нумар рэдаруемага элемента";
			int num = input_and_check(1, size_of_mas);
			mas[num - 1]->Back();
			break;
		}
		case 4:
		{
			delete_g(&mas, size_of_mas);
			break;
		}
		case 5:
		{
			ofstream file;
			file.open("Sklad.txt", ofstream::trunc);
			file.close();
			break;
		}
		case 0:
		{
			ofstream file;
			file.open("Sklad.txt", ofstream::trunc);
			file.close();
			ofstream fole;
			fole.open("Add.txt", ofstream::trunc);
			fole.close();
			for (int i = 0; i < size_of_mas; i++)
			{
				mas[i]->Save_to_file();
			}
			break;
		}
		default:
		{break; }
		}
	}
}

void Sort(shared_ptr<shared_ptr<Goods>[]>* mas, int size_of_mas)
{
	int switcher = -1;
	system("cls");
	cout << "________________________________________________________________________________________________________________\n";
	cout << "|                                             Меню cартыроўкі                                                  |\n";
	cout << "|1. па прозвішчу                                                                                               |\n";
	cout << "|2. па даце                                                                                                    |\n";
	cout << "|3. па кошту                                                                                                   |\n";
	cout << "|0. выхад                                                                                                      |\n";
	cout << "|______________________________________________________________________________________________________________|\n";
	cin.clear();
	switcher = input_and_check(0, 3);
	switch (switcher)
	{
	case 1:
	{
		for (int k = 0; k < size_of_mas; k++)
		{
			for (int i = 1; i < size_of_mas - k; i++)
			{
				if ((*mas)[i - 1]->geter1() > (*mas)[i]->geter1())
				{
					(*mas)[100] = (*mas)[i - 1];
					(*mas)[i - 1] = (*mas)[i];
					(*mas)[i] = (*mas)[100];
				}
			}
		}
		break;
	}
	case 2:
	{
		for (int k = 0; k < size_of_mas; k++)
		{
			for (int i = 1; i < size_of_mas - k; i++)
			{
				if ((*mas)[i - 1]->Geter_date() > (*mas)[i]->Geter_date())
				{
					(*mas)[100] = (*mas)[i - 1];
					(*mas)[i - 1] = (*mas)[i];
					(*mas)[i] = (*mas)[100];
				}
			}
		}
		break;
	}
	case 3:
	{
		for (int k = 0; k < size_of_mas; k++)
		{
			for (int i = 1; i < size_of_mas - k; i++)
			{
				if ((*mas)[i - 1]->geter2() > (*mas)[i]->geter2())
				{
					(*mas)[100] = (*mas)[i - 1];
					(*mas)[i - 1] = (*mas)[i];
					(*mas)[i] = (*mas)[100];
				}
			}
		}
		break;
	}
	}
}

void Find(shared_ptr<shared_ptr<Goods>[]>* mas, int size_of_mas)
{
	char a;

	int switcher = -1;
	system("cls");
	cout << "________________________________________________________________________________________________________________\n";
	cout << "|1. пошук па найменню                                                                                          |\n";
	cout << "|2. пошук па кошту                                                                                             |\n";
	cout << "|3. па даце                                                                                                    |\n";
	cout << "|0. выхад                                                                                                      |\n";
	cout << "|______________________________________________________________________________________________________________|\n";
	cin.clear();
	switcher = input_and_check(0, 3);
	system("cls");
	bool sw = 0;


	switch (switcher)
	{
	case 1:
	{
		cout << "тавар з якім найменнем вы шукаеце: ";
		string name;
		cin >> name;
		for (int i = 0; i < size_of_mas; i++)
		{
			if ((*mas)[i]->geter1() == name)
			{
				cout << "________________________________________________________________________________________________________________\n";
				cout << "|        Найменне        |      Кошт      |   Клас небяспечнасці   |     Вага     |   Колькасць   |    Дата    |\n";
				cout << "|________________________|________________|________________________|______________|_______________|____________|\n";
				sw = 1;
				cout << "|  ";
				(*mas)[i]->show();
				cout << "|________________________|________________|________________________|______________|_______________|____________|\n";

				ofstream file;
				file.open("Sprav.txt", ios_base::app);
				if (!file.is_open()) cout << "памылка адкрыцця файла";
				file << "________________________________________________Вынікі пошука___________________________________________________\n";
				file << "|______________________________________________________________________________________________________________|\n";
				file << "|        Найменне        |      Кошт      |   Клас небяспечнасці   |     Вага     |   Колькасць   |    Дата    |\n";
				file << "|________________________|________________|________________________|______________|_______________|____________|\n";
				file << "|" << i + 1 << ".";
				(*mas)[i]->spr(file);
				file << "|________________________|________________|________________________|______________|_______________|____________|\n";
				file.close();
				break;
			}
		}
		break;
	}
	case 2:
	{
		cout << "тавар з якім коштам вы шукаеце: ";
		int coast;
		cin >> coast;
		for (int i = 0; i < size_of_mas; i++)
		{
			if ((*mas)[i]->geter2() == coast)
			{
				cout << "________________________________________________________________________________________________________________\n";
				cout << "|        Найменне        |      Кошт      |   Клас небяспечнасці   |     Вага     |   Колькасць   |    Дата    |\n";
				cout << "|________________________|________________|________________________|______________|_______________|____________|\n";
				sw = 1;
				cout << "|  ";
				(*mas)[i]->show();
				cout << "|________________________|________________|________________________|______________|_______________|____________|\n";

				ofstream file;
				file.open("Sprav.txt", ios_base::app);
				if (!file.is_open()) cout << "памылка адкрыцця файла";
				file << "________________________________________________Вынікі пошука___________________________________________________\n";
				file << "|______________________________________________________________________________________________________________|\n";
				file << "|        Найменне        |      Кошт      |   Клас небяспечнасці   |     Вага     |   Колькасць   |    Дата    |\n";
				file << "|________________________|________________|________________________|______________|_______________|____________|\n";
				file << "|" << i + 1 << ".";
				(*mas)[i]->spr(file);
				file << "|________________________|________________|________________________|______________|_______________|____________|\n";
				file.close();

				break;
			}
		}
		break;
	}
	case 3:
	{
		cout << "тавар з якой датай вы шукаеце (фармат паводле выгляда ДД.ММ.ГГГГ): ";
		string date;
		cin >> date;
		for (int i = 0; i < size_of_mas; i++)
		{
			if ((*mas)[i]->geter6() == date)
			{
				cout << "________________________________________________________________________________________________________________\n";
				cout << "|        Найменне        |      Кошт      |   Клас небяспечнасці   |     Вага     |   Колькасць   |    Дата    |\n";
				cout << "|________________________|________________|________________________|______________|_______________|____________|\n";
				sw = 1;
				cout << "|  ";
				(*mas)[i]->show();
				cout << "|________________________|________________|________________________|______________|_______________|____________|\n";

				ofstream file;
				file.open("Sprav.txt", ios_base::app);
				if (!file.is_open()) cout << "памылка адкрыцця файла";
				file << "________________________________________________Вынікі пошука___________________________________________________\n";
				file << "|______________________________________________________________________________________________________________|\n";
				file << "|        Найменне        |      Кошт      |   Клас небяспечнасці   |     Вага     |   Колькасць   |    Дата    |\n";
				file << "|________________________|________________|________________________|______________|_______________|____________|\n";
				file << "|" << i + 1 << ".";
				(*mas)[i]->spr(file);
				file << "|________________________|________________|________________________|______________|_______________|____________|\n";
				file.close();

				break;
			}
		}
		break;
	}
	}
	if (sw == 0)
	{
		system("cls");
		cout << "пошук наўдалы, элемент адсутнічае";
	}
	cout << "націсніне нешта";
	a = _getch();
}

void Filt(shared_ptr<shared_ptr<Goods>[]>* mas, int size_of_mas)
{
	char a;
	int weight;
	int switcher = -1;
	system("cls");
	cout << "________________________________________________________________________________________________________________\n";
	cout << "|1. толькі наяўныя (колькасць>0)                                                                               |\n";
	cout << "|2. толькі бяспечныя (danerous class==\"бяспечны\")                                                              |\n";
	cout << "|3. па ваге (асабісты ўвод)                                                                                    |\n";
	cout << "|0. выхад                                                                                                      |\n";
	cout << "|______________________________________________________________________________________________________________|\n";
	cin.clear();
	switcher = input_and_check(0, 3);
	if (switcher == 3)
	{
		cout << "тавар з якой вагай вы шукаеце?";
		cin >> weight;
	}

	ofstream file;
	file.open("Sprav.txt", ios_base::app);
	if (!file.is_open()) cout << "памылка адкрыцця файла";
	file << "___________________________________________Вынікі прагляда з фільтрам___________________________________________\n";
	file << "|______________________________________________________________________________________________________________|\n";
	file << "|        Найменне        |      Кошт      |   Клас небяспечнасці   |     Вага     |   Колькасць   |    Дата    |\n";
	file << "|________________________|________________|________________________|______________|_______________|____________|\n";




	system("cls");
	cout << "________________________________________________________________________________________________________________\n";
	cout << "|                                                  Спіс тавараў                                                |\n";
	cout << "|______________________________________________________________________________________________________________|\n";
	cout << "|        Найменне        |      Кошт      |   Клас небяспечнасці   |     Вага     |   Колькасць   |    Дата    |\n";
	cout << "|________________________|________________|________________________|______________|_______________|____________|\n";
	int n = 0;
	switch (switcher)
	{
	case 1:
	{
		for (int i = 0; i < size_of_mas; i++)
		{
			if ((*mas)[i]->geter4() > 0)
			{
				n++;
				cout << "|" << i + 1 << ".";
				(*mas)[i]->show();
				cout << "|________________________|________________|________________________|______________|_______________|____________|\n";
				file << "|" << i + 1 << ".";
				(*mas)[i]->spr(file);
				file << "|________________________|________________|________________________|______________|_______________|____________|\n";
			}
		}
		break;
	}
	case 2:
	{
		for (int i = 0; i < size_of_mas; i++)
		{
			if ((*mas)[i]->geter5() == "бяспечны")
			{
				n++;
				cout << "|" << i + 1 << ".";
				(*mas)[i]->show();
				cout << "|________________________|________________|________________________|______________|_______________|____________|\n";
				file << "|" << i + 1 << ".";
				(*mas)[i]->spr(file);
				file << "|________________________|________________|________________________|______________|_______________|____________|\n";
			}
		}
		break;
	}
	case 3:
	{
		for (int i = 0; i < size_of_mas; i++)
		{
			if ((*mas)[i]->geter3() == weight)
			{
				n++;
				cout << "|" << i + 1 << ".";
				(*mas)[i]->show();
				cout << "|________________________|________________|________________________|______________|_______________|____________|\n";
				file << "|" << i + 1 << ".";
				(*mas)[i]->spr(file);
				file << "|________________________|________________|________________________|______________|_______________|____________|\n";
			}
		}
		break;
	}
	}
	if (n == 0)
	{
		cout << "каб паглядзець тавары патрэбныя тавары\n";
		file << "|_________________________________________Пошук_не_завершыўся_паспяхова_________________________________________\n";
	}
	cout << "націсніне нешта";
	a = _getch();

	file.close();
}

void Show_g(shared_ptr<shared_ptr<Goods>[]>* mas, int size_of_mas)
{
	ofstream file;
	file.open("Sprav.txt", ios_base::app);
	if (!file.is_open()) cout << "памылка адкрыцця файла";
	file << "________________________________________________________________________________________________________________\n";
	file << "|______________________________________________________________________________________________________________|\n";
	file << "|        Найменне        |      Кошт      |   Клас небяспечнасці   |     Вага     |   Колькасць   |    Дата    |\n";
	file << "|________________________|________________|________________________|______________|_______________|____________|\n";
	
	for (int i = 0; i < size_of_mas; i++)
	{
		file << "|" << i + 1 << ".";
		(*mas)[i]->spr(file);
		file << "|________________________|________________|________________________|______________|_______________|____________|\n";
	}
	file.close();


	char a;
	system("cls");
	cout << "________________________________________________________________________________________________________________\n";
	cout << "|______________________________________________________________________________________________________________|\n";
	cout << "|        Найменне        |      Кошт      |   Клас небяспечнасці   |     Вага     |   Колькасць   |    Дата    |\n";
	cout << "|________________________|________________|________________________|______________|_______________|____________|\n";
	for (int i = 0; i < size_of_mas; i++)
	{
		cout << "|" << i + 1 << ".";
		(*mas)[i]->show();
		cout << "|________________________|________________|________________________|______________|_______________|____________|\n";
	}
	if (size_of_mas == 0)
		cout << "каб паглядзець тавары патрэбныя тавары\n";
	cout << "націсніне нешта";
	a = _getch();
}


void delete_g(shared_ptr<shared_ptr<Goods>[]>* mas, int& size_of_mas)
{
	Show_g(mas, size_of_mas);
	cout << "\nАбярыце нумар выдаляемага запісу: ";
	int num = input_and_check(1, size_of_mas) - 1;
	int counter;
	for (counter = num; counter < size_of_mas; counter++)
	{
		(*mas)[counter] = (*mas)[counter + 1];
	}
	size_of_mas--;
}

void Goods::spr(ofstream& file)
{
	item.spr(file);
	file << setw(15) << value << "|" << setw(12) << date.GetDate() << "|" << endl;
}

void Item::spr(ofstream& file)
{
	file << setw(22) << name << "|" << setw(16) << coast << "|" << setw(24) << dangrous_cl << "|" << setw(14) << weight << "|";
}


void Goods::show()
{
	item.show();
	cout << setw(15) << value << "|" << setw(12) << date.GetDate() << "|" << endl;
}

void Item::show()
{
	cout << setw(22) << name << "|" << setw(16) << coast << "|" << setw(24) << dangrous_cl << "|" << setw(14) << weight << "|";
}


