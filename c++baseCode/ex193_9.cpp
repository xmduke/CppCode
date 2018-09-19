#include<iostream>
#include<string>
using namespace std;
class teacher
{
public:
	teacher(string nam,int a,char s,string tit,string ad,string t);
	void display();
protected:
	string name;
	int age;
	char sex;
	string title;
	string addr;
	string tel;
};

teacher::teacher(string nam,int a,char s,string tit,string ad,string t):name(nam),age(a),sex(s),title(tit),addr(ad),tel(t){}
void teacher::display()
{
	cout<<"name:"<<name<<endl;
	cout<<"age:"<<age<<endl;
	cout<<"sex:"<<sex<<endl;
	cout<<"title:"<<title<<endl;
	cout<<"address:"<<addr<<endl;
	cout<<"tel:"<<tel<<endl;
}
class cadre
{
public:
	cadre(string nam,int a,char s,string p,string ad,string t);
	void display();
protected:
	string name;
	int age;
	char sex;
	string post;
	string addr;
	string tel;
};
cadre::cadre(string nam,int a,char s,string p,string ad,string t):name(nam),age(a),sex(s),post(p),addr(ad),tel(t){}
void cadre::display()
{	cout<<"name:"<<name<<endl;
	cout<<"age:"<<age<<endl;
	cout<<"sex:"<<sex<<endl;
	cout<<"post:"<<post<<endl;
	cout<<"address:"<<addr<<endl;
	cout<<"tel:"<<tel<<endl;
}
class person:public teacher,public cadre
{
public:
	person(string nam,int a,char s,string tit,string p,string ad,string t,float w);
	void show();
private:
	float wage;
};
person::person(string nam,int a,char s,string t,string p,string ad,string tel,float w):teacher(nam,a,s,t,ad,tel),cadre(nam,a,s,p,ad,tel),wage(w){}
void person::show()
{
	teacher::display();
	cout<<"post:"<<cadre::post<<endl;
	cout<<"wages:"<<wage<<endl;
}
int main()
{
	person person1("wang",50,'f',"prof","president","135beijing","61234567",1534.5);
	person1.show();
	return 0;
}