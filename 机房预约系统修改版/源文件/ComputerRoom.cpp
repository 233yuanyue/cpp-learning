#include"ComputerRoom.h"

constexpr int ComputerRoom::RNUM1;
constexpr int ComputerRoom::RNUM2;
constexpr int ComputerRoom::RNUM3;
constexpr int ComputerRoom::RNUM4;
constexpr int ComputerRoom::RNUM5;
constexpr int ComputerRoom::RNUM6;
constexpr int ComputerRoom::FAIL;
constexpr int ComputerRoom::SUCFUL;
constexpr int ComputerRoom::CANCEL;
constexpr int ComputerRoom::NFULL;
constexpr int ComputerRoom::SFULL;
constexpr int ComputerRoom::TFULL;
constexpr bool ComputerRoom::USED;
constexpr bool ComputerRoom::NUSED;

ComputerRoom::ComputerRoom()
{
	if (!this->loadInfo()) {
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 6; ++j) {
				for (int k = 0; k < 6; ++k) {
					this->is_full[i][j][k] = NFULL;
				}
			}
		}
	}
	this->init(false);
}

void ComputerRoom::init(bool _init)
{
	if (_init || !this->loadRInfo(1)) {
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 6; ++j) {
				for (int k = 0; k < RNUM1; ++k) {
					this->room1[i][j][k] = NUSED;
				}
			}
		}
	}

	if (_init || !this->loadRInfo(2)) {
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 6; ++j) {
				for (int k = 0; k < RNUM2; ++k) {
					this->room2[i][j][k] = NUSED;
				}
			}
		}
	}

	if (_init || !this->loadRInfo(3)) {
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 6; ++j) {
				for (int k = 0; k < RNUM3; ++k) {
					this->room3[i][j][k] = NUSED;
				}
			}
		}
	}

	if (_init || !this->loadRInfo(4)) {
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 6; ++j) {
				for (int k = 0; k < RNUM4; ++k) {
					this->room4[i][j][k] = NUSED;
				}
			}
		}
	}

	if (_init || !this->loadRInfo(5)) {
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 6; ++j) {
				for (int k = 0; k < RNUM5; ++k) {
					this->room5[i][j][k] = NUSED;
				}
			}
		}
	}

	if (_init || !this->loadRInfo(6)) {
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 6; ++j) {
				for (int k = 0; k < RNUM6; ++k) {
					this->room6[i][j][k] = NUSED;
				}
			}
		}
	}
}

bool ComputerRoom::loadInfo()
{
	ifstream infile;
	infile.open("RoomInfo.csv", std::ios::in);

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
		while (infile >> data) {
			int index = 0, pos = -1;
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 6; ++j) {
					for (int k = 0; k < 6; ++k) {
						pos = data.find(",", index);

						if (pos == -1) {//找不到返回-1
							break;
						}

						string temp = data.substr(index, pos - index);
						int info = std::stoi(temp);
						this->is_full[i][j][k]=info;
						index = pos + 1;
					}
				}
			}
			infile.close();
			return true;
		}
	}
	return false;
}

void ComputerRoom::saveInfo()
{
	ofstream outfile;
	outfile.open("RoomInfo.csv", ios::out);
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 6; ++j) {
			for (int k = 0; k < 6; ++k) {
				outfile << this->is_full[i][j][k] << ",";
			}
		}
	}
	outfile.close();
}

