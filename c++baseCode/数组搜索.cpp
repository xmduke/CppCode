#include<iostream.h>
const int DECLARED_SIZE=20;
void fill_array(int a[],int size,int& number_used);
int search(const int a[],int number_used,int target);
int main()
{
	int arr[DECLARED_SIZE],list_size,target;
	fill_array(arr,DECLARED_SIZE,list_size);
	char ans;
	int result;
	do
	{
		cout<<"Enter a number to search for:";
		cin>>target;
		result=search(arr,list_size,target);
		if(result==-1)
			cout<<target<<"is not on the list.\n";
		else
			cout<<target<<"is stored in array position"<<result<<endl<<"(remember:the first position is 0.)\n";
		cout<<"search again?(y/n followed by return):";
		cin>>ans;
	}while((ans!='n')&&(ans!='N'));
	cout<<"end of program.\n";
	return 0;
}
int search(const int a[],int number_used,int target)
{
	int index=0;
	bool found=false;
	while((!found)&&(index<number_used))
		if(target==a[index])
			found=true;
		else
			index++;
		if(found)
			return index;
		else
			return -1;
}
void fill_array(int a[],int size,int& number_used)
{
	cout<<"enter up to "<<size<<"nonnegative whole number.\n"<<"mark the end of the list with a negative number.\n";
	int next,index=0;
	cin>>next;
	while((next>=0)&&(index<size))
	{
		a[index]=next;
		index++;
		cin>>next;
	}
	number_used=index;
}