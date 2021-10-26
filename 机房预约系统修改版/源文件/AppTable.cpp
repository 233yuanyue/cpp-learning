#include"AppTable.h"

constexpr int AppTable::STU;
constexpr int AppTable::TEA;
constexpr int AppTable::SANDT;

/*state说明：
0、无审核
1、审核未通过
2、主动取消
3、审核通过
4、审核中
*/
int AppTable::set_appInfo(int period,int day,int room,int seat,int state)
{
	int info=this->app_time = period * 1000000 + day * 100000 + room * 10000 + state * 1000 + seat;
	this->app_state = state;
	return info;
}

int AppTable::show_appInfo()
{
	return this->app_time;
}

int AppTable::show_state()
{
	return this->app_state;
}

void AppTable::show_appInfo(int choice)
{
	ComputerRoom com;
	if (choice != TEA) {
		cout << "< " << com.str_day(this->app_time / 100000 % 10) << " >   < "
			<< com.str_period(this->app_time / 1000000) << " >   < "
			<< com.str_room(this->app_time / 10000 % 10) << " >   < "
			<< this->app_time % 1000 << " >号	< "
			<< com.str_state(this->app_time / 1000 % 10) << " >" << endl;

		if (choice == STU) {
			return;
		}
	}

	cout << "< " << com.str_day(this->app_time / 100000 % 10) << " >   < "
		<< com.str_period(this->app_time / 1000000) << " >   < "
		<< com.str_room(this->app_time / 10000 % 10) << " >    < "
		<< com.str_state(this->app_time / 1000 % 10) << " >" << endl;
}

void AppTable::set_result(int state)
{
	this->app_state = state;
	int info = this->app_time;
	info = info / 10000 * 10000 + state * 1000 + info % 1000;
	this->app_time = info;
}

void AppTable::add_tea_app(int info)
{
	this->app_time = info;
	this->app_state = 3;
}

void AppTable::add_stu_app(int info)
{
	this->app_time = info;
	this->app_state = info / 1000 % 10;
}

int AppTable::show_appResult()
{
	return this->app_state;
}