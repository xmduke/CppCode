#include<iostream>
#include<string>
using namespace std;
class student
{
public:
	student(int ,string ,float);
	void display();
private:
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
	cout<<endl<<"num:"<<num<<endl;
	cout<<"name:"<<name<<endl;
	cout<<"score:"<<score<<endl;
}
class graduate:public student
{
public:
	graduate(int ,string ,float ,float);
	void display();
private:
	float pay;
};
graduate::graduate(int n,string nam,float s,float p):student(n,nam,s),pay(p){}
void graduate::display()
{
	student::display();
	cout<<"pay="<<pay<<endl;
}
int main()
{
	student stud1(1001,"li",87.5);
	graduate grad1(2001,"wang",98.5,563.5);
	student *pt=&stud1;
	pt->display();
	pt=&grad1;
	pt->display();
	return 0;
}