#include <iostream.h>
//using namespace std;
class Complex
{
public:
 Complex(double r=0,double i=0):real(r),imag(i)
 {

 };
 friend Complex operator +(Complex &c1,Complex &c2);
 friend Complex operator +(Complex &c,double i);
 friend Complex operator +(double i,Complex &c);
 friend ostream& operator << (ostream&,Complex&); //声明重载运算符“<<”
 friend istream& operator >> (istream&,Complex&); //声明重载运算符“>>”
private:
 double real;
 double imag;
};
Complex operator +(Complex &c1,Complex &c2)
{
 return Complex(c1.real+c2.real,c1.imag+c2.imag);
}
Complex operator +(Complex &c,double i)
{
 return Complex(i+c.real,c.imag);
}
Complex operator +(double i,Complex &c)
{
 return Complex(i+c.real,c.imag);
}
ostream& operator << (ostream& output,Complex& c) //定义重载运算符“<<”
{
 output<<"("<<c.real<<"+"<<c.imag<<"i)";
 return output;
}
istream& operator >> (istream& input,Complex& c)  //定义重载运算符“>>”
{
 cout<<"input real part and imaginary part of complex number:";
 input>>c.real>>c.imag;
 return input;
}
int main( )
{
 Complex c1(3,4),c2(3,2),c3,c4,c5;
 c3=c1+c2;
 c4=5+c2;
 c5=c1+5;
 cout<<"c3="<<c3<<endl;
 cout<<"c4="<<c4<<endl;
 cout<<"c5="<<c5<<endl;
 return 0;
}

