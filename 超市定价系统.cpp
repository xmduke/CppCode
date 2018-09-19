#include<iostream.h>
const double LOW_MARKUP=0.05;
const double HIGH_MARKUP=0.10;
const int THRESHOLD=7;
void introduction();
void get_input(double& cost,int& turnover);
double price(double cost,int turnover);
void give_output(double cost,int turnover,double price);
int main()
{
	double wholesale_cost,retail_price;
	int shelf_time;
	introduction();
	get_input(wholesale_cost,shelf_time);
	retail_price=price(wholesale_cost,shelf_time);
	give_output(wholesale_cost,shelf_time,retail_price);
	return 0;
}
void introduction()
{
	cout<<"this program determines the retail price for\n an item at a Quick-shop supermarket store.\n";
}
void get_input(double& cost,int& turnover)
{
	cout<<"Enter the wholesale cost of item:$";
	cin>>cost;
	cout<<"Enter the expected number of days until mold:";
	cin>>turnover;
}
void give_output(double cost,int turnover,double price)
{
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout<<"wholesale cost=$"<<cost<<endl<<"Expected time until sold="<<turnover<<"days"<<endl<<"retail price =$"<<price<<endl;
}
double price(double cost,int turnover)
{
	if(turnover<=THRESHOLD)
		return (cost+(LOW_MARKUP*cost));
	else
		return (cost+(HIGH_MARKUP*cost));
}
