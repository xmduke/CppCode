#include<iostream.h>
#include<stdlib.h>
class matrix
{
public:
	void set();
	void display();
	friend matrix operator +(matrix &,matrix &);
private:
	int mat[2][3];
};
void matrix::set()
{
	cout<<"please input the value:"<<endl;
	for(int i=0;i<2;i++)
		for(int j=0;j<3;j++)
			cin>>mat[i][j];
}
void matrix::display()
{
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<mat[i][j]<<" ";
		}
		cout<<endl;
	}
}
matrix operator +(matrix &a,matrix &b)
{
	matrix c;
	for(int i=0;i<2;i++)
		for(int j=0;j<3;j++)
			c.mat[i][j]=a.mat[i][j]+b.mat[i][j];
		return c;
}  
int main() 
{
	matrix a,b,c;
	a.set();
	cout<<"matrix a:"<<endl;
	a.display();
	b.set();
	cout<<"matrix b:"<<endl;
	b.display();
	c=a+b;
	cout<<"matrix c:"<<endl;
	c.display();
	system("pause");
	return 0; 
}  
