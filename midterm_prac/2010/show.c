#include<stdio.h>

int main() {

	for(int i=9; i>0; i--) {
		for(int k=1; k<=i; k++) {
			printf("%d ", k);
		}
		printf("\n");
	}
}
