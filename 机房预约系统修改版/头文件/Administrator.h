#pragma once
#include"User.h"

class Administrator :public User
{
public:
	Administrator() = default;

	void show_menu();
	void loadInfo(int) {};
	void saveInfo(int) {};
	void clear(int) {};
	void changePas(string);
};
