#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"Student.h"
#include<vector>
#include<iomanip>

using namespace std;

struct Shijian
{
	int xuhao;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
}s;

struct ss
{
	int gonghao;
	string name;
	int count;
	string num;
}ss[50];

vector<Shijian> v_shi;
vector<Shijian>::iterator it1;
vector<Shijian>::iterator it2;
vector<Student> v_stu;
vector<Student>::iterator it;
int jishu = 0;

void begin()
{
	cout << "                   **欢迎进入学生考勤管理系统**                 " << endl
		<< "        **************************************************      " << endl
		<< "        *                                                *      " << endl
		<< "        *                                                *      " << endl
		<< "        *    1、输出每个同学的有效考勤次数及出勤率       *      " << endl
		<< "        *    2、出勤率高于某百分比的学生                 *      " << endl
		<< "        *    3、出勤率低于某百分比的学生                 *      " << endl
		<< "        *    4、某时间段考勤的学生                       *      " << endl
		<< "        *    5、按考勤号查询某同学考勤情况               *      " << endl
		<< "        *    6、按学号查询某同学考勤情况                 *      " << endl
		<< "        *    7、按姓名查询某同学考勤情况                 *      " << endl
		<< "        *    8、退出                                     *      " << endl
		<< "        *                                                *      " << endl
		<< "        *                                                *      " << endl
		<< "        **************************************************      " << endl
		<< "              *****请选择您所需要的信息(1-8)*****                " << endl
		<<endl<<endl<<endl;
}

void clear()//清除脏数据
{
	ifstream in_file("1_attlog.dat", ios::binary);
	if (!in_file){
		cerr << "The file is error.\n";
		exit(-1);
	}
	string str, tmp[10];
	while (getline(in_file, str)){
		int num = 0;
		istringstream ss(str);
		while (ss >> tmp[num++]);
		s.xuhao = std::stoi(tmp[0]);
		s.year = std::stoi(tmp[1].substr(0, 4));
		s.month = std::stoi(tmp[1].substr(5, 7));
		s.day = std::stoi(tmp[1].substr(8, 10));
		s.hour = std::stoi(tmp[2].substr(0, 2));
		s.minute = std::stoi(tmp[2].substr(3, 5));
		s.second = std::stoi(tmp[2].substr(6, 8));
		if (s.xuhao >= 5 && s.xuhao <= 31){
			if ( (s.month == 6 && s.day >= 14 && s.day <= 30) ||
				(s.month == 7 && s.day >= 1 && s.day <= 14)){
				if (s.hour<8||s.hour == 8 && s.minute <= 15 || s.hour == 11 && s.minute >= 25 ||s.hour>11)
					v_shi.push_back(s);
			}
		}
	}
	in_file.close();
	for (it1 = v_shi.begin(); it1 != v_shi.end(); it1++){
		for (it2 = it1 + 1; it2 != v_shi.end();){
			if (it1->xuhao == it2->xuhao&&it1->month == it2->month&&it1->day == it2->day
				&&(it1->hour == it2->hour||it1->hour<8&&it2->hour==8||it1->hour==8&&it2->hour<7
				||it1->hour==11&&it2->hour>11||it1->hour>11&&it2->hour==11)){
				it2 = v_shi.erase(it2);
			}
			else ++it2;
		}
	}
}

void set()//求出出勤次数及出勤率
{
	for (it1 = v_shi.begin(); it1 != v_shi.end(); it1++){
		for (it2 = it1 + 1; it2 != v_shi.end(); it2++){
			if (it1->xuhao==it2->xuhao&&it1->month == it2->month&&it1->day == it2->day){
					for (it = v_stu.begin(); it != v_stu.end(); it++){
						if (it->gonghao == it1->xuhao){
							it->count++;
							break;
						}
					}
				}
			}
		}
	for (it = v_stu.begin(); it != v_stu.end(); it++){
		it->chuqinlv = it->count / 19.0;
	}
	for (it = v_stu.begin(); it != v_stu.end(); it++){
		ss[jishu].name = it->name;
		ss[jishu].num = it->num;
		ss[jishu].count = 0;
		ss[jishu].gonghao = it->gonghao;
		jishu++;
	}
}

