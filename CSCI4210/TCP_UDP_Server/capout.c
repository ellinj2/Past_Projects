#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
	FILE* fd = fopen("max.txt", "w");
	fprintf(fd, "BROADCAST 990\n");
	for(int i=0; i<991; i++){fprintf(fd, "A");}
	fprintf(fd, "\n");
	fclose(fd);
}
