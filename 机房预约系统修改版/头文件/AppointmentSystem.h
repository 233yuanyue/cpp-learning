#pragma once
#include"Administrator.h"
#include"Student.h"
#include"Teacher.h"
#include"ComputerRoom.h"
#include<vector>
#include<map>
#include<algorithm>
#include<fstream>
#include<list>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::list;
using std::pair;
using std::make_pair;
using std::to_string;
using std::ofstream;
using std::ifstream;

class AppointmentSystem
{
public:
	AppointmentSystem();

	void show_sign_in_menu();
	void exit_system();
	void sign_in(bool);
	static constexpr int STU = 1;
	static constexpr int TEA = 2;
	static constexpr int SANDT = 3;
	static constexpr int ADM = 0;
	static constexpr int NONAPP = 0;
	static constexpr int NOTPASS = 1;
	static constexpr int CANCEL = 2;
	static constexpr int PASS = 3;
	static constexpr int APPING = 4;

protected:
	bool init();
	void loadUInfo();
	void saveUInfo(int);
	int creatAccount(bool);
	void add_stuAccount(int, string);
	void add_teaAccount(int, string);
	bool is_exist(int, bool);
	void add_account(bool);
	void find_account(int);
	int put_tea_app(int, int, int, int);
	void put_stu_app(int, int, int, int, int, int);
	void show_app(int);
	void clearAppInfo();
	void remove_record(int, int);
	pair<int, Student> is_right_stu(int, string);
	pair<int, Teacher> is_right_tea(int, string);
	void load_stuRecord();
	void save_stuRecord();
	void clear_stuRecord();
	void loadApp(int);
	void saveApp(int);
	void clearApp();
	void showUser(int, int, int);
	void show_userPart(int, int);
	void examine_stuRec();
	Student show_stu(int);
	void examine_stuRec(int,bool);
	void admPart();
	void teaPart(pair<int, Teacher>);
	void stuPart(pair<int, Student>);

private:
	int t_id;
	int s_id;
	map<int,Student> stuInfo;
	map<int,Teacher> teaInfo;
	Administrator admInfo;
	ComputerRoom computerRoom;
	list<pair<int, int> > stu_record;
	vector<pair<int, int> > tea_app;
	vector<pair<int, int> > stu_app;
};
