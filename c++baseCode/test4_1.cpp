#include<iostream>
using namespace std;
class Base
{
public:
	void setx(int i){x=i;}
	int getx(){return x;}
protected:
	int x;
};
class Derived:public Base
{
public:
	void sety(int i){y=i;}
	int gety(){return y;}
	void show(){cout<<"Base::x="<<getx()<<endl;}
public:
	int y;
};
int main()
{
	Derived bb;
	bb.setx(16);
	bb.sety(25);
	bb.show();
	cout<<"Base::x="<<bb.getx()<<endl;
	cout<<"Derived::y="<<bb.y<<endl;
	cout<<"Base::x="<<bb.getx()<<endl;
	cout<<"Derived::y="<<bb.gety()<<endl;
	return 0;
}
