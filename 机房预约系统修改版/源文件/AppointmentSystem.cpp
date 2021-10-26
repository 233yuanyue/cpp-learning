#include"AppointmentSystem.h"

constexpr int AppointmentSystem::STU;
constexpr int AppointmentSystem::TEA;
constexpr int AppointmentSystem::SANDT;
constexpr int AppointmentSystem::ADM;
constexpr int AppointmentSystem::NONAPP;
constexpr int AppointmentSystem::NOTPASS;
constexpr int AppointmentSystem::CANCEL;
constexpr int AppointmentSystem::PASS;
constexpr int AppointmentSystem::APPING;

AppointmentSystem::AppointmentSystem()
{
	if (!this->init()) {
		this->admInfo.set_info(111, "111");
	}
	this->loadUInfo();
	this->load_stuRecord();
	this->loadApp(SANDT);
}

bool AppointmentSystem::init()
{
	ifstream infile;
	infile.open("ADMIN.txt", ios::in);

	if (infile.is_open()) {
		char ch;
		infile >> ch;
		if (infile.eof()) {
			infile.close();
			return false;
		}
		else {
			infile.putback(ch);
		}

		string data;
		int pos = -1;
		while (infile >> data) {
			pos = data.find(",", 0);
			if (pos == -1) {
				return false;
			}
			else {
				string sid = data.substr(0, pos), password = data.substr(pos + 1, data.length() - 1);
				int iid = stoi(sid);
				this->admInfo.set_info(iid, password);
			}
			return true;
		}
	}
	return false;
}



void AppointmentSystem::loadUInfo()
{
	ifstream stu_ifs, tea_ifs;
	this->s_id = 0, this->t_id = 0;
	stu_ifs.open("STUDE.csv", ios::in);
	tea_ifs.open("TEACH.csv", ios::in);

	if (stu_ifs.is_open()) {
		string data;
		while (stu_ifs >> data) {
			int pos = -1, index = 0;
			int id_temp = 0, uid_temp = 0;
			string pas_temp = "";

			for (int i = 0; i < 3; ++i) {
				pos = data.find(",",index);
				string stemp = data.substr(index, pos - index);
				if (i==0) {
					id_temp = stoi(stemp);
				}
				else if (i == 1) {
					uid_temp = stoi(stemp);
				}
				else {
					pas_temp = stemp;
				}
				index = pos + 1;
			}
			this->s_id++;
			Student stu;
			stu.set_info(uid_temp, pas_temp);
			this->stuInfo.insert(make_pair(id_temp, stu));
		}
		stu_ifs.close();
	}

	if (tea_ifs.is_open()) {
		string data;
		while (tea_ifs >> data) {
			int pos = -1, index = 0;
			int id_temp = 0, uid_temp = 0;
			string pas_temp = "";

			for (int i = 0; i < 3; ++i) {
				pos = data.find(",", index);
				string stemp = data.substr(index, pos - index);
				if (i == 0) {
					id_temp = stoi(stemp);
				}
				else if (i == 1) {
					uid_temp = stoi(stemp);
				}
				else {
					pas_temp = stemp;
				}
				index = pos + 1;
			}
			this->t_id++;
			Teacher tea;
			tea.set_info(uid_temp, pas_temp);
			this->teaInfo.insert(make_pair(id_temp, tea));
		}
		tea_ifs.close();
	}
}

void AppointmentSystem::saveUInfo(int choice)
{
	ofstream outfile;
	if (choice == ADM) {
		outfile.open("ADMIN.txt", ios::out);
		outfile << this->admInfo.show_id() << "," << this->admInfo.show_password() << endl;
	}
	else if (choice == STU) {
		outfile.open("STUDE.csv", ios::out);
		for (auto vit = this->stuInfo.begin(); vit != this->stuInfo.end(); ++vit) {
			outfile << vit->first << "," << vit->second.show_id() << "," << vit->second.show_password() << "," << endl;
		}
	}
	else {
		outfile.open("TEACH.csv", ios::out);
		for (auto vit = this->teaInfo.begin(); vit != this->teaInfo.end(); ++vit) {
			outfile << vit->first << "," << vit->second.show_id() << "," << vit->second.show_password() << "," << endl;
		}
	}
	outfile.close();
}

