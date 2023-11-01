#include <stdio.h>

/*
 * String length pointer
 * If the value is NULL, break.
 * increase the pointer by 1 and increase len value by 1.
 * The while statement ends and the length is returned. 
 */
int strlen_p(char *str) {
	int len=0;
	
	while(*str++) {
		len++;
	}
	return len;
}

/*
 * String length array
 * If the value is '\0', break.
 * increase the array by 1 and increase i value by 1.
 * the while statement ends and the length is returned.
 */
int strlen_a(char str[]) {
	int i;
	
	for (i=0; str[i]!='\0'; i++);
	return i;
}

/*
 * String copy pointer
 * If the value is NULL, break
 * Substitute the *src with the value of 1 to the *dst with the value of 1. 
 */
void strcpy_p(char *dst, char *src) {
	while(*src) {
		*dst++ = *src++;
	}
	*dst = *src;
}

/*
 * String copy array
 * If the value is NULL, break
 * Subsititute src[i] into dst[i]
 * increase i by 1.
 */
void strcpy_a(char dst[], char src[]) {
	int i;
	
	for(i = 0; src[i]!='\0'; i++)
		dst[i] = src[i];
	dst[i] = src[i];
}

/*
 * Put src after dst. pointer
 * Until dst pointer points to NULL
 * Put the src.
 */
void strcat_p(char *dst, char *src) {
	while(*dst++)
		;
	dst--;
	while(*src) {
		*dst++ = *src++;
	}
	*dst = *src;
}

/*
 * Put src after dst. array
 * Until dst array points to NULL
 * Put the src.
 */
void strcat_a(char dst[], char src[]) {
	int i, j;
	
	for (i = 0 ; dst[i] != '\0' ; i++)
	;
	for (j = 0 ; src[j] != '\0' ; j++)
		dst[i+j] = src[j];
	dst[i+j] = src[j];
}


/* 
 * String comparison pointer
 * If *dst and *src are not the same
 * Return *dst - *src
 */
int strcmp_p(char *dst, char *src) {
	while(*dst != '\0' || *src != '\0') {
		if (*dst != *src)
			return *dst - *src;
		dst++; src++;
	}	
	return 0;
}

/* 
 * String comparison array
 * If dst[i] and src[i] are not the same
 * Return dst[i] - src[i]
 */
int strcmp_a(char dst[], char src[]) {
        int i=0;
        while(dst[i] != '\0' || src[i] != '\0') {
		if (dst[i] != src[i]) 
                	return dst[i] - src[i];
	       	i++;
        }
        return 0;
}


int main()
{
	int	len1, len2;
	char	str1[20], str2[20];

	len1 = strlen_p("Hello");
	len2 = strlen_a("Hello");
	printf("strlen: p=%d, a=%d\n", len1, len2);

	strcpy_p(str1, "Hello");
	strcpy_a(str2, "Hello");
	printf("strcpy: p=%s, a=%s\n", str1, str2);

	strcat_p(str1, ", World!");
	strcat_a(str2, ", World!");
	printf("strcat: p=%s, a=%s\n", str1, str2);

	strcpy_p(str1, "abc");
        strcpy_a(str2, "abcd");
	int result;

	// strcmp_p and strcmp_a do the same machanism
       	if(strcmp_p(str1, str2) == strcmp_a(str1, str2)) {
	       result = strcmp_p(str1, str2);

		printf("str1: %s, str2: %s\nstrcmp: ", str1, str2);
		if (result == 0)
		        printf("Strings are equal.\n");
		else if (result < 0)
			printf("str1 is less than str2.\n");
		else
		        printf("str1 is greater than str2.\n");
	       	}
	// error
       	else
	       printf("strcmp_p != strcmp_a");
	
}

