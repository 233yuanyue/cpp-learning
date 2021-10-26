#include"Teacher.h"

void Teacher::show_menu()
{
	cout << "欢迎<" << this->show_id() << ">的登录!" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "-                                                                                     -" << endl;
	cout << "-                         ***********************************                         -" << endl;
	cout << "-                         **********1、审核学生预约**********                         -" << endl;
	cout << "-                         **********2、机房使用登记**********                         -" << endl;
	cout << "-                         **********3、取消使用申请**********                         -" << endl;
	cout << "-                         **********4、机房申请记录**********                         -" << endl;
	cout << "-                         **********5、修改账号密码**********                         -" << endl;
	cout << "-                         **********6、注销登录信息**********                         -" << endl;
	cout << "-                         ***********************************                         -" << endl;
	cout << "-                                                                                     -" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
}

void Teacher::loadInfo(int uid)
{
	ifstream infile;
	string file_name = this->show_t_file(uid);
	infile.open(file_name, ios::in);

	if (infile.is_open()) {
		string data;
		int index = 0;
		int pos = -1;

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
				this->t_apt.push_back(app);
				index = pos + 1;
			}
		}
		infile.close();
	}
}

void Teacher::saveInfo(int uid)
{
	ofstream outfile;
	string file_name = this->show_t_file(uid);
	outfile.open(file_name, ios::out);
	for (auto vit = this->t_apt.begin(); vit != this->t_apt.end(); ++vit) {
		outfile << vit->show_appInfo() << ",";
	}
	outfile.close();
}

void Teacher::changePas(string password)
{
	this->user_password = password;
}

void Teacher::clear(int uid)
{
	ofstream outfile;
	string file_name = this->show_t_file(uid);
	outfile.open(file_name, ios::trunc);
	outfile.close();
	this->t_apt.clear();
}

void Teacher::stu_appInfo(int info)
{

}

int Teacher::cancel_app(int uid)
{
	int pos = 0, index = 0, info = -1;
	vector<int> vtemp;

	for (auto vit = this->t_apt.begin(); vit != this->t_apt.end(); ++vit) {
		if (vit->show_state() == 3) {
			cout << pos+1 << "  ";
			vit->show_appInfo(_TEA);
			cout << endl;
			pos++;
			vtemp.push_back(index);
		}
		index++;
	}

	if (pos != 0) {
		int choice;
		cout << "请选择你要取消的申请：" << endl;
		cin >> choice;
		if (choice <= pos) {
			auto apt = this->t_apt.begin() + (*(vtemp.begin() + choice - 1));
			apt->set_result(2);
			info = apt->show_appInfo() / 10000;
			cout << "取消成功" << endl;
			this->saveInfo(uid);
		}
		else {
			cout << "申请不存在！" << endl;
		}
	}
	else {
		cout << "无可取消申请！" << endl;
	}
	return info;
}

void Teacher::aptRecord(AppTable app)
{
	this->t_apt.push_back(app);
}

void Teacher::show_aptRec()
{
	ComputerRoom com;
	if (!this->t_apt.empty()) {
		for (auto vit = this->t_apt.begin(); vit != this->t_apt.end(); ++vit) {
			vit->show_appInfo(_TEA);
		}
	}
	else {
		cout << "暂无申请记录" << endl;
	}
}
