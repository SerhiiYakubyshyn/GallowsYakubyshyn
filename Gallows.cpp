#include "pch.h"
#include<iostream>
#include<Windows.h>
#include<string>
#include<time.h>
#include<fstream>
#include<iomanip>
#include<map>
#include<memory>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
class Gallows
{
public:
	Gallows():word(""), count_try(0), count_enter(0), status (true){}
	~Gallows() {}
	void Clear();
	void Save();
	void Read();
	void Give_Random_Word(int level);
	string Get_Word() const;
	vector<string>& Get_All_words();
	vector<char>& Get_Good_Letters();
	vector<char>& Get_Bad_Letters();
	vector<char>& Get_All_Letters();
	int Get_Count_Try() const;
	int Get_Count_Enter() const;
	bool Get_Status() const;
	void Set_Word(string word);
	void Set_All_Words(string word);
	void Set_Good_Letters(char letter);
	void Set_Bad_Letters(char letter);
	void Set_All_Letters(char letter);
	void Set_count_try(int count_try);
	void Set_count_enter(int count_enter);
	void Set_Status(bool status);
	void Find_Letter(char ask_letter);
	void Print_Leters(vector<char> letters);
	void ShowAll();
private:
	void Analysis(char ask_letter, int indexf);
	string word;
	vector<string> all_words;
	vector<char> good_used_letters;
	vector<char> bad_used_letters;
	vector<char> all_letters;
	int count_try;
	int count_enter;
	bool status;
};
class Print_Console_Gallows
{
public:
	Print_Console_Gallows();
	bool Check_Letter(char ask_letter);
	void Ask_Letter();
	void Print_Gallows();
	void Print_Table();
	void Print();
	void Statistic(clock_t timer);
	int MyLevel();
	void Start();
	void Add_new_word();
	void Show();
private:
	Gallows play;
	vector<vector<char>> gallows;
};
int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	Print_Console_Gallows Game;
	string Do;
	while (true) {
		SetConsoleTextAttribute(hStdOut, (WORD)(11));
		cout << "\n(0)Выход\n(1)Новая игра\nВыберите действие-> ";//help команда по редагувані (добавити слово, або показати усі слова)
		cin >> Do;
		if (Do[0] == '0')
			break;
		else if (Do[0] == '1')
			Game.Start();
		else if (Do == "help") {
			cout << "\n(1)Добавить слово\n(2)Показать все слова\nВыберите действие-> ";
			cin >> Do;
			if (Do[0] == '1')
				Game.Add_new_word();
			else if (Do[0] == '2')
				Game.Show();
		}
		else {
			SetConsoleTextAttribute(hStdOut, (WORD)(4));
			cout << "\nОшибка ввода!\n";
		}
	}
	SetConsoleTextAttribute(hStdOut, (WORD)(15));
	cout << endl << endl;
	system("pause");
	return 0;
}
void Gallows::Clear()
{
	this->word = "";
	this->good_used_letters.clear();
	this->bad_used_letters.clear();
	this->all_letters.clear();
	this->all_words.clear();
	this->count_try = 0;
	this->count_enter = 0;
	this->status = true;
}
void Gallows::Save()
{
	string path;
	path = "MyWords.bin";
	fstream fout;
	fout.exceptions(fstream::badbit | fstream::failbit);
	try {
		fout.open(path, fstream::out | fstream::binary | fstream::app);
		cout << "file open.Saving..." << endl;
		for (size_t i = 0; i < all_words.size(); i++)
		{
			size_t len = all_words[i].length() + 1;
			fout.write((char*)&len, sizeof(len));
			fout.write((char*)all_words[i].c_str(), len);
		}
		fout.close();
	}
	catch (const exception& ex) {
		SetConsoleTextAttribute(hStdOut, (WORD)(4));
		cout << ex.what() << endl;
		cout << "Error Save File!";
		SetConsoleTextAttribute(hStdOut, (WORD)(6));
	}
}
void Gallows::Read()
{
	Clear();
	string path;
	path = "MyWords.bin";
	fstream fin;
	fin.exceptions(fstream::badbit | fstream::failbit);
	try {
		fin.open(path, fstream::in | ifstream::binary);
		cout << "Reading file..." << endl;
		while (!fin.eof()) {
			size_t len;
			fin.read((char*)&len, sizeof(len));
			char* buf = new char[len];
			fin.read(buf, len);
			Set_All_Words(buf);
			delete[]buf;
		}
	}
	catch (const exception& ex) {
		SetConsoleTextAttribute(hStdOut, (WORD)(4));
		cout << ex.what() << endl;
		cout << "Error Read File!";
		SetConsoleTextAttribute(hStdOut, (WORD)(6));
	}
	if (fin.is_open()) {
		fin.close();
	}
}
void Gallows::Give_Random_Word(int level)
{
	int my_word;
	bool give_word = false;
	while (!give_word) {
		my_word = rand() % all_words.size();
		word = all_words[my_word];
		if (level == 1 && word.length() <= 4)
			give_word = true;
		else if (level == 2 && (word.length() >= 5 && word.length() <= 7))
			give_word = true;
		else if (level == 3 && word.length() >= 8)
			give_word = true;
	}
}
string Gallows::Get_Word() const
{
	return this->word;
}
vector<string>& Gallows::Get_All_words()
{
	return this->all_words;
}
vector<char>& Gallows::Get_Good_Letters()
{
	return this->good_used_letters;
}
vector<char>& Gallows::Get_Bad_Letters()
{
	return this->bad_used_letters;
}
vector<char>& Gallows::Get_All_Letters()
{
	return this->all_letters;
}
int Gallows::Get_Count_Try() const
{
	return this->count_try;
}
int Gallows::Get_Count_Enter() const
{
	return this->count_enter;
}
bool Gallows::Get_Status() const
{
	return this->status;
}
void Gallows::Set_Word(string word)
{
	this->word = word;
}
void Gallows::Set_All_Words(string word)
{
	this->all_words.push_back(word);
}
void Gallows::Set_Good_Letters(char letter)
{
	this->good_used_letters.push_back(letter);
}
void Gallows::Set_Bad_Letters(char letter)
{
	this->bad_used_letters.push_back(letter);
}
void Gallows::Set_All_Letters(char letter)
{
	this->all_letters.push_back(letter);
}
void Gallows::Set_count_try(int count_try)
{
	this->count_try = count_try;
}
void Gallows::Set_count_enter(int count_enter)
{
	this->count_enter = count_enter;
}
void Gallows::Set_Status(bool status)
{
	this->status = status;
}
void Gallows::Find_Letter(char ask_letter)
{
	int indexf = word.find(ask_letter);
	Analysis(ask_letter, indexf);
}
void Gallows::Print_Leters(vector<char> letters)
{
	for (auto elem : letters) {
		cout << elem << " ";
	}
}
void Gallows::ShowAll()
{
	Read();
	SetConsoleTextAttribute(hStdOut, (WORD)(10));
	cout << endl;
	for (size_t i = 0; i < all_words.size(); i++)
	{
		cout << all_words[i] << endl;
	}
	cout << "Count: " << all_words.size() << endl;
}
void Gallows::Analysis(char ask_letter, int indexf)
{
	if (indexf >= 0) {
		int count_letters = 0;
		this->good_used_letters.push_back(ask_letter);
		for (int i = 0; i < word.length(); i++) {
			for (int j = 0; j < good_used_letters.size(); j++) {
				if (word[i] == this->good_used_letters[j])
					count_letters++;
			}
		}
		if (count_letters == this->word.length())
			this->status = false;
	}
	else {
		this->bad_used_letters.push_back(ask_letter);
		this->count_try++;
		if (count_try == 6)
			this->status = false;
	}
}
Print_Console_Gallows::Print_Console_Gallows()
{
	vector<vector<char>> newgallows(10);
	gallows = newgallows;
	for (int i = 0; i < 10; i++) {
		gallows[i].resize(10, i);
		for (int j = 0; j < 10; j++) {
			if (i == 9 || j == 2 || (i == 0 && (j > 1 && j < 7)))
				gallows[i][j] = '#';
			else if ((i == 1 && j == 6) || (i == 2 && j == 6))
				gallows[i][j] = '|';
			else if (i == 3 && j == 6)
				gallows[i][j] = 'O';
			else if ((i == 4 && j == 6) || (i == 5 && j == 6))
				gallows[i][j] = '|';
			else if ((i == 6 && j == 5) || (i == 4 && j == 5))
				gallows[i][j] = '/';
			else if ((i == 6 && j == 7) || (i == 4 && j == 7))
				gallows[i][j] = '\\';
			else
				gallows[i][j] = ' ';
		}
	}
}
bool Print_Console_Gallows::Check_Letter(char ask_letter)
{
	for (auto elem : play.Get_Bad_Letters()) {
		if (ask_letter == elem)
			return false;
	}
	for (auto elem : play.Get_Good_Letters()) {
		if (ask_letter == elem)
			return false;
	}
	return true;
}
void Print_Console_Gallows::Ask_Letter()
{
	SetConsoleTextAttribute(hStdOut, (WORD)(11));
	string ask_letter;
	cout << "\nВведите букву-> ";
	SetConsoleCP(1251);
	cin >> ask_letter;
	SetConsoleCP(866);
	system("CLS");
	if (ask_letter == "cheat") {//cheat код на показ слова
		SetConsoleTextAttribute(hStdOut, (WORD)(10));
		cout << play.Get_Word();
	}
	else {
		if (Check_Letter(ask_letter[0])) {
			play.Set_count_enter(play.Get_Count_Enter() + 1);
			play.Find_Letter(ask_letter[0]);
			play.Set_All_Letters(ask_letter[0]);
		}
		else {
			SetConsoleTextAttribute(hStdOut, (WORD)(12));
			cout << "Вы уже вводили букву " << ask_letter[0];
			SetConsoleTextAttribute(hStdOut, (WORD)(11));
		}
	}
}
void Print_Console_Gallows::Print_Gallows()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if ((play.Get_Count_Try() < 1) && (((i == 1 && j == 6) || (i == 2 && j == 6)) || (i == 3 && j == 6)))
				cout << " ";
			else if ((play.Get_Count_Try() < 2) && ((i == 4 && j == 6) || (i == 5 && j == 6)))
				cout << " ";
			else if ((play.Get_Count_Try() < 3) && (i == 4 && j == 5))
				cout << " ";
			else if ((play.Get_Count_Try() < 4) && (i == 4 && j == 7))
				cout << " ";
			else if ((play.Get_Count_Try() < 5) && (i == 6 && j == 5))
				cout << " ";
			else if ((play.Get_Count_Try() < 6) && (i == 6 && j == 7))
				cout << " ";
			else
				cout << gallows[i][j];
		}
		cout << endl;
	}
}
void Print_Console_Gallows::Print_Table()
{
	for (int i = 0, j = 0; i < play.Get_Word().length(); i++) {
		cout << " | ";
		for (int j = 0; j < play.Get_Good_Letters().size(); j++) {
			if (play.Get_Word()[i] == play.Get_Good_Letters()[j])
				cout << play.Get_Word()[i];
		}
	}
	cout << " |\n";
}
void Print_Console_Gallows::Print()
{
	cout << endl;
	SetConsoleTextAttribute(hStdOut, (WORD)(6));
	Print_Gallows();
	SetConsoleTextAttribute(hStdOut, (WORD)(14));
	cout << endl;
	Print_Table();
	cout << "\nНеправильные буквы: ";
	play.Print_Leters(play.Get_Bad_Letters());
}
void Print_Console_Gallows::Statistic(clock_t timer)
{
	if (play.Get_Count_Try() < 6) {
		SetConsoleTextAttribute(hStdOut, (WORD)(2));
		cout << "\nВы выиграли!";
	}
	else {
		SetConsoleTextAttribute(hStdOut, (WORD)(4));
		cout << "\nВы проиграли!";
	}
	cout << "\nВремя игры: " << (float)timer / 1000 << " секунд";
	cout << "\nКоличество попиток: " << play.Get_Count_Enter();
	cout << "\nКоличество неправильных попиток: " << play.Get_Count_Try();
	cout << "\nЗагаданое слово: " << play.Get_Word();
	cout << "\nБуквы игрока: ";
	play.Print_Leters(play.Get_All_Letters());
}
int Print_Console_Gallows::MyLevel()
{
	string level;
	system("CLS");
	while (true) {
		SetConsoleTextAttribute(hStdOut, (WORD)(11));
		cout << "\n(1) 1-й уровень, до 4 букв\n(2) 2-й уровень, от 5-ти до 7-ми букв\n(3) 3-й уровень, больше 7-ми букв\nВыберите уровень игры-> ";
		cin >> level;
		if (level[0] == '1')
			return 1;
		else if (level[0] == '2')
			return 2;
		else if (level[0] == '3')
			return 3;
		else {
			SetConsoleTextAttribute(hStdOut, (WORD)(4));
			cout << "Не верный ввод!";
		}
	}
}
void Print_Console_Gallows::Start()
{
	play.Read();
	play.Give_Random_Word(MyLevel());
	system("CLS");
	Print();
	clock_t timer;
	timer = clock();
	while (play.Get_Status()) {
		Ask_Letter();
		Print();
	}
	timer = clock() - timer;
	Statistic(timer);
	cout << endl;
	play.Clear();
}
void Print_Console_Gallows::Add_new_word()
{
	SetConsoleTextAttribute(hStdOut, (WORD)(9));
	string NewWord;
	cout << "\nВведите слово которое хотите добавить-> ";
	SetConsoleCP(1251);
	cin >> NewWord;
	SetConsoleCP(866);
	play.Set_All_Words(NewWord);
	play.Save();
}
void Print_Console_Gallows::Show()
{
	play.ShowAll();
}