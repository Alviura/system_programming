#include <stdio.h>
#include <stdlib.h>

/* 
Types of files in C
Text files - Store information in form of ASCII characters internally, and when the file is opened, the content is readable by humans	
Binary file - It stores information in form of 0's or 1's and it is saved with the .bin extension


FILE pointer - A structure that contains info needed for reading and writing a file
*/

// A program to read content from a file
int readFromFile () {
	int buffer_size = 20;
	char *name = malloc(buffer_size);
	FILE *fptr;
	fptr = fopen("mwaura.txt","r");
	if (fptr == NULL){
		printf("The file doesnet exist");
		exit(1);
	}
	fgets(name, buffer_size, fptr);   // Read a line
    printf("%s\n", name);
	fclose(fptr);
	return 0;
}

int writeToFile(){
	char *fname = malloc(10);
	FILE *fptr = fopen("writing.txt", "r");
	if (fptr == NULL){
		printf("File dont exist");
		return 1;
	}
	printf("Enter content: ");
	scanf("%s", fname);
	fprintf(fptr, "%s", fname);
	fclose(fptr);
	return 0;
}

int appendFile(){
	int num;
	FILE *fptr = fopen("mwaura.txt", "a");
	printf("Enter what you want to add to file: ");
	scanf("%d", &num);
	fprintf(fptr, "%d", num);
	fclose(fptr);
	return 0;
}

int main(){
	readFromFile();
	appendFile();
	return 0;
}
