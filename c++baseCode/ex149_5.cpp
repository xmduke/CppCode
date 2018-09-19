#include<iostream.h>
#include<stdlib.h>
class matrix
{
public:
	friend ostream& operator << (ostream&,matrix&); //���������������<<��
	friend istream& operator >> (istream&,matrix&); //���������������>>��
	friend matrix operator +(matrix &,matrix &);
private:
	int mat[2][3];
};
ostream& operator << (ostream& output,matrix& c) //���������������<<��
{
	for(int i=0;i<=1;i++)
	{
		for(int j=0;j<=2;j++)
			output<<c.mat[i][j]<<" ";
		cout<<endl;
	}
	return output;
}
istream& operator >> (istream& input,matrix& c)  //���������������>>��
{
	for(int i=0;i<=1;i++)
	{
		for(int j=0;j<=2;j++)
			input>>c.mat[i][j];
	}
	return input;
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
	cout<<"please input matrix a:\n";
	cin>>a;
	cout<<"matrix a:"<<endl;
	cout<<a;
	cout<<"please input matrix b:\n";
	cin>>b;
	cout<<"matrix b:"<<endl;
	cout<<b;
	c=a+b;
	cout<<"matrix c:"<<endl;
	cout<<c;
	system("pause");
	return 0; 
}  
