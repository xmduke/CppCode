#include<iostream>
void initialize_screen();
double celsius(double fahrenheit);
void show_results(double f_degrees,double c_degrees);
int main()
{
	using namespace std;
	double f_temperature,c_temperature;
	initialize_screen();
	cout<<"I will convert a Fahrenheit temperature"<<"to celsius.\n"<<"Enter a temperature in Fahrenheit:";
	cin>>f_temperature;
	c_temperature=celsius(f_temperature);
	show_results(f_temperature,c_temperature);
	return 0;
}
void initialize_screen()
{
	using namespace std;
	cout<<endl;
	return ;
}
double celsius(double fahrenheit)
{
	return ((5.0/9.0)*(fahrenheit-32));
}
void show_results(double f_degrees,double c_degrees)
{
	using namespace std;
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(1);
	cout<<f_degrees<<"degrees Fahrenheit is equivalent to\n"<<c_degrees<<"degrees celsius.\n";
	
}