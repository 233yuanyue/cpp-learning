#include"User.h"

constexpr int User::_STU;
constexpr int User::_TEA;
constexpr int User::_SANDT;
const string User::SFILE = "MyApp_s.csv";//初始化
const string User::TFILE = "MyApp_t.csv";

void User::set_info(int id, string password)
{
	this->user_id = id;
	this->user_password = password;
}

int User::show_id()
{
	return this->user_id;
}

string User::show_password()
{
	return this->user_password;
}

string User::show_s_file(int id)
{
	string seed = to_string(id);
	string file_name = seed + SFILE;
	return file_name;
}
string User::show_t_file(int id)
{
	string seed = to_string(id);
	string file_name = seed + TFILE;
	return file_name;
}
