#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if (argc != 4){
		printf("Needs 3 args. You gave %d. [infile1] [infile2] [outfile]", argc);
	}
	const int SIZE = 100;
	const int BUFFSIZE = 10000;

	char file1[SIZE];
	char file2[SIZE];
	char file3[SIZE];
	sprintf(file1,"%s",argv[1]);
	sprintf(file2,"%s",argv[2]);
	sprintf(file3,"%s",argv[3]);
	unsigned char buf1[BUFFSIZE];
	unsigned char buf2[BUFFSIZE];
	FILE *f1;
	FILE *f2;
	FILE *out;
	int n,m,i,offset;
	offset = 29;

	f1 = fopen(file1,"rb");
	f2 = fopen(file2, "rb");
	out = fopen(file3, "wb");
	//copy the file 1 image to the output
	while(n = fread(buf1,1,BUFFSIZE,f1)){
		fwrite(buf1,1,n,out);
	}

	//seek files to the bmp standard for pixel data start
	fseek(f1,offset,SEEK_SET);
	fseek(f2,offset,SEEK_SET);
	fseek(out,offset,SEEK_SET);

	//loop through the file pixel data setting output 
	while (n = fread(buf1,1,BUFFSIZE,f1)){
		m = fread(buf2,1,BUFFSIZE,f2);
		if (m == 0 || n == 0){
			break;
		}
		for(i=0;i<n;i++){
			buf1[i] = buf1[i] ^ buf2[i];
		}
		if (n>m){
			fwrite(buf1,1,m,out);
		} else {
			fwrite(buf1,1,n,out);
		}
	}

	//close files
	fclose(f1);
	fclose(f2);
	fclose(out);
	return 0;
}
