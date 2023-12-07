#include<stdio.h>

void strupper(char str[]) {

	for (int i=0; str[i]; i++) {
		if(str[i]>='a' && str[i]<='z') str[i]+=('A'-'a');
	}
}

int main() {
	char str[20]= "hello, world!";
	strupper(str);
	printf("%s\n", str);
}
