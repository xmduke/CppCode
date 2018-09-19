#include<iostream.h>
int factorial(int n);
int main()
{	
	int n,x;
	cin>>n;
	x=factorial(n);
	cout<<x;
}
int factorial(int n)
{
	int product=1;
	while (n>0)
	{
		product=n*product;
		n--;
	}
	return product;
}