void AppointmentSystem::show_sign_in_menu()
{
	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "-                                                                                      -" << endl;
	cout << "-                         ********************************                             -" << endl;
	cout << "-                         ***********1、学生登录**********                             -" << endl;
	cout << "-                         ***********2、教职工登录********                             -" << endl;
	cout << "-                         ***********0、退出系统**********                             -" << endl;
	cout << "-                         ********************************                             -" << endl;
	cout << "-                                                                                      -" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl;
}

void AppointmentSystem::exit_system()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

int AppointmentSystem::creatAccount(bool stu)
{
	if (stu) {
		this->s_id++;
		return this->s_id;
	}

	this->t_id++;
	return this->t_id;
}

void AppointmentSystem::add_stuAccount(int id, string password)
{
	Student stu;
	stu.set_info(id, password);
	this->stuInfo.insert(make_pair(this->creatAccount(true), stu));
}

void AppointmentSystem::add_teaAccount(int id, string password)
{
	Teacher tea;
	tea.set_info(id, password);
	this->teaInfo.insert(make_pair(this->creatAccount(false), tea));
}

bool AppointmentSystem::is_exist(int id, bool stu)
{
	if (stu) {
		for (auto mit = stuInfo.begin(); mit != stuInfo.end(); ++mit) {
			if (mit->second.show_id()==id) {
				return true;
			}
		}
	}
	else {
		for (auto mit = teaInfo.begin(); mit != teaInfo.end(); ++mit) {
			if (mit->second.show_id() == id) {
				return true;
			}
		}
	}

	return false;
}

void AppointmentSystem::add_account(bool stu)
{
	int id;
	cout << "请输入学号/教职工号：" << endl;
	cin >> id;

	if (is_exist(id, stu)) {
		cout << "该账号已存在！" << endl;
	}
	else {
		string password = to_string(id);

		if (stu) {
			Student s;
			s.set_info(id, password);
			this->stuInfo.insert(make_pair(this->creatAccount(true), s));
		}
		else {
			Teacher t;
			t.set_info(id, password);
			this->teaInfo.insert(make_pair(this->creatAccount(false), t));
		}
		cout << "账户添加成功！" << endl;
	}
}

void AppointmentSystem::find_account(int way)
{
	if (way != TEA) {
		if (this->stuInfo.empty()) {
			cout << "无学生账号信息！" << endl;
		}
		else {
			cout << "学生信息：" << endl;
			for (auto it = stuInfo.begin(); it != stuInfo.end(); ++it) {
				cout << "suid：" << it->first << "\t学号：" << it->second.show_id() << endl;
			}
		}

		if (way == STU) {
			return;
		}
		else {
			cout << endl;
		}
	}

	if (this->teaInfo.empty()) {
		cout << "无教职工账号信息！" << endl;
	}
	else {
		cout << "教职工信息：" << endl;
		for (auto it = teaInfo.begin(); it != teaInfo.end(); ++it) {
			cout << "tuid：" << it->first << "\t职工号：" << it->second.show_id() << endl;
		}
	}
}

void AppointmentSystem::clearAppInfo()
{
	this->computerRoom.clearInfo();
	this->stu_app.clear();
	this->tea_app.clear();
}

void AppointmentSystem::remove_record(int uid, int info)
{
	pair<int, int> p;
	for (auto lit = this->stu_record.begin(); lit != this->stu_record.end(); ++lit) {
		if (lit->first == uid && lit->second == info) {
			p = *lit;
			break;
		}
	}
	this->stu_record.remove(p);
	this->save_stuRecord();
}

void AppointmentSystem::show_app(int way)//1_学生预约信息  2_教师预约信息  3_全部预约信息
{
	if (way != TEA) {
		if (!this->stu_app.empty()) {
			cout << "学生申请信息：" << endl;
			for (auto vit = this->stu_app.begin(); vit != this->stu_app.end(); ++vit) {
				AppTable app;
				app.add_stu_app(vit->second);
				cout << "uid:" << vit->first << "   ";
				app.show_appInfo(STU);
			}
		}
		else {
			cout << "无学生申请信息：" << endl;
		}

		if (way == STU) {
			return;
		}
		cout << endl;
	}

	if (!this->tea_app.empty()) {
		cout << "教职工申请信息：" << endl;
		for (auto vit = this->tea_app.begin(); vit != this->tea_app.end(); ++vit) {
			AppTable app;
			app.add_tea_app(vit->second);
			cout << "uid:" << vit->first << "   ";
			app.show_appInfo(TEA);
		}
	}
	else {
		cout << "无教职工申请信息：" << endl;
	}
}

