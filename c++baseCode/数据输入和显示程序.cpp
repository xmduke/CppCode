#include<iostream.h>
class Person
{
public:
	void setid(int x){cout<<"请输入编号："<<endl; cin>>x; id=x;}
	void getid(){cout<<"编号："<<id<<endl;}
	void setname(char y){cout<<"请输入姓名："<<endl; cin>>y; name=y;}
	void getname(){cout<<"姓名："<<name<<endl;}
	void setsex(char z){cout<<"请输入性别："<<endl; cin>>z; sex=z;}
	void getsex(){cout<<"性别："<<sex<<endl;}
	void setage(int a){cout<<"请输入年龄："<<endl; cin>>a; age=a;}
	void getage(){cout<<"年龄："<<age<<endl;}
private:
	int id;
	char name;
	char sex;
	int age;
};
class Student:public Person
{
public:
	void setlist(char i){cout<<"请输入系别："<<endl; cin>>i;list=i;}
	void getlist(){cout<<"系别："<<list<<endl;}
	void setgread(int j){cout<<"请输入成绩："<<endl; cin>>j;gread=j;}
	void getgread(){cout<<"成绩："<<gread<<endl;}
private:
	char list;
	int gread;
};
class Teacher:public Person
{
public:
	void setcall(char n){cout<<"请输入职称："<<endl; cin>>n;call=n;}
	void getcall(){cout<<"系别："<<call<<endl;}
	void setpartment(char m){cout<<"请输入部门："<<endl; cin>>m;partment=m;}
	void getpartment(){cout<<"部门："<<partment<<endl;}
private:
	char call;
	char partment;
};
int main()
{
	
	char m=0;
	Student AA;
	cout<<"请输入学生信息："<<endl;
	AA.setid(0);
	AA.setname(m);
	AA.setsex(m);
	AA.setage(0);
	AA.setgread(0);
	AA.setlist(m);
	cout<<"学生信息如下："<<endl;
	AA.getid();
	AA.getname();
	AA.getsex();
	AA.getage();
	AA.getgread();
	AA.getlist();
	Teacher BB;
	cout<<"请输入老师信息："<<endl;
	BB.setid(0);
	BB.setname(m);
	BB.setsex(m);
	BB.setage(0);
	BB.setcall(m);
	BB.setpartment(m);
	cout<<"老师信息如下："<<endl;
	BB.getid();
	BB.getname();
	BB.getsex();
	BB.getage();
	BB.getcall();
	BB.getpartment();
	return 0;
}
