#pragma once
#include"User.h"

class Teacher :public User 
{
public:
	Teacher() = default;

	void show_menu();
	void loadInfo(int);
	void saveInfo(int);
	void changePas(string);
	void clear(int);
	void stu_appInfo(int);
	int cancel_app(int);
	void aptRecord(AppTable);
	void show_aptRec();

private:
	vector<AppTable> t_apt;
};