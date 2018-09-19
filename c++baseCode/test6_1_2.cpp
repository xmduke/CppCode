#include <iostream>
using namespace std;
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
	cout<<"max('3','7')  is "<<max('3','7')<<endl;//单引号是字符，比较的是3和7的asc||码，其为整型
	return 0;
}
