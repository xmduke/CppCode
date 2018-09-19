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
double distance(Location &a, Location &b)   //��Ԫ����
{
    int dx=a.x-b.x;
	int dy=a.y-b.y;
	return sqrt(dx*dx+dy*dy);
}
double Location::distance(Location b)   //��Ա����
{
    int dx=x-b.x;
	int dy=y-b.y;
	return sqrt(dx*dx+dy*dy);
}
void main()
{
	Location A(-10,-20),B(-40,60);
	cout<<"A("<<A.Getx( )<<","<<A.Gety( )<<"),B("<<B.Getx( )<<","<<B.Gety( )<<")"<<endl;
	double d=A.distance(B);  //���ó�Ա����
	cout<<"Distance1= "<<d<<endl;
	cout<<"Distance2= "<<distance(A,B)<<endl;
}   //������Ԫ����
