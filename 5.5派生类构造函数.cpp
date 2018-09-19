#include<iostream>
#include<string>
using namespace std;
class student
{
public:
	student(int n,string nam,char s)
	{
		num=n;
		name=nam;
		sex=s;
	}
	~student(){}
protected:
	int num;
	string name;
	char sex;
};
class student1:public student
{
public:
	student1(int n,string nam,char s,int a,string ad):student(n,nam,s)
	{
		age=a;
		addr=ad;
	}
	void show()
	{
		cout<<"num:"<<num<<endl;
		cout<<"name:"<<name<<endl;
		cout<<"sex:"<<sex<<endl;
		cout<<"age:"<<age<<endl;
		cout<<"address:"<<addr<<endl<<endl;
	}
	~student1(){}
private:
	int age;
	string addr;
};
int main()
{
	student1 stud1(10010,"wang",'f',19,"115beijing");
	student1 stud2(10011,"zhang",'m',21,"213beijing");
	stud1.show();
	stud2.show();
	return 0;
}