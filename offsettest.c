#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if (argc < 3){
		printf("Needs 3 args. You gave %d. [infile1] [outfile]\n", argc);
	}
	const int SIZE = 100;
	const int BUFFSIZE = 10000;

	char file1[SIZE];
	char file2[SIZE];
	sprintf(file1,"%s",argv[1]);
	sprintf(file2,"%s",argv[2]);
	unsigned char buf1[BUFFSIZE];
	FILE *f1;
	FILE *out;
	int n,i,offset;
	offset = 54;

	f1 = fopen(file1,"rb");
	out = fopen(file2, "wb");
    fseek(f1,offset,SEEK_SET);
	fseek(out,offset,SEEK_SET);

	f1 = fopen(file1,"rb");
	out = fopen(file2, "wb");
	//copy the file 1 image to the output
	while(n = fread(buf1,1,BUFFSIZE,f1)){
        fwrite(buf1,1,n,out);
	}

	//Testing to make sure the first byte of pixel data is at offset 54
    // char bufzero[1];
    // bufzero[0] = 255;
	// int negSeek = -1528;
	// fseek(out,negSeek-1,SEEK_END);
	// for (i=negSeek;i<0;i++){
	// 	n= fwrite(bufzero,1,sizeof(bufzero),out);
	// }
    // fseek(out,518045,SEEK_END);
    // for (i=0;i<0;i++){
    // 	n= fwrite(bufzero,1,sizeof(bufzero),out);
    // }
	//close files
	fclose(f1);
	fclose(out);
	return 0;
}
