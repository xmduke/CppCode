#include<iostream>
#include<string>
using namespace std;
void main()
{
	string str[5];
	cout<<"��ֱ�����5���ַ�����"<<endl;
	cout<<"1: ";
	cin>>str[0];
	cout<<endl<<"2: ";
	cin>>str[1];
	cout<<endl<<"3: ";
	cin>>str[2];
	cout<<endl<<"4: ";
	cin>>str[3];
	cout<<endl<<"5: ";
	cin>>str[4]; 
	cout<<endl<<"�����5���ַ����ֱ���:"<<endl;
	cout<<str[0]<<" "<<str[1]<<" "<<str[2]<<" "<<str[3]<<" "<<str[4]<<endl;
	cout<<"��ת���˳��Ϊ:"<<endl; cout<<str[4]<<" "<<str[3]<<" "<<str[2]<<" "<<str[1]<<" "<<str[0]<<endl;
}