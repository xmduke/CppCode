#include<iostream>
using namespace std;
class students
{
public:
	students(int x,int y);
	void print();
private:
	int num;
	int gread;
};
students::students(int x,int y)
{
	num=x;
	gread=y;
}
void students::print()
{
	cout<<"Ñ§ºÅ£º"<<num<<"  "<<"³É¼¨£º"<<gread<<endl;
}
int main()
{
	students *pt;
	students a[5]={
			students(01,98),
			students(02,97),
			students(03,96),
			students(04,95),
			students(05,94)};
	pt=a;
	for(int i=0;i<5;i=i+2)
	{
		
		pt->print();
		pt=pt+2;
	}
	return 0;
}