bool ComputerRoom::loadRInfo(int room)
{
	ifstream infile;
	switch (room)
	{
	case 1:
	{
		infile.open("Room1.csv", ios::in);
		if (infile.is_open()) {
			string data;

			char ch;
			infile >> ch;
			if (infile.eof()) {
				infile.close();
				return false;
			}
			else {
				infile.putback(ch);
			}

			while (infile >> data) {
				int index = 0, pos = -1;
				for (int i = 0; i < 5; ++i) {
					for (int j = 0; j < 6; ++j) {
						for (int k = 0; k < RNUM1; ++k) {
							pos = data.find(",", index);
							string temp = data.substr(index, pos - index);
							int iinfo = stoi(temp);
							bool binfo = static_cast<bool>(iinfo);
							this->room1[i][j][k] = binfo;
							index = pos + 1;
						}
					}
				}
			}
			infile.close();
			return true;
		}
		return false;
	}
	case 2:
	{
		infile.open("Room2.csv", ios::in);
		if (infile.is_open()) {
			string data;

			char ch;
			infile >> ch;
			if (infile.eof()) {
				infile.close();
				return false;
			}
			else {
				infile.putback(ch);
			}

			while (infile >> data) {
				int index = 0, pos = -1;
				for (int i = 0; i < 5; ++i) {
					for (int j = 0; j < 6; ++j) {
						for (int k = 0; k < RNUM2; ++k) {
							pos = data.find(",", index);
							string temp = data.substr(index, pos - index);
							int iinfo = stoi(temp);
							bool binfo = static_cast<bool>(iinfo);
							this->room2[i][j][k] = binfo;
							index = pos + 1;
						}
					}
				}
			}
			infile.close();
			return true;
		}
		return false;
	}
	case 3:
	{
		infile.open("Room3.csv", ios::in);
		if (infile.is_open()) {
			string data;

			char ch;
			infile >> ch;
			if (infile.eof()) {
				infile.close();
				return false;
			}
			else {
				infile.putback(ch);
			}

			while (infile >> data) {
				int index = 0, pos = -1;
				for (int i = 0; i < 5; ++i) {
					for (int j = 0; j < 6; ++j) {
						for (int k = 0; k < RNUM3; ++k) {
							pos = data.find(",", index);
							string temp = data.substr(index, pos - index);
							int iinfo = stoi(temp);
							bool binfo = static_cast<bool>(iinfo);
							this->room3[i][j][k] = binfo;
							index = pos + 1;
						}
					}
				}
			}
			infile.close();
			return true;
		}
		return false;
	}
	case 4:
	{
		infile.open("Room4.csv", ios::in);
		if (infile.is_open()) {
			string data;

			char ch;
			infile >> ch;
			if (infile.eof()) {
				infile.close();
				return false;
			}
			else {
				infile.putback(ch);
			}

			while (infile >> data) {
				int index = 0, pos = -1;
				for (int i = 0; i < 5; ++i) {
					for (int j = 0; j < 6; ++j) {
						for (int k = 0; k < RNUM4; ++k) {
							pos = data.find(",", index);
							string temp = data.substr(index, pos - index);
							int iinfo = stoi(temp);
							bool binfo = static_cast<bool>(iinfo);
							this->room4[i][j][k] = binfo;
							index = pos + 1;
						}
					}
				}
			}
			infile.close();
			return true;
		}
		return false;
	}
	case 5:
	{
		infile.open("Room5.csv", ios::in);
		if (infile.is_open()) {
			string data;

			char ch;
			infile >> ch;
			if (infile.eof()) {
				infile.close();
				return false;
			}
			else {
				infile.putback(ch);
			}

			while (infile >> data) {
				int index = 0, pos = -1;
				for (int i = 0; i < 5; ++i) {
					for (int j = 0; j < 6; ++j) {
						for (int k = 0; k < RNUM5; ++k) {
							pos = data.find(",", index);
							string temp = data.substr(index, pos - index);
							int iinfo = stoi(temp);
							bool binfo = static_cast<bool>(iinfo);
							this->room5[i][j][k] = binfo;
							index = pos + 1;
						}
					}
				}
			}
			infile.close();
			return true;
		}
		return false;
	}
	case 6:
	{
		infile.open("Room6.csv", ios::in);
		if (infile.is_open()) {
			string data;

			char ch;
			infile >> ch;
			if (infile.eof()) {
				infile.close();
				return false;
			}
			else {
				infile.putback(ch);
			}

			while (infile >> data) {
				int index = 0, pos = -1;
				for (int i = 0; i < 5; ++i) {
					for (int j = 0; j < 6; ++j) {
						for (int k = 0; k < RNUM6; ++k) {
							pos = data.find(",", index);
							string temp = data.substr(index, pos - index);
							int iinfo = stoi(temp);
							bool binfo = static_cast<bool>(iinfo);
							this->room6[i][j][k] = binfo;
							index = pos + 1;
						}
					}
				}
			}
			infile.close();
			return true;
		}
		return false;
	}
	default:
		break;
	}
	return false;
}

