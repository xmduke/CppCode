#include<iostream>
using namespace std;
class complex
{
public:
	complex(){real=0;imag=0;}
	complex(double r,double i){real=r;imag=i;}
	void display();

	double real;
	double imag;
};
complex operator+(complex &c1,complex &c2)
{
	complex c;
	c.real=c1.real+c2.real;
    c.imag=c1.imag+c2.imag;
	return c;
	
}
void complex::display()
{
	cout<<"("<<real<<","<<imag<<"i)"<<endl;
}
int main()
{
	complex c1(3,4),c2(5,-10),c3;
	c3=operator+(c1,c2);
	cout<<"c1=";c1.display();
	cout<<"c2=";c2.display();
	cout<<"c3=";c3.display();
	return 0;
}