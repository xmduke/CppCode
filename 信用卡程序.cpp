#include<iostream.h>
int main()
{
	double balance=50.00;
	int count=0;
	cout<<"this program tells you how long it takes\n"<<"to accumulate a debt of $100,starting wuth\n"<<"an initial balance of $50 owed.\n"<<"the interest rate is 2% per month.\n";
	while(balance<100.00)
	{
		balance=balance+0.02*balance;
		count++;
	}
	cout<<"after"<<count<<"month,\n";
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout<<"your balnace due will be $"<<balance<<endl;
	return 0;
}