int AppointmentSystem::put_tea_app(int period, int day, int room,int uid)
{
	AppTable app;
	int info=app.set_appInfo(period, day, room, 0, 3);//0表示申请整间教室，3代表申请通过
	this->tea_app.push_back(make_pair(uid,info));
	return info;
}

void AppointmentSystem::put_stu_app(int period, int day, int room,int seat,int state,int uid)
{
	AppTable app;
	int info = app.set_appInfo(period, day, room, seat, state);
	this->stu_record.push_back(make_pair(uid, info));
}


pair<int, Student>  AppointmentSystem::is_right_stu(int id, string password)
{
	Student stu;
	stu.set_info(0, "");
	pair<int, Student> p(make_pair(0, stu));

	for (auto it = stuInfo.begin(); it != stuInfo.end(); ++it) {
		if (it->second.show_id() == id) {
			if (it->second.show_password() == password) {
				return *it;
			}
			else {
				return p;
			}
		}
	}
	return p;
}

pair<int, Teacher> AppointmentSystem::is_right_tea(int id, string password)
{
	Teacher tea;
	tea.set_info(0, "");
	pair<int, Teacher> p(make_pair(0, tea));

	for (auto it = teaInfo.begin(); it != teaInfo.end(); ++it) {
		if (it->second.show_id() == id) {
			if (it->second.show_password() == password) {
				return *it;
			}
			else {
				return p;
			}
		}
	}
	return p;
}

void AppointmentSystem::sign_in(bool stu)
{
	int id;
	string password;
	cout << "请输入账号：" << endl;
	cin >> id;
	cout << "请输入密码：" << endl;
	cin >> password;

	if (stu) {
		this->stuPart(is_right_stu(id, password));
	}
	else {
		if (id == admInfo.show_id() && password == admInfo.show_password()) {
			system("cls");
			this->admPart();
		}
		else {
			this->teaPart(is_right_tea(id, password));
		}
	}
	system("pause");
	system("cls");
}

void AppointmentSystem::load_stuRecord()
{
	ifstream infile;
	infile.open("stuRecord.csv", ios::in);
	
	if (infile.is_open()) {
		string data;
		int uid, info;
		while (infile >> data) {
			int index = 0, pos = -1;
			for (int i = 0; i < 2; ++i) {
				pos = data.find(",", index);
				string temp = data.substr(index, pos - index);
				if (i == 0) {
					uid = stoi(temp);
				}
				else {
					info = stoi(temp);
				}
				index = pos + 1;
			}
			this->stu_record.push_back(make_pair(uid, info));
		}
		infile.close();
	}
}

void AppointmentSystem::save_stuRecord()
{
	ofstream outfile;
	outfile.open("stuRecord.csv", ios::out);
	for (auto lit = this->stu_record.begin(); lit != this->stu_record.end(); ++lit) {
		if (lit->second / 1000 % 10 != 3) {
			outfile << lit->first << "," << lit->second << "," << endl;
		}
	}
}

void AppointmentSystem::clear_stuRecord()
{
	ofstream outfile;
	outfile.open("stuRecord.csv", ios::trunc);
	outfile.close();
	this->computerRoom.init(true);
}

void AppointmentSystem::loadApp(int choice)
{
	if (choice != TEA) {
		ifstream infile_stu;
		infile_stu.open("stuApp.csv", ios::in);
		if (infile_stu.is_open()) {
			string data;
			while (infile_stu >> data) {
				int index = 0, pos = -1;
				int uid, info;
				for (int i = 0; i < 2; ++i) {
					pos = data.find(",", index);
					string temp = data.substr(index, pos - index);
					if (i == 0) {
						uid = stoi(temp);
					}
					else {
						info = stoi(temp);
					}
					index = pos + 1;
				}
				this->stu_app.push_back(make_pair(uid, info));
			}
			infile_stu.close();
		}
		if (choice == STU) {
			return;
		}
	}

	ifstream infile_tea;
	infile_tea.open("teaApp.csv", ios::in);
	if (infile_tea.is_open()) {
		string data;
		while (infile_tea >> data) {
			int index = 0, pos = -1;
			int uid, info;
			for (int i = 0; i < 2; ++i) {
				pos = data.find(",", index);
				string temp = data.substr(index, pos - index);
				if (i == 0) {
					uid = stoi(temp);
				}
				else {
					info = stoi(temp);
				}
				index = pos + 1;
			}
			this->tea_app.push_back(make_pair(uid, info));
		}
		infile_tea.close();
	}
}

