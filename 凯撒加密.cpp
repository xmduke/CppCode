#include<stdio.h>
int main()
{
	char c;
	printf("ÇëÊäÈëÃ÷ÎÄ:");
	
	while((c=getchar())!='\n')
	{
		if(c>='A'&&c<='Z')
			c='A'+(c-'A'+3)%26;
		else if(c>='a'&&c<='z')
			c='a'+(c-'a'+3)%26;
		
		putchar(c);
	}
	printf("\n");
	
	
	return 0;
}