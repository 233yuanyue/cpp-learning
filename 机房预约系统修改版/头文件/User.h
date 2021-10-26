#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"AppTable.h"
#include<fstream>
#include<map>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::stoi;//string to int          //stol    string to long       //stoll
using std::map;
using std::to_string;

class User {
public:
	User() = default;

	virtual void show_menu() = 0;
	virtual void loadInfo(int) = 0;
	virtual void saveInfo(int) = 0;
	virtual void clear(int) = 0;
	virtual void changePas(string) = 0;

	void set_info(int, string);
	int show_id();
	string show_password();
	string show_s_file(int);
	string show_t_file(int);

protected:
	int user_id;
	string user_password;
	static constexpr int _STU = 1;
	static constexpr int _TEA = 2;
	static constexpr int _SANDT = 3;
	static const string SFILE;//string类型不允许像int那样在头文件中初始化
	static const string TFILE;
};