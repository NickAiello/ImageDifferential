#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if (argc != 3){
		printf("Needs 2 args. You gave %d. [infile1] [infile2]\n", argc-1);
	}
	const int SIZE = 100, BUFFSIZE = 10000;
	char file1[SIZE], file2[SIZE];
	sprintf(file1,"%s",argv[1]);
	sprintf(file2,"%s",argv[2]);
	unsigned char buf1[BUFFSIZE], buf2[BUFFSIZE];
	FILE *f1, *f2;
	int n,m,i,j,offset;

	//starting offset of pixel data (for .bmp format)
	offset = 1078;

	//open input files
	f1 = fopen(file1,"rb");
	f2 = fopen(file2, "rb");

	//seek files to the bmp standard for pixel data start
	fseek(f1,offset,SEEK_SET);
	fseek(f2,offset,SEEK_SET);
	
	//Counters for stats
	unsigned long int sameBytes, diffBytes, totalBytes, sameBits, diffBits;
	totalBytes = sameBytes = diffBytes = sameBits = diffBits = 0;

	//loop through the file pixel data comparing counts of same bits / bytes
	while (n = fread(buf1,1,BUFFSIZE,f1)){//read from file 1
		m = fread(buf2,1,BUFFSIZE,f2);//read from file 2
		if (m == 0 || n == 0){//if the amount read is different, file size is different, one file has ended, quit here
			break;
		}
		totalBytes += n;
		for(i=0;i<n;i++){
			//get the # of bits same / diff
			unsigned char compareIsolater = 0b00000001;
			for (j=0;j<8;j++){
				if ((compareIsolater & (unsigned char)buf1[i]) == (compareIsolater & (unsigned char)buf2[i])) {
					sameBits++;
				} else {
					diffBits++;
				}
				compareIsolater = compareIsolater << 1;
			}
			//get # of bytes same / diff
			if (buf1[i] == buf2[i]){ sameBytes++; }
			else { diffBytes++; }
			//printf("%d ^ %d = %d\n",(unsigned int)buf1[i],(unsigned int)buf2[i], (unsigned int)(buf1[i]^buf2[i]));//test print for finding 
		}
	}

	//Print stats
	printf("# of same bytes / bits = %ld / %ld\n",sameBytes,sameBits);
	printf("# of diff bytes / bits = %ld / %ld\n",diffBytes, diffBits);
	printf("Total bytes / bits = %ld / %ld\n",totalBytes,totalBytes*8);
	printf("Percent same bytes / bits = %f / %f\n",((double)sameBytes / (double)totalBytes)*100,((double)sameBits / ((double)totalBytes*8))*100);
	printf("Percent diff bytes / bits = %f / %f\n",((double)diffBytes / (double)totalBytes)*100,((double)diffBits / ((double)totalBytes*8))*100);

	//close files
	fclose(f1);
	fclose(f2);
	return 0;
}
