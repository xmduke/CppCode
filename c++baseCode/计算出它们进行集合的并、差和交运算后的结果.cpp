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
	cout<< "输入集合元素" << d <<" 个：";
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
		for(int j=0;j<s1.len;j++) //在s1.s[]中选出不相同的
		{
			if(s[i]==s1.s[j]) //选出相同的元素删掉得到s1.s与s不同的元素
			{
				for(;j<s1.len;j++)
					s1.s[j]=s1.s[j+1];
				--s1.len;
			}
		}
	}
	for(int j=0;j<s1.len;j++) // 将s1.s[]中不相同的加在s[]后面 
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
			if(s1.s[i]==s[j]) //选出s与s1.s中相同的元素并且删除掉
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
		for(int j=0;j<len;j++) // 选出相同的元素
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
	cout<< "建立含有几个元素的集合：";
	cin>> n; 
	A1.input(n);
	set B1;
	cout<< "建立含有几个元素的集合：";
	cin>> n; 
	B1.input(n);
	cout<< "两集合的差集（A1 - B1）为：";
	C1=A1-B1;
	C1.disp(); 
	cout<<endl<<endl;
	int p;
	set C3;
	set A3;
	cout<< "建立含有几个元素的集合：";
	cin>>p; 
	A3.input(p);
	set B3;
	cout<< "建立含有几个元素的集合：";
	cin>>p; 
	B3.input(p);
	cout<< "两集合的并集（A3 + B3）为：";
	C3=A3+B3;
	C3.disp(); 
	cout<<endl;
	int m;
	set C2;
	set A2;
	cout<< "建立含有几个元素的集合：";
	cin>>m; 
	A2.input(m);
	set B2;
	cout<< "建立含有几个元素的集合：";
	cin>>m; 
	B2.input(m);
	cout<< "两集合的交集（A2 * B2）为：";
	C2=A2*B2;
	C2.disp(); 
	cout<<endl;
	return 0;
}
