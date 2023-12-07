#include<stdio.h>
#include<string.h>

void del (char *str, char c)
{
	int len = strlen(str);
	int k=0;
	
	for(int i=0; i < len; i++) {
		if(str[i] != c) {
			str[k] = str[i];
			k++;	
		}
	}

	str[k] = '\0';
}

void
main()
{
	char str[20] = "Hello";
	del(str,'l');
	puts(str);
}