void search(int x)
{
	string tmp;
	int temp, day1, day2, month1, month2;
	float percent;
	if (x == 1){
		cout << " 学号              姓名         出勤次数     出勤率" << endl;
		for (it = v_stu.begin(); it != v_stu.end(); it++){
			cout << it->num;
			cout.width(10);
			cout << it->name;
			cout.width(13);
			cout << it->count;
			cout.width(15);
			cout << it->chuqinlv << endl;
		}
		cout << endl << endl << endl;
	}
	else if (x == 2){
		cout << "请输入百分比（以两位小数方式输入）.\n";
		cin >> percent;
		cout << "出勤率高于" << percent << "的人有：" << endl;
		cout << " 学号              姓名         出勤次数     出勤率" << endl;
		for (it = v_stu.begin(); it != v_stu.end(); it++){
			if (it->chuqinlv > percent){
				cout << it->num;
				cout.width(10);
				cout << it->name;
				cout.width(13);
				cout << it->count;
				cout.width(15);
				cout << it->chuqinlv << endl;
			}
		}
		cout << endl << endl << endl;
	}
	else if (x == 3){
		cout << "请输入百分比（以两位小数方式输入）.\n";
		cin >> percent;
		cout << "出勤率低于" << percent << "的人有：" << endl;
		cout << " 学号              姓名         出勤次数     出勤率" << endl;
		for (it = v_stu.begin(); it != v_stu.end(); it++){
			if (it->chuqinlv < percent){
				cout << it->num;
				cout.width(10);
				cout << it->name;
				cout.width(13);
				cout << it->count;
				cout.width(15);
				cout << it->chuqinlv << endl;
			}
		}
		cout << endl << endl << endl;
	}
	else if (x == 4){
		for (int i = 0; i < jishu; i++)
		{
			ss[i].count = 0;
		}
		cout << "请输入时间段（格式形如6 24 7 10，代表6月24日到7月10日）" << endl;
		cin >> month1 >> day1 >> month2 >> day2;
		for (it1 = v_shi.begin(); it1 != v_shi.end(); it1++){
			for (it2 = it1 + 1; it2 != v_shi.end(); it2++){
				if (it1->xuhao == it2->xuhao&&it1->month == it2->month&&it1->day == it2->day){
					if (month1 == 6 && month2 == 6)
					{
						if (it1->day>=day1&&it1->day<=day2){
							for (int i = 0; i < jishu;i++){
								if (ss[i].gonghao == it1->xuhao){
									ss[i].count++;
									break;
								}
							}
						}
					}
					else if (month1 == 7 && month2 == 7)
					{
						if (it1->day >= day1&&it1->day <= day2)
						{
							for (int i = 0; i < jishu; i++){
								if (ss[i].gonghao == it1->xuhao){
									ss[i].count++;
									break;
								}
							}
						}
					}
					else if (month1 == 6 && month2 == 7)
					{
						if (it1->month == 6)
						{
							if (it1->day >= day1)
							{
								for (int i = 0; i < jishu; i++){
									if (ss[i].gonghao == it1->xuhao){
										ss[i].count++;
										break;
									}
								}
							}
						}
						else if (it1->month == 7)
						{
							if (it1->day <= day2)
							{
								for (int i = 0; i < jishu; i++){
									if (ss[i].gonghao == it1->xuhao){
										ss[i].count++;
										break;
									}
								}
							}
						}
					}
				}
			}
		}
		cout << "在" << month1 << "月" << day1 << "日到" << month2 << "月" << day2 << "日打卡的有：\n";
		cout << "    学号           姓名           考勤次数" << endl;
		for (int i = 0; i < jishu; i++)
		{
			cout << ss[i].num;
			cout.width(10);
			cout << ss[i].name;
			cout.width(13);
			cout << ss[i].count << endl;
		}
		cout << endl << endl << endl;
	}
	else if (x == 5)
	{
		cout << "请输入该同学考勤号.\n";
		cin >> temp;
		for (it = v_stu.begin(); it != v_stu.end(); it++)
		{
			if (it->gonghao == temp)
				cout << it->num << " " << it->name
				<< " " << it->count << " " << it->chuqinlv << endl;
		}
		cout << endl << endl << endl;
	}
	else if (x == 6)
	{
		cout << "请输入该同学学号.\n";
		cin >> tmp;
		for (it = v_stu.begin(); it != v_stu.end(); it++)
		{
			if (it->num == tmp)
				cout << it->num << " " << it->name
				<< " " << it->count << " " << it->chuqinlv << endl;
		}
		cout << endl << endl << endl;
	}
	else if (x == 7)
	{
		cout << "请输入该同学姓名.\n";
		cin >> tmp;
		for (it = v_stu.begin(); it != v_stu.end(); it++)
		{
			if (it->name == tmp)
				cout << it->num << " " << it->name
				<< " " << it->count << " " << it->chuqinlv << endl;
		}
		cout << endl << endl << endl;
	}
	else if (x == 8) {
		cout << "退出考勤管理系统，欢迎下次使用！" << endl;
		exit(-1);
	}
	cout << "请继续选择:";
	cin >> temp;
	search(temp);
}

int main()
{
	begin();
	ifstream infile("学生名单.txt");
	if (!infile){
		cerr << "The file is error.\n";
		exit(-1);
	}
	string str, tmp[10];
	while (getline(infile, str)){
		istringstream ss(str);
		int count = 0;
		while (ss >> tmp[count++]);
		v_stu.push_back(Student(stoi(tmp[1]), stoi(tmp[2]), tmp[3], tmp[4]));
	}
	infile.close();
	clear();
	set();
	int x;
	cin >> x;
	search(x);
	return 0;
}