#include<stdio.h>
int main() {
	char buffer[1024];
	setvbuf(stdout,buffer,_IOFBF,sizeof(buffer));
	printf("This will be buffered untill the buffer is full or flushed.\n");
	printf("Multiple printf calls may be combined in a single I/O operation\n");
	fflush(stdout);
	return 0;



}
