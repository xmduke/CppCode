#include<iostream.h>
class Person
{
public:
	void setid(int x){cout<<"�������ţ�"<<endl; cin>>x; id=x;}
	void getid(){cout<<"��ţ�"<<id<<endl;}
	void setname(char y){cout<<"������������"<<endl; cin>>y; name=y;}
	void getname(){cout<<"������"<<name<<endl;}
	void setsex(char z){cout<<"�������Ա�"<<endl; cin>>z; sex=z;}
	void getsex(){cout<<"�Ա�"<<sex<<endl;}
	void setage(int a){cout<<"���������䣺"<<endl; cin>>a; age=a;}
	void getage(){cout<<"���䣺"<<age<<endl;}
private:
	int id;
	char name;
	char sex;
	int age;
};
class Student:public Person
{
public:
	void setlist(char i){cout<<"������ϵ��"<<endl; cin>>i;list=i;}
	void getlist(){cout<<"ϵ��"<<list<<endl;}
	void setgread(int j){cout<<"������ɼ���"<<endl; cin>>j;gread=j;}
	void getgread(){cout<<"�ɼ���"<<gread<<endl;}
private:
	char list;
	int gread;
};
class Teacher:public Person
{
public:
	void setcall(char n){cout<<"������ְ�ƣ�"<<endl; cin>>n;call=n;}
	void getcall(){cout<<"ϵ��"<<call<<endl;}
	void setpartment(char m){cout<<"�����벿�ţ�"<<endl; cin>>m;partment=m;}
	void getpartment(){cout<<"���ţ�"<<partment<<endl;}
private:
	char call;
	char partment;
};
int main()
{
	
	char m=0;
	Student AA;
	cout<<"������ѧ����Ϣ��"<<endl;
	AA.setid(0);
	AA.setname(m);
	AA.setsex(m);
	AA.setage(0);
	AA.setgread(0);
	AA.setlist(m);
	cout<<"ѧ����Ϣ���£�"<<endl;
	AA.getid();
	AA.getname();
	AA.getsex();
	AA.getage();
	AA.getgread();
	AA.getlist();
	Teacher BB;
	cout<<"��������ʦ��Ϣ��"<<endl;
	BB.setid(0);
	BB.setname(m);
	BB.setsex(m);
	BB.setage(0);
	BB.setcall(m);
	BB.setpartment(m);
	cout<<"��ʦ��Ϣ���£�"<<endl;
	BB.getid();
	BB.getname();
	BB.getsex();
	BB.getage();
	BB.getcall();
	BB.getpartment();
	return 0;
}