void ComputerRoom::saveRInfo(int room)
{
	ofstream outfile;
	switch (room)
	{
	case 1:
	{
		outfile.open("Room1.csv", ios::out);
		if (outfile.is_open()) {
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 6; ++j) {
					for (int k = 0; k < RNUM1; ++k) {
						outfile << this->room1[i][j][k] << ",";
					}
				}
			}
		}
		break;
	}
	case 2:
	{
		outfile.open("Room2.csv", ios::out);
		if (outfile.is_open()) {
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 6; ++j) {
					for (int k = 0; k < RNUM2; ++k) {
						outfile << this->room2[i][j][k] << ",";
					}
				}
			}
		}
		break;
	}
	case 3:
	{
		outfile.open("Room3.csv", ios::out);
		if (outfile.is_open()) {
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 6; ++j) {
					for (int k = 0; k < RNUM3; ++k) {
						outfile << this->room3[i][j][k] << ",";
					}
				}
			}
		}
		break;
	}
	case 4:
	{
		outfile.open("Room4.csv", ios::out);
		if (outfile.is_open()) {
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 6; ++j) {
					for (int k = 0; k < RNUM4; ++k) {
						outfile << this->room4[i][j][k] << ",";
					}
				}
			}
		}
		break;
	}
	case 5:
	{
		outfile.open("Room5.csv", ios::out);
		if (outfile.is_open()) {
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 6; ++j) {
					for (int k = 0; k < RNUM5; ++k) {
						outfile << this->room5[i][j][k] << ",";
					}
				}
			}
		}
		break;
	}
	case 6:
	{
		outfile.open("Room6.csv", ios::out);
		if (outfile.is_open()) {
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 6; ++j) {
					for (int k = 0; k < RNUM6; ++k) {
						outfile << this->room6[i][j][k] << ",";
					}
				}
			}
		}
		break;
	}
	default:
		break;
	}
	outfile.close();
}

void ComputerRoom::clearInfo()
{
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 6; ++j) {
			for (int k = 0; k < 6; ++k) {
				this->is_full[i][j][k] = NFULL;
			}
		}
	}
	this->init(true);
}

void ComputerRoom::room_forTea(int info)
{
	int period = info / 1000000;
	int day = info / 100000 % 10;
	int room = info / 10000 % 10;
	int seat = info % 1000;
	switch (room)
	{
	case 1:
	{
		this->room1[period - 1][day - 1][seat - 1] = NUSED;
		break;
	}
	case 2:
	{
		this->room2[period - 1][day - 1][seat - 1] = NUSED;
		break;
	}
	case 3:
	{
		this->room3[period - 1][day - 1][seat - 1] = NUSED;
		break;
	}
	case 4:
	{
		this->room4[period - 1][day - 1][seat - 1] = NUSED;
		break;
	}
	case 5:
	{
		this->room5[period - 1][day - 1][seat - 1] = NUSED;
		break;
	}
	case 6:
	{
		this->room6[period - 1][day - 1][seat - 1] = NUSED;
		break;
	}
	}
}

void ComputerRoom::isFull(int period, int day,int room, int num)
{
	if (num == 0) {
		this->is_full[period - 1][day - 1][room - 1] = SFULL;
	}
	else {
		this->is_full[period - 1][day - 1][room - 1] = NFULL;
	}	
}

int ComputerRoom::get_room_rest(int period, int day)
{
	int fNum = 0;
	for (int room = 0; room < 6; ++room) {
		if (!this->is_full[period-1][day-1][room]) {
			fNum++;
		}
	}
	return fNum;
}

int ComputerRoom::get_all_rest(int period,int day,int room)
{
	int rNum = 0;
	if (this->is_full[period-1][day-1][room-1]!=TFULL) {
		switch (room)
		{
		case 1:
		{
			for (int i = 0; i < RNUM1; ++i) {
				if (this->room1[period - 1][day - 1][i] == NUSED) {
					rNum++;
				}
			}
			this->isFull(period, day, room, rNum);
			return rNum;
		}
		case 2:
		{
			for (int i = 0; i < RNUM2; ++i) {
				if (this->room2[period - 1][day - 1][i] == NUSED) {
					rNum++;
				}
			}
			this->isFull(period, day, room, rNum);
			return rNum;
		}
		case 3:
		{
			for (int i = 0; i < RNUM3; ++i) {
				if (this->room3[period - 1][day - 1][i] == NUSED) {
					rNum++;
				}
			}
			this->isFull(period, day, room, rNum);
			return rNum;
		}
		case 4:
		{
			for (int i = 0; i < RNUM4; ++i) {
				if (this->room4[period - 1][day - 1][i] == NUSED) {
					rNum++;
				}
			}
			this->isFull(period, day, room, rNum);
			return rNum;
		}
		case 5:
		{
			for (int i = 0; i < RNUM5; ++i) {
				if (this->room5[period - 1][day - 1][i] == NUSED) {
					rNum++;
				}
			}
			this->isFull(period, day, room, rNum);
			return rNum;
		}
		case 6:
		{
			for (int i = 0; i < RNUM6; ++i) {
				if (this->room6[period - 1][day - 1][i] == NUSED) {
					rNum++;
				}
			}
			this->isFull(period, day, room, rNum);
			return rNum;
		}
		default:
			break;
		}
	}
	return rNum;
}

