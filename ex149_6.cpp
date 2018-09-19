#include<iostream.h>

class complex
{
public:
	complex(){real=0;imag=0;}
	complex(double r){real=r;imag=0;}
	complex(double r,double i){real=r;imag=i;}
	operator double(){return real;}
//	friend complex operator+(complex c1,complex c2);
	void display();
private:
	double real;
	double imag;
};
/*complex operator+(complex c1,complex c2)
{
	
	return complex(c1.real+c2.real,c1.imag+c2.imag);
}*/
void complex::display()
{
	cout<<"("<<real<<","<<imag<<"i)"<<endl;
}
int main()
{
	complex c1(3,4),c2;
	double d1;
	d1=2.5+c1;
	cout<<d1<<endl;
	c2=complex(d1);
	c2.display();
	return 0;
}