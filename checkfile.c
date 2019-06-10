#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if (argc != 2){
		printf("Needs 2 args. You gave %d. [infile1] [infile2]\n", argc-1);
	}
	const int SIZE = 100, BUFFSIZE = 10000;
	char file1[SIZE], file2[SIZE];
	sprintf(file1,"%s",argv[1]);
	unsigned char buf1[BUFFSIZE], buf2[BUFFSIZE];
	FILE *f1, *f2;
	int n,m,i,j,offset;

	//starting offset of pixel data (for .bmp format)
	offset = 54;

	//open input files
	f1 = fopen(file1,"rb");

	//seek files to the bmp standard for pixel data start
	fseek(f1,offset,SEEK_SET);
	
	//Counters for stats
	unsigned long int sameBytes, diffBytes, totalBytes, sameBits, diffBits;
	totalBytes = sameBytes = diffBytes = sameBits = diffBits = 0;

	//loop through the file pixel data comparing counts of same bits / bytes
	while (n = fread(buf1,1,BUFFSIZE,f1)){//read from file 1
        for (i=0;i<n;i++){
            if (buf1[i] != 255){
                printf("%ld\n",ftell(f1)-n+i);
            }
        }
    }
}