void AppointmentSystem::saveApp(int choice)
{
	if (choice != TEA) {
		ofstream outfile_stu;
		outfile_stu.open("stuApp.csv", ios::out);
		for (auto vit = this->stu_app.begin(); vit != this->stu_app.end(); ++vit) {
			outfile_stu << vit->first << "," << vit->second << "," << endl;
		}
		outfile_stu.close();

		if (choice == STU) {
			return;
		}
	}

	ofstream outfile_tea;
	outfile_tea.open("teaApp.csv", ios::out);
	for (auto vit = this->tea_app.begin(); vit != this->tea_app.end(); ++vit) {
		outfile_tea << vit->first << "," << vit->second << "," << endl;
	}
	outfile_tea.close();
}

void AppointmentSystem::clearApp()
{
	this->stu_app.clear();
	this->tea_app.clear();
	this->saveApp(SANDT);
}

void AppointmentSystem::showUser(int period, int day, int choice)
{
	if (choice != TEA) {
		for (auto vit = this->stu_app.begin(); vit != this->stu_app.end(); ++vit) {
			ComputerRoom com;
			if (vit->second / 100000 == period * 10 + day){
				int seat = vit->second % 1000;
				int room = vit->second / 10000 % 10;
				cout << "学生" << "  " << "uid:" << vit->first
					<< " < " << com.str_period(period) << " > < "
					<< com.str_room(room) << " > < "
					<< seat << " > 号" << endl;
			}
		}
		if (choice == STU) {
			return;
		}
		cout << endl;
	}

	for (auto vit = this->tea_app.begin(); vit != this->tea_app.end(); ++vit) {
		ComputerRoom com;
		if (vit->second / 100000 == period * 10 + day) {
			int room = vit->second / 10000 % 10;
			cout << "教职工" << "  " << "uid:" << vit->first
				<< " < " << com.str_period(period) << " > < "
				<< com.str_room(room) << " >" << endl;
		}
	}
}

void AppointmentSystem::show_userPart(int period, int day)
{
	while (true) {
		int choice;
		cout << "要查看使用用户吗？" << endl;
		cout << "1、查看学生" << endl;
		cout << "2、查看教师" << endl;
		cout << "3、查看全部" << endl;
		cout << "4、不查看" << endl;
		cout << "5、退出" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			this->showUser(period, day, STU);
			break;
		}
		case 2:
		{
			this->showUser(period, day, TEA);
			break;
		}
		case 3:
		{
			this->showUser(period, day, SANDT);
			break;
		}
		case 5:
		{
			return;
		}
		default:
			break;
		}
	}
}

void AppointmentSystem::examine_stuRec()
{
	AppTable app;
	int index = 1;

	for (auto lit = this->stu_record.begin(); lit != this->stu_record.end(); ++lit) {
		if (lit->second / 1000 % 10 != 3) {
			cout << index++ << "======= " << "编号：" << lit->first << "  信息：";
			app.add_stu_app(lit->second);
			app.show_appInfo(STU);
		}
	}
}

Student AppointmentSystem::show_stu(int uid)
{
	for (auto mit = this->stuInfo.begin(); mit != this->stuInfo.end(); ++mit) {
		if (mit->first == uid) {
			return mit->second;
		}
	}
	Student stu;
	return stu;
}

void AppointmentSystem::examine_stuRec(int index,bool pass)
{
	int state = NONAPP;
	if (pass) {
		state = PASS;
	}
	else {
		state = NOTPASS;
	}

	if (index != 0) {
		int ind = 1;
		for (auto lit = this->stu_record.begin(); lit != this->stu_record.end(); ++lit) {
			if (index == ind && lit->second / 1000 % 10 != 3) {
				lit->second = lit->second / 10000*10000 + state*1000 + lit->second % 1000;
				Student stu = this->show_stu(lit->first);
				stu.change_apt(lit->first, state);
				if (state == PASS) {
					this->stu_app.push_back(make_pair(lit->first, lit->second));
				}
				else {
					this->computerRoom.room_forTea(lit->second);
					this->computerRoom.saveRInfo(lit->second/10000%10);
				}
				break;
			}
			ind++;
		}
	}
	else {
		for (auto lit = this->stu_record.begin(); lit != this->stu_record.end(); ++lit) {
			if (lit->second / 1000 % 10 != 3) {
				lit->second = lit->second / 10000*10000 + state*1000 + lit->second % 1000;
				Student stu = this->show_stu(lit->first);
				stu.change_apt(lit->first, state);
				if (state == PASS) {
					this->stu_app.push_back(make_pair(lit->first, lit->second));
				}
				else {
					this->computerRoom.room_forTea(lit->second);
				}
			}
		}
		if (!pass) {
			this->computerRoom.saveRInfo(1);
			this->computerRoom.saveRInfo(2);
			this->computerRoom.saveRInfo(3);
			this->computerRoom.saveRInfo(4);
			this->computerRoom.saveRInfo(5);
			this->computerRoom.saveRInfo(6);
		}
	}
	this->save_stuRecord();
	this->stu_record.clear();
	this->load_stuRecord();

	if (pass) {
		this->saveApp(STU);
	}
}

