#include<iostream.h>
#define PI 3.1415927
class container
{
protected:
	double radius;
public:
	container(double radius1){};
	virtual double surface_area()=0;
	virtual double volume()=0;
};
class cube:public container
{
public:
	cube(double r):container(r)
	{
		radius=r;
	}
	double surface_area()
	{
		return 6*radius*radius;
	}
	double volume()
	{
		return radius*radius*radius;
	}
};
class sphere:public container
{
public:
	sphere(double r):container(r)
	{
		radius=r;
	}
	double surface_area()
	{
		return 4*PI*radius*radius;
	}
	double volume()
	{
		return 4*PI*radius*radius*radius/3;
	}
};
class cylinder:public container
{
protected:
	double height;
public:
	cylinder(double r,double h):container(r)
	{
		radius=r;height=h;
	}
	double surface_area()
	{
		return 2*PI*radius*radius+2*PI*radius*height;
	}
	double volume()
	{
		return PI*radius*radius*height;
	}
};
int main()
{
	cube a(6.0);
	sphere b(5.0);
	cylinder c(5.0,6.0);
	cout<<"������������"<<a.surface_area()<<endl;
	cout<<"�����������"<<a.volume()<<endl;
	cout<<"��������"<<b.surface_area()<<endl;
	cout<<"�������"<<b.volume()<<endl;
	cout<<"Բ����������"<<c.surface_area()<<endl;
	cout<<"Բ���������"<<c.volume()<<endl;
	return 0;
}