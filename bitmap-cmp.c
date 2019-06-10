#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if (argc != 3){
		printf("Needs 2 args. You gave %d. [infile1] [infile2]\n", argc-1);
		return 1;
	}
	const int SIZE = 100, BUFFSIZE = 10000;
	char file1[SIZE], file2[SIZE];
	sprintf(file1,"%s",argv[1]);
	sprintf(file2,"%s",argv[2]);
	unsigned char buf1[BUFFSIZE], buf2[BUFFSIZE];
	FILE *f1, *f2;
	int n,m,i,j,offset;
	
	//starting offset of pixel data (for .bmp format)
	offset = 54;
	unsigned int horizontalResOffset = 18;
	unsigned int verticalResOffset = 20;
	unsigned int horizontalRes = 0, verticalRes = 0;

	//open input files
	f1 = fopen(file1,"rb");
	f2 = fopen(file2, "rb");

	fseek(f1,horizontalResOffset,SEEK_SET);
	n = fread(&horizontalRes,1,4,f1);
	//fseek(f1,verticalResOffset,SEEK_SET);
	n = fread(&verticalRes,1,4,f1);
	printf("Image is: %ux%u pixels\n",horizontalRes,verticalRes);

	//rows end in '0' character, find the multiple for each row
	unsigned int rowEndMultiple = (horizontalRes*3) + 1;//1 byte each for RGB for each pixel => each row
	printf("Row end multiple = %u\n", rowEndMultiple);
	//seek files to the bmp standard for pixel data start
	fseek(f1,offset,SEEK_SET);
	fseek(f2,offset,SEEK_SET);
	
	//Counters for stats
	unsigned long int sameBytes, diffBytes, totalBytes, sameBits, diffBits, count;
	totalBytes = sameBytes = diffBytes = sameBits = diffBits = count = 0;

	//loop through the file pixel data comparing counts of same bits / bytes
	while (n = fread(buf1,1,BUFFSIZE,f1)){//read from file 1
		m = fread(buf2,1,BUFFSIZE,f2);//read from file 2
		if (m == 0 || n == 0){//if the amount read is different, file size is different, one file has ended, quit here
			printf("Files are of different size\n");
			break;
		}
		
		for(i=0;i<n;i++){
			if ( (totalBytes+i+1) % rowEndMultiple == 0 ){
				//printf("%ld:(%ld) %d==%d\n",ftell(f1)-n+i,totalBytes+i+1,buf1[i],buf2[i]);
				//printf("FUCK: %ld x %ld\n",totalBytes+i+1,count);
				count++;
				continue;
			}
			//get # of bytes same / diff
			if (buf1[i] == buf2[i]){
				sameBytes++; 
				//printf("%ld:(%ld) %d==%d\n",ftell(f1)-n+i,totalBytes+i+1,buf1[i],buf2[i]);
			}
			else { diffBytes++; }
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
			//printf("%d ^ %d = %d\n",(unsigned int)buf1[i],(unsigned int)buf2[i], (unsigned int)(buf1[i]^buf2[i]));//test print for finding
		}
		totalBytes += n;
	}

	totalBytes -= count;

	//Print stats
	printf("\nStats are only of pixel data. Header memory differences are NOT included.\n");
	printf("# of same bytes / bits = %ld / %ld\n",sameBytes,sameBits);
	printf("# of diff bytes / bits = %ld / %ld\n",diffBytes, diffBits);
	printf("Total bytes / bits = %ld / %ld (%ld row end bytes discounted)\n",totalBytes,totalBytes*8,count);
	printf("Percent same bytes / bits = %f / %f\n",((double)sameBytes / (double)totalBytes)*100,((double)sameBits / ((double)totalBytes*8))*100);
	printf("Percent diff bytes / bits = %Lf / %Lf\n",((long double)diffBytes / (long double)totalBytes)*100,((long double)diffBits / ((long double)totalBytes*8))*100);

	//close files
	fclose(f1);
	fclose(f2);
	return 0;
}
