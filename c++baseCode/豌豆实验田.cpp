#include<iostream.h>
double est_total(int min_peas,int max_peas,int pod_count);
int main()
{
	int max_count,min_count,pod_count;
	double average_pea,yield;
	cout<<"Enter minimum and maximum number of peas in a pod:";
	cin>>min_count>>max_count;
	cout<<"Enter the number of pods:";
	cin>>pod_count;
	cout<<"Enter the weight of an average pea (in ounces):";
	cin>>average_pea;
	yield=est_total(min_count,max_count,pod_count)*average_pea;
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(3);
	cout<<"min number of peas per pod="<<min_count<<endl<<"max number of peas per pod="<<max_count<<endl<<"pod count="<<pod_count<<endl
	<<"average pea weight="<<average_pea<<"ounces"<<endl<<"estimated average yield="<<yield<<"ounces"<<endl;
	return 0;
}
double est_total(int min_peas,int max_peas,int pod_count)
{
	double average_pea;
	average_pea=(max_peas+min_peas)/2.0;
	return (pod_count * average_pea);
}