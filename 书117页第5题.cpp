#include <iostream>
using namespace std;
class Student
{
public:
	Student(int, int);
	void max(Student* s);
private:
	int num;
	int scor;
};
Student::Student(int n, int s):num(n),scor(s){}
void Student::max(Student* s)
{
	int i, max_num=0, max_scor=0;
	for(i=0;i<5;++i)
		if((s+i)->scor > max_scor)
		{
			max_scor=(s+i)->scor;  
			max_num=(s+i)->num;
		}
		cout<<"�ɼ�����ߵ�ѧ��Ϊ"<<max_num<< endl;
		cout<<"�ɼ�����ߵĳɼ�Ϊ"<<max_scor<< endl;
}
int main()
{
	Student s[5]= {Student(1, 78), Student(2, 92), Student(4, 81), Student(4, 89), Student(5, 68)};
	Student *p;
	p=&s[0];
	p->max(p); //max������ķ���
	return 0;
}