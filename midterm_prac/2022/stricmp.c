#include <stdio.h>
#include <ctype.h>

int stricmp_p(char *dst, char *src) {

	int result=0;

	while(*dst != '\0' || *src != '\0') {
		char c1 = tolower(*dst);
		char c2 = tolower(*src);

		if (c1 != c2) {
			result =  c1 - c2;
			break;
		}
		dst++; src++;
	}	
	
	if(result < 0) return -1;
	else if(result > 0) return 1;
	else return 0;
}


void
main()
{
        char str1[] = "Hello";
        char str2[] = "hello";
        char str3[] = "World!";


        printf("%d : %d\n", stricmp_p(str1, str2), stricmp_p(str1, str3));
}
