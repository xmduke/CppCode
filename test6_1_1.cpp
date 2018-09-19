#include <iostream>
using namespace std;
template<typename  T>
T max (T x,T y)
{ 
	return x>y? x:y;
}
int max(int a,int b)
{
	return a>b? a:b;
}
double max (double  a,double  b)
{
	return a>b? a:b;
}
int  main()
{ 
	cout<<"max('3','7') is "<<max('3','7')<<endl;
	return 0;
}