void ComputerRoom::show_time_table()
{
	cout << "可选机房数	周一(1)	周二(2)	周三(3)	周四(4)	周五(5)	周六(6) " << endl;
	cout << " 上午一(1)	" << get_room_rest(1, 1) << "	" << get_room_rest(1, 2) << "	" << get_room_rest(1, 3)
		<< "	" << get_room_rest(1, 4) << "	" << get_room_rest(1, 5) << "	" << get_room_rest(1, 6) << "	" << endl;
	cout << " 上午二(2)	" << get_room_rest(2, 1) << "	" << get_room_rest(2, 2) << "	" << get_room_rest(2, 3)
		<< "	" << get_room_rest(2, 4) << "	" << get_room_rest(2, 5) << "	" << get_room_rest(2, 6) << "	" << endl;
	cout << " 下午一(3)	" << get_room_rest(3, 1) << "	" << get_room_rest(3, 2) << "	" << get_room_rest(3, 3)
		<< "	" << get_room_rest(3, 4) << "	" << get_room_rest(3, 5) << "	" << get_room_rest(3, 6) << "	" << endl;
	cout << " 下午二(4)	" << get_room_rest(4, 1) << "	" << get_room_rest(4, 2) << "	" << get_room_rest(4, 3)
		<< "	" << get_room_rest(4, 4) << "	" << get_room_rest(4, 5) << "	" << get_room_rest(4, 6) << "	" << endl;
	cout << " 晚间段(5)	" << get_room_rest(5, 1) << "	" << get_room_rest(5, 2) << "	" << get_room_rest(5, 3)
		<< "	" << get_room_rest(5, 4) << "	" << get_room_rest(5, 5) << "	" << get_room_rest(5, 6) << "	" << endl;
	cout << "								" << endl;
}

int ComputerRoom::show_room_info(int period,int day)
{
	if (period > 0 && period < 6 && day>0 && day < 7) {
		cout << "该时间段机房情况如下：" << endl;
		cout << "1号机房剩余：" << this->get_all_rest(period, day, 1) << endl;
		cout << "2号机房剩余：" << this->get_all_rest(period, day, 2) << endl;
		cout << "3号机房剩余：" << this->get_all_rest(period, day, 3) << endl;
		cout << "4号机房剩余：" << this->get_all_rest(period, day, 4) << endl;
		cout << "5号机房剩余：" << this->get_all_rest(period, day, 5) << endl;
		cout << "6号机房剩余：" << this->get_all_rest(period, day, 6) << endl;
	}
	else {
		return 0;
	}

	return 1;
}

int ComputerRoom::is_app_suf(int period, int day, int room)
{
	if(this->is_full[period - 1][day - 1][room - 1]!=NFULL) {
		return -1;
	}
	else {
		switch (room)
		{
		case 1:
		{
			for (int i = 0; i < RNUM1; ++i) {
				if (this->room1[period - 1][day - 1][i] == NUSED) {
					this->room1[period - 1][day - 1][i] = USED;
					this->saveRInfo(room);
					return i;
				}
			}
			break;
		}
		case 2:
		{
			for (int i = 0; i < RNUM2; ++i) {
				if (this->room2[period - 1][day - 1][i] == NUSED) {
					this->room2[period - 1][day - 1][i] = USED;
					this->saveRInfo(room);
					return i;
				}
			}
			break;
		}
		case 3:
		{
			for (int i = 0; i < RNUM3; ++i) {
				if (this->room3[period - 1][day - 1][i] == NUSED) {
					this->room3[period - 1][day - 1][i] = USED;
					this->saveRInfo(room);
					return i;
				}
			}
			break;
		}
		case 4:
		{
			for (int i = 0; i < RNUM4; ++i) {
				if (this->room4[period - 1][day - 1][i] == NUSED) {
					this->room4[period - 1][day - 1][i] = USED;
					this->saveRInfo(room);
					return i;
				}
			}
			break;
		}
		case 5:
		{
			for (int i = 0; i < RNUM5; ++i) {
				if (this->room5[period - 1][day - 1][i] == NUSED) {
					this->room5[period - 1][day - 1][i] = USED;
					this->saveRInfo(room);
					return i;
				}
			}
			break;
		}
		case 6:
		{
			for (int i = 0; i < RNUM6; ++i) {
				if (this->room6[period - 1][day - 1][i] == NUSED) {
					this->room6[period - 1][day - 1][i] = USED;
					this->saveRInfo(room);
					return i;
				}
			}
			break;
		}
		default:
			break;
		}
	}
	return -1;
}

