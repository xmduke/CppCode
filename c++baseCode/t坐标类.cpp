#include<iostream.h>
#include<math.h>
class Location 
{
private:
	int x,y;
public:
	Location(int i, int j):x(i),y(j) {}
	int Getx( ) {return x;}
	int Gety( ) {return y;}
	double distance(Location b);
	friend double distance(Location &a, Location &b);
};
double distance(Location &a, Location &b)   //友元函数
{
    int dx=a.x-b.x;
	int dy=a.y-b.y;
	return sqrt(dx*dx+dy*dy);
}
double Location::distance(Location b)   //成员函数
{
    int dx=x-b.x;
	int dy=y-b.y;
	return sqrt(dx*dx+dy*dy);
}
void main()
{
	Location A(-10,-20),B(-40,60);
	cout<<"A("<<A.Getx( )<<","<<A.Gety( )<<"),B("<<B.Getx( )<<","<<B.Gety( )<<")"<<endl;
	double d=A.distance(B);  //调用成员函数
	cout<<"Distance1= "<<d<<endl;
	cout<<"Distance2= "<<distance(A,B)<<endl;
}   //调用友元函数
