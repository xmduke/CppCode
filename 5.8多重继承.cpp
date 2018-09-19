#include<iostream>
#include<string>
using namespace std;
class teacher
{
public:
	teacher(string nam,int a,string t)
	{
		name=nam;
		age=a;
		title=t;
	}
	void display()
	{
		cout<<"name:"<<name<<endl;
		cout<<"age:"<<age<<endl;
		cout<<"title:"<<title<<endl;
	}
protected:
	string name;
	int age;
	string title;
};
class student
{
public:
	student(string nam,char s,float sco)
	{
		name1=nam;
		sex=s;
		score=sco;
	}
	void display1()
	{
		cout<<"name:"<<name1<<endl;
		cout<<"sex:"<<sex<<endl;
		cout<<"score:"<<score<<endl;
	}
protected:
	string name1;
	char sex;
	float score;
};
class graduate:public teacher,public student
{
public:
	graduate(string nam,int a,char s,string t,float sco,float w):teacher(nam,a,t),student(nam,s,sco),wage(w){}
	void show()
	{
	cout<<"name:"<<name<<endl;
	cout<<"age:"<<age<<endl;
	cout<<"sex:"<<sex<<endl;
	cout<<"score:"<<score<<endl;
	cout<<"title:"<<title<<endl;
	cout<<"wage:"<<wage<<endl;
	}
private:
	float wage;
};
int main()
{
	graduate grad1("wang",24,'f',"assisant",89.5,1234.5);
	grad1.show();
	return 0;
}