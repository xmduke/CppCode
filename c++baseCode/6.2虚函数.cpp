#include<iostream>
#include<string>
using namespace std;
class student
{
public:
	student(int ,string,float);
	void display();
protected:
	int num;
	string name;
	float score;
};
student::student(int n,string nam,float s)
{
	num=n;
	name=nam;
	score=s;
}
void student::display()
{
	cout<<"num:"<<num<<endl;
	cout<<"name:"<<name<<endl;
	cout<<"score:"<<score<<endl;
	cout<<endl;
}
class graduate:public student
{
public:
	graduate(int ,string,float,float);
	void display();
private:
	float pay;
};
void graduate::display()
{
	cout<<"num:"<<num<<endl;
	cout<<"name:"<<name<<endl;
	cout<<"score:"<<score<<endl;
	cout<<"pay:"<<pay<<endl;
	cout<<endl;
}
graduate::graduate(int n,string nam,float s,float p):student(n,nam,s),pay(p){}
int main()
{
	student stud1(1101,"li",87.5);
	graduate grad1(2001,"wang",98.5,563.5);
	student *pt=&stud1;
	pt->display();
	pt=&grad1;
	pt->display();
	return 0;
}
