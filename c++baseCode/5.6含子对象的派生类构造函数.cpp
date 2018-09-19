#include<iostream>
#include<string>
using namespace std;
class student
{
public:
	student(int n,string nam)
	{
		num=n;
		name=nam;
	}
	void display()
	{
		cout<<"num:"<<num<<endl<<"name:"<<name<<endl;
	}
protected:
	int num;
	string name;
};
class student1:public student
{
public:
	student1(int n,string nam,int n1,string nam1,int a,string ad):student(n,nam),monitor(n1,nam1)
	{
		age=a;
		addr=ad;
	}
	void show()
	{
		cout<<"this student is:"<<endl;
		display();
		cout<<"age:"<<age<<endl;
		cout<<"address:"<<addr<<endl<<endl;
	}
	void show_monitor()
	{
		cout<<endl<<"class monitor is:"<<endl;
		monitor.display();
	}
private:
	student monitor;
	int age;
	string addr;
};
int main ()
{
	student1 stud1(10010,"wang",10001,"li",19,"115beijing");
	stud1.show();
	stud1.show_monitor();
	return 0;
}