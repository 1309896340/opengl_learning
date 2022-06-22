#include <stdio.h>
#include <string.h>

int getStringFromFile(const char *filename,void *dst,int max_size){
	FILE *fp = NULL;
	char c;
	char *cptr = (char *)dst;
	int size = 0;
	
	fp = fopen(filename,"r");
	while((c=fgetc(fp))!=EOF){
		*cptr = c;
		size++;
		cptr++;
		if(size >= max_size-1)
			break;
	}
	*cptr = '\0';
	
	fclose(fp);
	return size;
}

#define SIZE 200


int main(int argc,char **argv){
	char buf[SIZE] = {0};
	
	int sz = getStringFromFile("shader",buf,SIZE);
	printf("sz=%d,str=|%s|\n",sz,buf);
	
	
	return 0;
}


