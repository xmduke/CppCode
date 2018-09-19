#include<iostream>
#include<cstring>
using namespace std;
class teacher
{
public:
	teacher(int ,char[],char);
	void display();
private:
	int num;
	char name[20];
	char sex;
};
teacher::teacher(int n,char nam[],char x)
{
	num=n;
	strcpy(name,nam);
	sex=x;
}
void teacher::display()
{
	cout<<"num:"<<num<<endl;
	cout<<"name:"<<name<<endl;
	cout<<"sex:"<<sex<<endl;
}
class birthdate
{
public:
	birthdate(int ,int ,int );
	void display();
	void change(int ,int ,int );
private:
	int year;
	int month;
	int day;
};
void birthdate::change(int y,int m,int d)
{
	year=y;
	month=m;
	day=d;
}
birthdate::birthdate(int y,int m,int d)
{
	year=y;
	month=m;
	day=d;
}
void birthdate::display()
{
	cout<<"birthday::"<<day<<"/"<<month<<"/"<<year<<endl;
}
class professor:public teacher
{
public:
	professor(int,char[],char,int,int,int ,float);
	void display();
	void change(int ,int,int);
private:
	float area;
	birthdate birthday;
};

professor::professor(int n,char nam[20],char s,int y,int m,int d,float a):teacher(n,nam,s),birthday(y,m,d),area(a){}

void professor::display()
{
	teacher::display();
	birthday.display();
	cout<<"area:"<<area<<endl;
}
void professor::change(int y,int m,int d)
{
	birthday.change(y,m,d);
}
int main()
{
	professor prof1(3012,"zhang",'f',1993,10,1,12.5);
	cout<<endl<<"the original date:"<<endl;
	prof1.display();
	cout<<endl<<"the new date:"<<endl;
	prof1.change(1996,6,1);
	prof1.display();
	return 0;
}