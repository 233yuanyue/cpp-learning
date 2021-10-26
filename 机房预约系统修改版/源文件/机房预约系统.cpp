#include<iostream>
using namespace std;
#include"AppointmentSystem.h"

/*相关需求：
一、使用人员简介：
1、学生：申请使用机房
2、教师：审核学生的预约申请
3、管理员：给教师和学生创建账号，初始用户名和密码111,111

二、机房简介：
1、共有6间
2、容纳人员分别为：50,50，50,100,100,200

三、申请简介：
1、申请信息每周刷新，由管理员操作
2、学生可以预约一周内的机房使用，预约时间为：周一至周五，时间段为上午两节，下午两节与晚上一节
3、教师负责审核教室的使用

四、具体需求：
1、登录身份：教师(职工号，密码)
学生(学号、密码)

隐藏身份：管理员(特定账号与密码)

2、学生端功能：预约，查看预约状态，取消预约、退出登录

3、教师端功能：查看预约信息和预约状态，进行预约审核，申请机房使用，退出登录

4、管理员端功能：添加学生或教师账号，查看机房信息，查看教师或学生账号信息，清空预约状态，退出登录*/

//重定义问题和未识别符号的问题可以：
//1、移除问题文件(cpp或h)再重新添加
//2、删除函数再重新添加

int main()
{
	AppointmentSystem appsys;
	while (true) {
		appsys.show_sign_in_menu();
		cout << "请选择登录方式：" << endl;
		int select_frist = 0;
		cin >> select_frist;

		switch (select_frist)
		{
		case 1:
			appsys.sign_in(true);
			break;
		case 2:
			appsys.sign_in(false);
			break;
		default:
			appsys.exit_system();
			break;
		}
	}
	system("pause");
	return 0;
}