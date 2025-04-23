#include <stdio.h>
#include <unistd.h>

int main() {
	setvbuf(stdout, NULL, _IOLBF, 0);
	printf("This will be printed immediately when a newline is encountered");
	sleep(5);
	printf("\n");
	printf("This appears immediately\n");
	return 0;
}
