#include <stdio.h>
#include <unistd.h>
int main(){
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("THis appears immediately");
	sleep(5);
	printf("and so does this\n");
	return 0;
}
