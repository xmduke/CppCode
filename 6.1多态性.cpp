#include<iostream.h>
class point
{
public:
	point(double x=0,double y=0);
	void setpoint(double ,double);
	double getx()const{return x;}
	double gety()const{return y;}
	friend ostream &operator<<(ostream &,const point &);
protected:
	double x,y;
};
point::point(double a,double b)
{x=a;y=b;}
void point::setpoint(double a,double b)
{x=a;y=b;}
ostream &operator<<(ostream &output,const point &p)
{
	output<<"["<<p.x<<","<<p.y<<"]"<<endl;
	return output;
}
class circle:public point
{
public:
	circle(double x=0,double y=0,double r=0);
	void setradius(double);
	double getradius()const;
	double area()const;
	friend ostream &operator<<(ostream &,const circle &);
private:
	double radius;
};
circle::circle(double a,double b,double r):point(a,b),radius(r){}
void circle::setradius(double r)
{
	radius=r;
}
double circle::getradius()const{return radius;}
double circle::area()const{return 3.14159*radius*radius;}
ostream &operator<<(ostream &output,const circle &c)
{
	output<<"center=["<<c.x<<","<<c.y<<"],r="<<c.radius<<",area="<<c.area()<<endl;
	return output;
}
int main()
{
	circle c(3.5,6.4,5.2);
	cout<<"original circle:\nx="<<c.getx()<<",y"<<c.gety()<<",r="<<c.getradius()<<",area="<<c.area()<<endl;
	c.setradius(7.5);
	c.setpoint(5,5);
	cout<<"new circle:\n"<<c;
	point &pref=c;
	cout<<"pref:"<<pref;
	return 0;
}