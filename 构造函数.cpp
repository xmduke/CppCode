#include<iostream>
using namespace std;
class fun
{
public:
	fun();
	void set();
	void print();
private:
	int x;
};
fun::fun()
{
	cout<<"������һ��ֵ:";
	x=0;
}
void fun::set()
{
	cin>>x;
	//return x;
}
void fun::print()
{
	cout<<"�����ֵΪ:"<<x<<endl;
}
int main()
{
	fun A;
	A.set();
	A.print();
	//cout<<"�����ֵΪ:"<<<<endl;
	return 0;
}