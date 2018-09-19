#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
class student
{
public:
 student(int no,string nam,char s,float sc){num=no;name=nam;sex=s;score=sc;}
 int  get_num();
 string get_name();
 char get_sex();
 void outputs();
private:
 int num;
 string name;
 char sex;
 float score;
};
class teacher
{
public:
 teacher(){}
 teacher(student&);
 teacher(int tno,string tnam,char ts,float p):tnum(tno),tname(tnam),tsex(ts),pay(p){}
 void display();
private:
 int tnum;
 string tname;
 char tsex;
 float pay;
};
void teacher::display()
{
 cout<<setw(8)<<"Type"<<setw(6)<<"num"<<setw(6)<<"name"<<setw(6)<<"sex"<<setw(6)<<"pay"<<endl;
 cout<<setw(8)<<"Teacher"<<setw(6)<<tnum<<setw(6)<<tname<<setw(6)<<tsex<<setw(6)<<pay<<endl;
}
teacher::teacher(student &stud)
{
 tnum=stud.get_num();
 tname=stud.get_name();
 tsex=stud.get_sex();
 pay=2500;
}
int  student::get_num()
{
 return num;
}
string student::get_name()
{
 return name;
}
char student::get_sex()
{
 return sex;
}
void student::outputs()
{
 cout<<setw(8)<<"Type"<<setw(6)<<"num"<<setw(6)<<"name"<<setw(6)<<"sex"<<setw(6)<<"score"<<endl;
 cout<<setw(8)<<"Student"<<setw(6)<<num<<setw(6)<<name<<setw(6)<<sex<<setw(6)<<score<<endl;
}

int main()
{
 student stud1(1001,"zhang",'m',98);
 teacher tech1(1003,"wang",'f',2000),tech2;
 tech2=teacher(stud1);

 stud1.outputs();
tech1.display();
 tech2.display();
 return 0;
}

