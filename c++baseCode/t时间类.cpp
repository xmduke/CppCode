#include<iostream.h>
#include<string>
class Time
{
public:
	Time(int h=0,int m=0,int s=0);
	Time operator+(Time&t2);
	void disptime(){cout << hours << ":" << minutes << ":" << seconds << " ." << endl;}
private:
  int  hours;
  int  minutes;
  int  seconds;
};
Time::Time(int h,int m,int s)
{
	 hours=h;
	 minutes=m;
	 seconds=s;
}
Time Time::operator+(Time&t2)
{
	Time t;
	t.hours=hours+t2.hours;
	t.minutes=minutes+t2.minutes;
	t.seconds=seconds+t2.seconds;
	if(t.seconds>=60)
	{
		t.seconds=t.seconds-60;
		t.minutes=t.minutes+1;
	}
	if(t.minutes>=60)
	{
		t.minutes=t.minutes-60;
		t.hours=t.hours+1;
	}
	return t;
}


int main()
{
	Time  t1(10 ,20,30) ,t2(12,35,40),t3;
	t3=t1+t2;
	cout<<"t1=";
	t1.disptime();
	cout<<"t2=";
	t2.disptime();
	cout<<"t1+t2:"<<" ";
	t3.disptime();
	return 0;
}