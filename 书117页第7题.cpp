#include<iostream>
using namespace std;
class Student
{
public:
	const Student(int n,float s):num(n),score(s){}
	void change(int n,float s)const{/*num=n;score=s;*/}
	void display()const{cout<<num<<" "<<score<<endl;}
private:
	int num;
	float score;
};
/*int main()
{	
	const Student stud(101,78.5);
	stud.change(101,78.5);
	stud.display();
	return 0;
}*/
int main()
{
	Student stud(101,78.5);
//	const Student *p=&stud;
	Student *const p=&stud;
	p->display();
	p->change(101,80.5);
	p->display();
	return 0;
}