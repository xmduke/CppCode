#include<iostream.h>
const int MAX = 50;


class set
{
public:
	set::set();
    void set::input(int d);
    int set::length();
    int set::getd(int i);
    void set::disp();
    set set::operator+(set s1);
    set set::operator-(set s1);
    set set::operator*(set s1);
	set set::operator=(set s1);
protected:
	int len;
    int s[MAX];
};
set::set()
{
	len = 0;
}
void set::input(int d)
{
	len = d;
	cout<< "���뼯��Ԫ��" << d <<" ����";
	for(int i=0;i<d;i++)
		cin>>s[i];
}
int set::length()
{
	int n=0;
	while(s[n]!='\0')
	{
		n++;
	}
	return n;
}
int set::getd(int i)
{
	return 0;
}
void set::disp()
{
	for(int i=0;i<len;i++)
		cout<<s[i]<<" ";
}
set set::operator+(set s1)
{
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<s1.len;j++) //��s1.s[]��ѡ������ͬ��
		{
			if(s[i]==s1.s[j]) //ѡ����ͬ��Ԫ��ɾ���õ�s1.s��s��ͬ��Ԫ��
			{
				for(;j<s1.len;j++)
					s1.s[j]=s1.s[j+1];
				--s1.len;
			}
		}
	}
	for(int j=0;j<s1.len;j++) // ��s1.s[]�в���ͬ�ļ���s[]���� 
	{
		s[len]=s1.s[j];
		len++;
	}
	s[len+s1.len]='\0';
	return *this;
}
set set::operator-(set s1)
{
	int t;
	for (int i=0;i<s1.len;i++)
	{
		for(int j=0;j<len;j++)
		{
			if(s1.s[i]==s[j]) //ѡ��s��s1.s����ͬ��Ԫ�ز���ɾ����
			{
				t=j; 
				for(;t<len;t++)
					s[t]=s[t+1];
				--len;
			}
		}
	}
	return *this;
}
set set::operator*(set s1)
{
	int m[MAX];
	int l = 0;
	for (int i=0;i<s1.len;i++)
	{
		for(int j=0;j<len;j++) // ѡ����ͬ��Ԫ��
		{ 
			if(s1.s[i]==s[j])
			{
				m[l] = s[j];
				l++;
			}
		}
	}
	for (i=0;i<l;i++)
		s[i]=m[i];
	s[l] ='\0';
	len = l;
	return *this;
}
set set::operator=(set s1)
{
	for(int i=0;i<s1.length();i++)
		s[i] = s1.s[i];
	len =s1.len;
	return *this;
}
int main()
{
	int n;
	set C1;
	set A1;
	cout<< "�������м���Ԫ�صļ��ϣ�";
	cin>> n; 
	A1.input(n);
	set B1;
	cout<< "�������м���Ԫ�صļ��ϣ�";
	cin>> n; 
	B1.input(n);
	cout<< "�����ϵĲ��A1 - B1��Ϊ��";
	C1=A1-B1;
	C1.disp(); 
	cout<<endl<<endl;
	int p;
	set C3;
	set A3;
	cout<< "�������м���Ԫ�صļ��ϣ�";
	cin>>p; 
	A3.input(p);
	set B3;
	cout<< "�������м���Ԫ�صļ��ϣ�";
	cin>>p; 
	B3.input(p);
	cout<< "�����ϵĲ�����A3 + B3��Ϊ��";
	C3=A3+B3;
	C3.disp(); 
	cout<<endl;
	int m;
	set C2;
	set A2;
	cout<< "�������м���Ԫ�صļ��ϣ�";
	cin>>m; 
	A2.input(m);
	set B2;
	cout<< "�������м���Ԫ�صļ��ϣ�";
	cin>>m; 
	B2.input(m);
	cout<< "�����ϵĽ�����A2 * B2��Ϊ��";
	C2=A2*B2;
	C2.disp(); 
	cout<<endl;
	return 0;
}