void AppointmentSystem::admPart()
{
	while (true) {
		this->admInfo.show_menu();
		int seclet_adm = 0;
		cin >> seclet_adm;

		switch (seclet_adm) {
		case 1:
		{
			cout << "请选择要添加的账号类型：" << endl;
			cout << "1、学生" << endl;
			cout << "2、教职工" << endl;

			int kind_secect = 0;
			cin >> kind_secect;

			switch (kind_secect) {
			case 1:
			{
				add_account(true);
				this->saveUInfo(STU);
				break;
			}
			case 2:
			{
				add_account(false);
				this->saveUInfo(TEA);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 2:
		{
			int find_way = 0;
			cout << "请输入要查找的账号信息与查找方式：" << endl;
			cout << "1、学生账号" << endl;
			cout << "2、教职工账号" << endl;
			cout << "3、全部账号" << endl;
			cin >> find_way;
			this->find_account(find_way);
			break;
		}
		case 3:
		{
			int choice;
			cout << "请选择你要查找的账号记录：" << endl;
			cout << "1、学生账号" << endl;
			cout << "2、教职工账号" << endl;
			cout << "3、全部账号" << endl;
			cin >> choice;

			switch (choice) {
			case 1:
			{
				this->show_app(STU);
				break;
			}
			case 2:
			{
				this->show_app(TEA);
				break;
			}
			default:
			{
				this->show_app(SANDT);
				break;
			}
			}
			break;
		}
		case 4:
		{
			system("cls");
			this->computerRoom.show_time_table();
			int period, day;
			cout << "请选择查看时间：" << endl;
			cin >> period >> day;
			int right = this->computerRoom.show_room_info(period, day);
			if (!right) {
				cout << "时间错误！" << endl;
			}
			else {
				this->show_userPart(period, day);
			}
			break;
		}
		case 5:
		{
			int choice;
			cout << "确定清空预约记录吗！" << endl;
			cout << "1、确定" << endl;
			cout << "2、取消" << endl;
			cin >> choice;

			if (choice == 1) {
				this->clearAppInfo();
				cout << "清空成功！" << endl;
			}
			break;
		}
		case 6:
		{
			string password, password1;
			cout << "请输入新密码：" << endl;
			cin >> password;
			cout << "请再次确认你的密码：" << endl;
			cin >> password1;
			if (password == password1) {
				this->admInfo.changePas(password);
				this->saveUInfo(ADM);
				cout << "修改成功!" << endl;
			}
			else {
				cout << "修改失败！" << endl;
			}
			break;
		}
		case 7:
		{
			return;
		}
		default:
		{
			break;
		}
		}
		system("pause");
		system("cls");
	}
}

void AppointmentSystem::stuPart(pair<int, Student> p)
{
	if (p.first == 0) {
		cout << "用户名或密码错误！" << endl;
	}
	else {
		Student stu(p.second);
		int uid = p.first;
		stu.loadInfo(uid);
		system("cls");
		while (true) {
			stu.show_menu();
			int seclet_stu = 0;
			cout << "请选择功能：" << endl;
			cin >> seclet_stu;

			switch (seclet_stu)
			{
			case 1:
			{
				if (stu.show_state() != 0) {
					cout << "你的预约已受理或生效！" << endl;
				}
				else {
					system("cls");
					this->computerRoom.show_time_table();
					int period, day;
					cout << "请选择预约时间段：" << endl;
					cin >> period >> day;
					int right = this->computerRoom.show_room_info(period, day);

					if (right) {
						int room;
						cout << "请选择机房：" << endl;
						cin >> room;
						int index = this->computerRoom.is_app_suf(period, day, room);

						if (index != -1) {
							int seat = index + 1;
							this->computerRoom.show_app_result(period, day, room, seat);
							stu.set_state(1);
							this->stu_record.push_back(make_pair(uid, stu.set_apt(period, day, room, seat)));
							this->save_stuRecord();
							stu.saveInfo(uid);
						}
						else {
							cout << "所选机房已满或不存在！" << endl;
						}
					}
					else {
						cout << "该时间段有误！" << endl;
					}
				}
				break;
			}
			case 2:
			{
				int info = stu.getAptInfo();
				if (info != -1) {
					this->computerRoom.set_app_result(info / 1000000, info / 100000 % 10, info / 10000 % 10, info % 1000, false);
					this->remove_record(uid, info);
					stu.set_state(0);
					stu.change_apt_state(2);
					stu.saveInfo(uid);
					cout << "预约已取消！" << endl;
				}
				else {
					cout << "没有待处理的预约！" << endl;
				}
				break;
			}
			case 3:
			{
				stu.show_apt();
				break;
			}
			case 4:
			{
				string password, password1;
				cout << "请输入新密码：" << endl;
				cin >> password;
				cout << "请再次确认你的密码：" << endl;
				cin >> password1;
				if (password == password1) {
					stu.changePas(password);
					this->saveUInfo(STU);
					cout << "修改成功!" << endl;
				}
				else {
					cout << "修改失败！" << endl;
				}
				break;
			}
			case 5:
				return;
			default:
				break;
			}
			system("pause");
			system("cls");
		}
	}
}

void AppointmentSystem::teaPart(pair<int, Teacher> p)
{
	if (p.first == 0) {
		cout << "学号或密码错误！" << endl;
	}
	else {
		Teacher tea(p.second);
		int uid = p.first;
		tea.loadInfo(uid);
		system("cls");
		while (true) {
			tea.show_menu();
			int seclet_tea = 0;
			cout << "请选择功能：" << endl;
			cin >> seclet_tea;

			switch (seclet_tea)
			{
			case 1:
			{
				system("cls");
				if (!this->stu_record.empty()) {
					this->examine_stuRec();
					int choice;
					cout << "请选择要批准申请的方式：" << endl;
					cout << "1、单人" << endl;
					cout << "2、全部" << endl;
					cout << "3、退出" << endl;
					cin >> choice;
					if (choice != 1 && choice != 2) {
						break;
					}
					if (choice == 1) {
						cout << "请选择申请：" << endl;
						cin >> choice;
					}
					else {
						choice = 0;
					}
					int pass;
					cout << "是否批准：" << endl;
					cout << "1、是，同意" << endl;
					cout << "2、不批准" << endl;
					cin >> pass;
					bool bpass;
					if (pass == 1) {
						bpass = true;
					}
					else if (pass == 2) {
						bpass = false;
					}
					else {
						break;
					}
					this->examine_stuRec(choice, bpass);
					cout << "操作成功" << endl;
				}
				else {
					cout << "无待批准申请！" << endl;
				}
				break;
			}
			case 2:
			{
				this->computerRoom.show_time_table();
				int period, day;
				cout << "请选择预约时间段：" << endl;
				cin >> period >> day;
				int right = this->computerRoom.show_room_info(period, day);

				if (right) {
					int room;
					cout << "请选择机房：" << endl;
					cin >> room;
					if (room > 0 && room < 7) {
						int flag = this->computerRoom.tea_app_room(period, day, room, true);
						if (flag == 1) {
							int info = this->put_tea_app(period, day, room, uid);
							AppTable app;
							app.add_tea_app(info);
							tea.aptRecord(app);
							tea.saveInfo(uid);
							this->saveApp(TEA);
						}
						else {
							cout << "机房已被预约" << endl;
						}
					}
					else {
						cout << "机房不存在！" << endl;
					}
				}
				else {
					cout << "该时间段有误！" << endl;
				}
				break;
			}
			case 3:
			{
				int info = tea.cancel_app(uid);
				this->computerRoom.tea_app_room(info / 100, info / 10 % 10, info % 10, false);
				break;
			}
			case 4:
			{
				tea.show_aptRec();
				break;
			}
			case 5:
			{
				string password, password1;
				cout << "请输入新密码：" << endl;
				cin >> password;
				cout << "请再次确认你的密码：" << endl;
				cin >> password1;
				if (password == password1) {
					tea.changePas(password);
					this->saveUInfo(TEA);
					cout << "修改成功!" << endl;
				}
				else {
					cout << "修改失败！" << endl;
				}
				break;
			}
			case 6:
				return;
			default:
				break;
			}
			system("pause");
			system("cls");
		}
	}
}