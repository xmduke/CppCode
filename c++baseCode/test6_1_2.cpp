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
	cout<<"max('3','7')  is "<<max('3','7')<<endl;//���������ַ����Ƚϵ���3��7��asc||�룬��Ϊ����
	return 0;
}
