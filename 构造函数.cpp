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
	cout<<"请输入一个值:";
	x=0;
}
void fun::set()
{
	cin>>x;
	//return x;
}
void fun::print()
{
	cout<<"输入的值为:"<<x<<endl;
}
int main()
{
	fun A;
	A.set();
	A.print();
	//cout<<"输入的值为:"<<<<endl;
	return 0;
}