#include"Student.h"

constexpr int Student::NONAPP;
constexpr int Student::APPING;
constexpr int Student::APPSUC;

Student::Student() :app_state(NONAPP), app_record(0){}

void Student::show_menu()
{
	cout << "欢迎<" << this->user_id << ">的登录!" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "-                                                                                     -" << endl;
	cout << "-                         *******************************                             -" << endl;
	cout << "-                         **********1、预约机房**********                             -" << endl;
	cout << "-                         **********2、取消预约**********                             -" << endl;
	cout << "-                         **********3、查看预约记录******                             -" << endl;
	cout << "-                         **********4、修改账号密码******                             -" << endl;
	cout << "-                         **********5、注销登录信息******                             -" << endl;
	cout << "-                         *******************************                             -" << endl;
	cout << "-                                                                                     -" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
}

void Student::loadInfo(int uid)
{
	ifstream infile;
	string file_name = this->show_s_file(uid);
	infile.open(file_name, ios::in);

	if (infile.is_open()) {
		string data;
		int index = 0, pos = -1;

		while (infile >> data) {
			while (true) {
				pos = data.find(",", index);

				if (pos == -1) {//找不到返回-1
					break;
				}

				string temp = data.substr(index, pos - index);
				int info = stoi(temp);
				AppTable app;
				app.add_stu_app(info);
				this->apt.push_back(app);
				this->app_record++;
				index = pos + 1;
			}

			if (!this->apt.empty()) {
				int state = this->apt.back().show_state();
				if (state == 3) {
					this->app_state = APPSUC;
				}
				else if (state == 4) {
					this->app_state = APPING;
				}
				else {
					this->app_state = NONAPP;
				}
			}
		}
		infile.close();
	}
}

void Student::saveInfo(int uid)
{
	ofstream outfile;
	string file_name = this->show_s_file(uid);
	outfile.open(file_name, ios::out);
	for (auto vit = this->apt.begin(); vit != this->apt.end();++vit) {
		outfile << vit->show_appInfo() << ",";
	}
	outfile.close();
}

void  Student::changePas(string password)
{
	this->user_password = password;
}

void Student::clear(int uid)
{
	ofstream  outfile;
	string file_name = this->show_s_file(uid);
	outfile.open(file_name, ios::trunc);
	outfile.close();
	this->app_state = NONAPP;
	this->app_record = 0;
	this->apt.clear();
}

void Student::set_state(int state)
{
	this->app_state = state;
}

int Student::show_state()
{
	return this->app_state;
}

int Student::set_apt(int period, int day, int room, int seat)
{
	AppTable apt;
	int info=apt.set_appInfo(period, day, room, seat, 4);
	this->apt.push_back(apt);
	this->app_record++;
	return info;
}

void Student::change_apt(int uid,int state)
{
	this->loadInfo(uid);
	if (!this->apt.empty()) {
		this->apt.back().set_result(state);
		this->saveInfo(uid);
	}
}

void Student::show_apt()
{
	if (this->app_record != 0) {
		for (int i = 0; i < this->app_record; ++i) {
			auto temp=this->apt.at(i);
			temp.show_appInfo(_STU);
		}
	}
	else {
		cout << "无预约记录" << endl;
	}
}

int Student::getAptInfo()
{
	if (this->app_record != 0) {
		return this->apt.back().show_appInfo();
	}
	else {
		return -1;
	}
}

void Student::change_apt_state(int state)
{
	this->apt.back().set_result(state);
}
