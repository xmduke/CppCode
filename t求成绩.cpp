#include<iostream>
using namespace std;
class Student
{
private:
	float score;
	static int count;
	static float total_score;
public:
	void account(float score1)
	{
		score=score1;
		++count;
		total_score=total_score+score;
    }
	static float sum()
	{
		return total_score;
    }
	static float average()
	{
		return total_score/count;
	}
};
int Student::  count=0;
float Student::  total_score=0.0;
int main()
{
	Student s1,s2;
	s1.account(99);
	cout<<Student::sum()<<endl;
	cout<<Student::average()<<endl;
	s2.account(70);
	cout<<Student::sum()<<endl;
	cout<<Student::average()<<endl;
	return 0;
}