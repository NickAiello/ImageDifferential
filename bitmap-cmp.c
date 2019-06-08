#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if (argc != 3){
		printf("Needs 3 args. You gave %d. [infile1] [infile2]", argc);
	}
	const int SIZE = 100;
	const int BUFFSIZE = 10000;

	char file1[SIZE];
	char file2[SIZE];
	sprintf(file1,"%s",argv[1]);
	sprintf(file2,"%s",argv[2]);
	unsigned char buf1[BUFFSIZE];
	unsigned char buf2[BUFFSIZE];
	FILE *f1;
	FILE *f2;
	int n,m,i,offset;
	offset = 1078;
	f1 = fopen(file1,"rb");
	f2 = fopen(file2, "rb");

	//seek files to the bmp standard for pixel data start
	fseek(f1,offset,SEEK_SET);
	fseek(f2,offset,SEEK_SET);

	unsigned int sameCount, diffCount, totalBytes, sameCountXORCheck, diffCountXORCheck;
	totalBytes = sameCount = diffCount = sameCountXORCheck = diffCountXORCheck = 0;
	//loop through the file pixel data comparing counts of same bytes
	while (n = fread(buf1,1,BUFFSIZE,f1)){
		m = fread(buf2,1,BUFFSIZE,f2);
		if (m == 0 || n == 0){
			break;
		}
		totalBytes += n;
		for(i=0;i<n;i++){
			if (buf1[i] == buf2[i]){ sameCount++; }
			else { diffCount++; }
			if ((unsigned int)(buf1[i] ^ buf2[i]) == 0) {
				sameCountXORCheck++; 	
			}
			else { diffCountXORCheck++; }
			//printf("%d ^ %d = %d\n",(unsigned int)buf1[i],(unsigned int)buf2[i], (unsigned int)(buf1[i]^buf2[i]));
		}
	}
	printf("# of same bytes = %d vs %d\n",sameCount, sameCountXORCheck);
	printf("# of diff bytes = %d vs %d\n",diffCount, diffCountXORCheck);
	printf("Total Bytes = %d\n",totalBytes);
	printf("Percent same = %f vs %f\n",((double)sameCount / (double)totalBytes)*100, ((double)sameCountXORCheck / (double)totalBytes)*100);
	printf("Percent diff = %f vs %f\n",((double)diffCount / (double)totalBytes)*100, ((double)diffCountXORCheck / (double)totalBytes)*100);
	//close files
	fclose(f1);
	fclose(f2);
	return 0;
}
