#include<iostream.h>
int main()
{
	int net_income;
	double tax_bill;
	double five_percent_tax,ten_percent_tax;
	cout<<"Enter net income (rounded to whole dollars) $";
	cin>>net_income;
	if(net_income<=15000)
		tax_bill=0;
	else if ((net_income>15000)&&(net_income<=25000))
		tax_bill=(0.05*(net_income-15000));
	else
	{
		five_percent_tax=0.05*10000;
		ten_percent_tax=0.10*(net_income-25000);
		tax_bill=(five_percent_tax+ten_percent_tax);
	}
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout<<"Net income =$"<<net_income<<endl<<"Tax bill=$"<<tax_bill<<endl;
	return 0;
}