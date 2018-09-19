#include<iostream>
#include<string>
using namespace std;
class student
{
public:
	void get_value()
	{cin>>num>>name>>sex;}
	void display()
	{
		cout<<"num:"<<num<<endl;
		cout<<"name:"<<name<<endl;
		cout<<"sex:"<<sex<<endl;
	}
private:
	int num;
	string name;
	char sex;
};
class student1:protected student
{
public:
	void display_1()
	{
		display();
		cout<<"age:"<<age<<endl;
		cout<<"address:"<<addr<<endl;
	}
	void get_value1()
	{
		get_value();
		cin>>age>>addr;
	}
private:
	int age;
	string addr;
};
int main()
{
	student1 stud;
	stud.get_value1();
	stud.display_1();
	return 0;

}