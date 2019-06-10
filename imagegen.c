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
	unsigned char offsetDetector[4];
	offset = 54;
	
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
			if (buf1[i] >= buf2[i]){
				buf1[i] = buf1[i] - buf2[i];
			} else {
				buf1[i] = 0b00000000;
			}
		}
		if (n>m){
			fwrite(buf1,1,m,out);
		} else {
			fwrite(buf1,1,n,out);
		}
	}
	//Testing to make sure the first byte of pixel data is at offset 54
	// int negSeek = -1;
	// fseek(out,negSeek-1,SEEK_END);
	// char bufzero[1];
	// bufzero[0] = bufzero[1] = bufzero[2] = 255;
	// for (i=negSeek;i<0;i++){
	// 	n= fwrite(bufzero,1,sizeof(bufzero),out);
	// }
		
	//close files
	fclose(f1);
	fclose(f2);
	fclose(out);
	return 0;
}