string ComputerRoom::str_period(int period)
{
	switch (period) {
	case 1:
		return "上午一";
	case 2:
		return "上午二";
	case 3:
		return "下午一";
	case 4:
		return "下午二";
	case 5:
		return "晚上段";
	}

	return "ERROR";
}
string ComputerRoom::str_day(int day)
{
	switch (day) {
	case 1:
		return "周一";
	case 2:
		return "周二";
	case 3:
		return "周三";
	case 4:
		return "周四";
	case 5:
		return "周五";
	case 6:
		return "周六";
	}

	return "ERROR";
}
string ComputerRoom::str_room(int room)
{
	switch (room) {
	case 1:
		return "一号机房";
	case 2:
		return "二号机房";
	case 3:
		return "三号机房";
	case 4:
		return "四号机房";
	case 5:
		return "五号机房";
	case 6:
		return "六号机房";
	}

	return "ERROR";
}

string ComputerRoom::str_state(int state)
{
	switch (state)
	{
	case 1:
		return "审核未通过";
	case 2:
		return "主动取消";
	case 3:
		return "审核通过";
	case 4:
		return "审核中";
	default:
		break;
	}

	return "ERROR";
}

void ComputerRoom::show_app_result(int period, int day, int room,int seat)
{
	cout << "你已预约< " << this->str_day(day) << " >   < "
		<< this->str_period(period) << " >   < "
		<< this->str_room(room) << " >   < "
		<<  seat << " >号" << endl;
	cout << "请等待系统审核" << endl;
}

void ComputerRoom::show_app_record(int period, int day, int room, int seat,int state)
{
	cout << "" << "<" << this->str_day(day) << " >  < "
		<< this->str_period(period) << " >  < "
		<< this->str_room(room) << " >  < "
		<< seat << " >号   < "
		<< this->str_state(state) << " >" << endl;
}

void ComputerRoom::set_app_result(int period, int day, int room, int seat,bool used)
{
	switch (room)
	{
	case 1:
	{
		this->room1[period - 1][day - 1][seat - 1] = used;
		this->saveRInfo(room);
		break;
	}
	case 2:
	{
		this->room2[period - 1][day - 1][seat - 1] = used;
		this->saveRInfo(room);
		break;
	}
	case 3:
	{
		this->room3[period - 1][day - 1][seat - 1] = used;
		this->saveRInfo(room);
		break;
	}
	case 4:
	{
		this->room4[period - 1][day - 1][seat - 1] = used;
		this->saveRInfo(room);
		break;
	}
	case 5:
	{
		this->room5[period - 1][day - 1][seat - 1] = used;
		this->saveRInfo(room);
		break;
	}
	case 6:
	{
		this->room6[period - 1][day - 1][seat - 1] = used;
		this->saveRInfo(room);
		break;
	}
	default:
		break;
	}
}

int ComputerRoom::tea_app_room(int period, int day, int room,bool app)
{
	if (app) {
		if (this->is_full[period - 1][day - 1][room - 1] == TFULL) {
			return FAIL;
		}
		else {
			this->is_full[period - 1][day - 1][room - 1] = TFULL;
			cout << "你已申请< " << this->str_day(day) << " >   < "
				<< this->str_period(period) << " >   < "
				<< this->str_room(room) << " >" << endl;
			this->saveInfo();
			return SUCFUL;
		}
	}
	else {
		this->is_full[period - 1][day - 1][room - 1] = NFULL;
		this->saveInfo();
		return CANCEL;
	}
}
