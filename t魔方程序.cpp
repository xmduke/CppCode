#include<iostream>
using namespace std;
class magic
{
	public:
		void getdata();
		void setfirstmagic();
		void generatemagic();
		void printmagic();
	private: 
		int m[4][4]; 
		int step; 
		int first; 
		int sum;
};
void magic::getdata()
{
	cin>>first>>step>>sum;
}
void magic::setfirstmagic()
{
	int temp=first;
	for(int i=0;i<4;i++)
	{
		for(int n=0;n<4;n++)
		{
            m[i][n]=temp;
			temp+=step;
		}
	}
} 
void magic::generatemagic()
{
	for(int i=0,int n=0;i<4,n<4;i++,n++)
	{
		m[i][i]=sum-m[i][i];
	}
	for(i=0, n=3;i<4;i++,n--)
	{
		m[i][n]=sum-m[i][n];
	}
}
void magic::printmagic()
{
	for(int i=0;i<4;i++)
	{
		for(int n=0;n<4;n++)
		{
			cout<<m[i][n]<<" ";
		}
		cout<<"\n";
	}
}
int main()
{
	magic square;
	cout<< "初始魔方：\n";
	square.getdata();
	square.setfirstmagic();
	square.printmagic();
	cout << "生成最终魔方：\n";
	square.generatemagic();
	square.printmagic();
	system("pause");
	return 0;
}