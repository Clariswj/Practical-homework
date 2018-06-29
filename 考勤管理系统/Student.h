#include<string>

using namespace std;

class Student
{
private:
	int gonghao;
	int jihao;
	string num;
	string name;
	int count;//出勤次数
	float chuqinlv;//出勤率
public:
	Student(int t_gonghao,int t_jihao,string t_num,string t_name);
	friend void set();
	friend void search(int x);
};

Student::Student(int t_gonghao, int t_jihao, string t_num, string t_name)
{
	gonghao = t_gonghao;
	jihao = t_gonghao;
	num = t_num;
	name = t_name;
	count = 0;
	chuqinlv = 0;
}

