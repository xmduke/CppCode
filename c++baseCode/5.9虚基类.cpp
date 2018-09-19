#include<iostream>
#include<string>
using namespace std;
class person
{
public:
	person(string nam,char s,int a)
	{name=nam;sex=s;age=a;}
protected:
	string name;
	char sex;
	int age;
};

class teacher:virtual public person
{
public:
	teacher(string nam,char s,int a,string t):person(nam,s,a){title=t;}
protected:
	string title;
};
class student:virtual public person
{
public:
	student(string nam,char s,int a,float sco):person(nam,s,a),score(sco){}
protected:
	float score;
};
class graduate:public teacher,public student
{
public:
	graduate(string nam,char s,int a,string t,float sco,float w):
	person(nam,s,a),teacher(nam,s,a,t),student(nam,s,a,sco),wage(w){}
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
	graduate grad1("wang",'f',24,"assistant",89.5,1234.5);
	grad1.show();
	return 0;
}