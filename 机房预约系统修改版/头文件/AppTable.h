#pragma once
#include<string>
#include<cmath>
using std::string;
#include"ComputerRoom.h"

class AppTable
{
public:
	AppTable() :app_time(0), app_state(0) {};

	int set_appInfo(int, int, int, int, int);
	int show_appInfo();
	int show_state();
	void show_appInfo(int);//1_学生 2_老师 3_全部
	void set_result(int);
	void add_tea_app(int);
	void add_stu_app(int);
	int show_appResult();

	static constexpr int STU = 1;
	static constexpr int TEA = 2;
	static constexpr int SANDT = 3;

private:
	int app_time;
	int app_state;
};