#include<iostream.h>

class shape
{
public:
	virtual double area()const{return 0.0;}
	virtual double volume()const{return 0.0;}
	virtual void shapename()const=0;
};
class point:public shape
{
public:
	point(double=0,double=0);
	void setpoint(double ,double);
	double getx()const{return x;}
	double gety()const{return y;}
	virtual void shapename()const{cout<<"point:";}
	friend ostream&operator<<(ostream &,const point &);
protected:
	double x,y;
};
point::point(double a,double b)
{x=a;y=b;}
void point::setpoint(double a,double b)
{
	x=a;
	y=b;
}
ostream&operator<<(ostream &output,const point &p)
{
	output<<"["<<p.x<<","<<p.y<<"]";
	return output;
}
class circle:public point
{
public:
	circle(double x=0,double y=0,double r=0):point(x,y),radius(r){}
	void setradius(double r){radius=r;}
	double getradius()const;
	virtual double area()const;
	virtual void shapename()const{cout<<"circle:";}
	friend ostream &operator<<(ostream &,const circle &);
protected:
	double radius;
};
/*circle::circle(double x,double y,double r)
void circle::setradius(double r)*/
double circle::getradius()const{return radius;}
double circle::area()const{return 3.14159*radius*radius;}
ostream &operator<<(ostream &output,const circle &c)
{
	output<<"["<<c.x<<","<<c.y<<"],r="<<c.radius;
	return output;
}
class cylinder:public circle
{
public:
	cylinder(double x=0,double y=0,double r=0,double h=0);
	void setheight(double);
	virtual double area()const;
	virtual double volume()const;
	virtual void shapename()const{cout<<"cylinder:";}
	friend ostream& operator<<(ostream&,const cylinder&);
protected:
	double height;
};
cylinder::cylinder(double a,double b,double r,double h):circle(a,b,r),height(h){}
void cylinder::setheight(double h){height=h;}
double cylinder::area()const{return 2*circle::area()+2*3.14159*radius*height;}
double cylinder::volume()const{return circle::area()*height;}
ostream& operator<<(ostream &output,const cylinder &cy)
{
	output<<"["<<cy.x<<","<<cy.y<<"],r="<<cy.radius<<",h="<<cy.height;
	return output;
}


int main()
{
	point point1(3.2,4.5);
	circle circle1(2.4,1.2,5.6);
	cylinder cylinder1(3.5,6.4,5.2,10.5);
	point1.shapename();
	cout<<point1<<endl;
	circle1.shapename();
	cout<<circle1<<endl;
	cylinder1.shapename();
	cout<<cylinder1<<endl;
	shape *pt;
	pt=&point1;
	pt->shapename();
	cout<<"x="<<point1.getx()<<",y="<<point1.gety()<<endl<<"area="<<pt->area()<<endl<<"volume="<<pt->volume()<<endl;
	pt=&circle1;
	pt->shapename();
	cout<<"x="<<circle1.getx()<<",y="<<circle1.gety()<<endl<<"area="<<pt->area()<<endl<<"volume="<<pt->volume()<<endl;
	pt=&cylinder1;
	pt->shapename();
	cout<<"x="<<cylinder1.getx()<<",y="<<cylinder1.gety()<<endl<<"area="<<pt->area()<<endl<<"volume="<<pt->volume()<<endl;
	return 0;
}







