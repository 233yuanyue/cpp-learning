#pragma once
#include<string>
#include<iostream>
#include<fstream>

using std::cout;
using std::endl;
using std::string;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::stoi;

class ComputerRoom
{
public:
	ComputerRoom();

	void init(bool);
	bool loadInfo();
	void saveInfo();
	bool loadRInfo(int);
	void saveRInfo(int);
	void clearInfo();
	void room_forTea(int);
	void isFull(int, int, int, int);
	int get_all_rest(int, int, int);
	void show_time_table();
	int show_room_info(int,int);
	int is_app_suf(int, int, int);
	string str_period(int);
	string str_day(int);
	string str_room(int);
	string str_state(int);
	void show_app_result(int, int, int, int);
	void show_app_record(int, int, int, int, int);
	void set_app_result(int, int, int, int,bool);
	int tea_app_room(int, int, int, bool);//0——添加失败    1——添加成功  -1——取消使用

	static constexpr int RNUM1 = 50;//替代#define
	static constexpr int RNUM2 = 50;
	static constexpr int RNUM3 = 50;
	static constexpr int RNUM4 = 100;
	static constexpr int RNUM5 = 100;
	static constexpr int RNUM6 = 200;
	static constexpr int FAIL = 0;
	static constexpr int SUCFUL = 1;
	static constexpr int CANCEL = -1;
	static constexpr int NFULL = 0;
	static constexpr int SFULL = 1;
	static constexpr int TFULL = 2;
	static constexpr bool USED = true;
	static constexpr bool NUSED = false;


private:
	int get_room_rest(int, int);

	bool room1[5][6][RNUM1];
	bool room2[5][6][RNUM2];
	bool room3[5][6][RNUM3];
	bool room4[5][6][RNUM4];
	bool room5[5][6][RNUM5];
	bool room6[5][6][RNUM6];
	int is_full[5][6][6];
};