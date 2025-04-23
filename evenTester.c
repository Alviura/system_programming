#include <stdio.h>

int main () {
	int number;
	while(scanf("%d", &number) == 1){
		if(number % 2 == 0){
			printf("%d is even\n", number);
		}else {
			printf("%d is odd\n", number);
		}
	}}
