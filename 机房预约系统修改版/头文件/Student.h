#pragma once
#include"User.h"
#include"AppTable.h"
#include"ComputerRoom.h"

class Student:public User
{
public:
	Student();

	void show_menu();
	void loadInfo(int);
	void saveInfo(int);
	void changePas(string);
	void clear(int);
	void set_state(int);
	int show_state();
	int set_apt(int, int, int, int);
	void change_apt(int, int);
	void show_apt();
	int getAptInfo();
	void change_apt_state(int state);

	static constexpr int NONAPP = 0;//即使类内初始化了，也应该类外重新定义
	static constexpr int APPING = 1;
	static constexpr int APPSUC = 2;

private:
	int app_state;//0——无预约，1——预约审核中，2——预约成功
	int app_record;
	vector<AppTable> apt;
};