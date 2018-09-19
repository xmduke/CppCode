#include<iostream>
using namespace std;
class volume
{
public:
	int value();
	void set();
	void print();
private:
	int length;
	int width;
	int height;
};

void volume::set()
{
	cin>>length>>width>>height;
}
int volume::value()
{
	return length*width*height;
}
void volume::print()
{
	cout<<"其体积为:"<<value()<<endl;
}
int main()
{
	volume A[3];
	for(int i=0;i<3;i++)
	{
		cout<<"请输入A"<<i+1<<"的长,宽,高:";
		A[i].set();
		A[i].value();
		A[i].print();
	}
	return 0;
}
