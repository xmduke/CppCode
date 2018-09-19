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
		cout<<"num:"<<num<<endl;
		cout<<"name:"<<name<<endl;
	}
protected:
	int num;
	string name;
};
class student1:public student
{
public:
	student1(int n,string nam,int a):student(n,nam)
	{age=a;}
	void show()
	{
		display();
		cout<<"age:"<<age<<endl;
	}
private:
	int age;
};
class student2:public student1
{
public:
	student2(int n,string nam,int a,int s):student1(n,nam,a)
	{score=s;}
	void show_all()
	{
		show();
		cout<<"score:"<<score<<endl;
	}
private:
	int score;
};
int main()
{
	student2 stud(10010,"li",17,89);
	stud.show_all();
	return 0;
}