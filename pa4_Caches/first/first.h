//#import<stdint.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
struct hash{
	int valid;
	int fifo;
	int index;
	int blockMin;
	int blockMax;
	unsigned long int tag;
};

int longToInt(unsigned long int a){
	//printf("A VALUE ===================== %lu\n", a);
	int b= a;
	return b;
}

void printBinary(int a, char * b){
	int n=a;
	int count=0;
	int p=0;
	printf("%s: ", b);
	while(n){
		if(n & 1)
			printf("1");
		else
			printf("0");
		if(p==3){
			printf(" ");
			p=-1;
		}
		p++;
		count++;
		n>>=1;
	}printf(" (%d long)", count);
	printf("\n");
	
}

void printLongBinary(unsigned long int a, char * b){
	unsigned long int n=a;
	int count=0;
	int p=0;
	printf("%s: ", b);
	while(n){
		if(n & 1)
			printf("1");
		else
			printf("0");
		if(p==3){
			printf(" ");
			p=-1;
		}
		p++;
		count++;
		n>>=1;
	}printf(" (%d long)", count);
	printf("\n");
	//return count;
}

unsigned long int binaryLength(unsigned long int addr){
	if(addr==0){
		return addr;
	}
	int bl=0;
	unsigned long int n=addr;
	while(n){
		n>>=1;
		bl++;
		//printf("!!!");
	}
	while(bl!=64){
		addr<<=1;
		bl++;
		//printf("%d\n", bl);
	}
	return addr;
}
int getBlockBits(unsigned long int addr, int blockBits, int length){
	int bits=64-blockBits;
	addr<<=bits;
	addr>>=bits;
	int a=longToInt(addr);
	return a;
}
int getIndexBits(unsigned long int addr, int indexBits, int blockBits, int length){
	addr>>=blockBits;
	int bits=64-indexBits;
	addr<<=(bits);
	bits=64-indexBits;
	addr>>=bits;
	
	int a=longToInt(addr);
	
	return a;
}
unsigned long int getTagBits(unsigned long int addr, int indexBits, int blockBits){
	addr= addr>>(indexBits+blockBits);
	return addr;
}
int findBits(int bits){
	int e=0;
	while(bits>>=1)
		e++;
	return e;
}

int sixteenPower(int mult){
	int sum=1;
	while(mult!=0){
		sum=sum*16;
		mult--;
	}
	return sum;
}

unsigned long int convertFromHex(char * a, int len){
	int i=0;
	//int j=len-1;;
	int mult=len-1;
	char curr;
	int c=0;
	unsigned long int posValue=0;//power of sixteen value
	//printf("in convertFromHex, passed char array: %s and length: %d\n", a, len);
	unsigned long int addr=0;
	//printf("addr at start: %lu\n", addr);
	while(i!=len){
		curr=a[i];
		posValue=sixteenPower(mult);
		//printf("-------value of 16, %lu, to the power of %d\n", posValue, mult);
		
		
		if(curr=='a'){
			c= 10;
			addr=addr+(posValue*c);
			//printf("addr = %lu\n", addr);
		}
		else if(curr== 'b'){
			c=11;
			//int m= posValue*c;
			//printf(" M = %d\n", m);
			addr=addr+(posValue*c);
			//printf("addr = %lu\n", addr);
		}
		else if(curr== 'c'){
			c=12;
			addr=addr+(posValue*c);
			//printf("addr = %lu\n", addr);
		}else if(curr=='d'){
			c=13;
			addr=addr+(posValue*c);
			//printf("addr = %lu\n", addr);
		}else if(curr== 'e'){
			c=14;
			addr=addr+(posValue*c);
			//printf("addr = %lu\n", addr);
		}else if(curr== 'f'){
			c=15;
			addr=addr+(posValue*c);
			//printf("addr = %lu\n", addr);
		}else if(isdigit(curr)){
			//printf("in default at i= %d\n", i);
			c=curr-'0';
			addr=addr+(posValue*c);
			//printf("addr = %lu\n", addr);
		}
		//printf("addr value at i=%d: %lu\n", i, addr);
		i++;
		mult--;
	}
	return addr;
	
}

unsigned long int getAddr(char * line, int len){
	int start=0;
	int end=0;
	int i=0;
	//printf("in get Addr\n");
	while(line[start]!='R' && line[start]!='W'){
		start++;
		//printf("in R and W loop\n");
	}
	start=start+4;
	end=len-1;
	int nLen=end-start+1;
	char a[nLen];
	i=0;
	int j=start;
	while(j!=len){
		a[i]=line[j];
		i++;
		j++;	
	}
	//printf("found hex addr: 0x%s\n", a);
	
	unsigned long int addr=convertFromHex(a, nLen);
	//printf("address found: %lu\n", addr);
	return addr;
}

char getInstruction(char * line){
	int i=0;
	while(line[i]!='R' && line[i]!='W'){
		i++;
	}
	char c=line[i];
	return c;
}

int findBinaryLength(unsigned long int a){
	unsigned long int n=a;
	int i=0;
	while(n){
		i++;
		n>>=1;
	}
	return i;
}

int findVictim(struct hash ** cache, int key, int numOfBlocks){//FINDS POS TO BE EVICTED
	int i=1;
	int lowest=cache[key][0].fifo;
	long int curr=0;
	int lowestPos=0;
	if(numOfBlocks==1){
		return lowestPos;
	}
	while(i<numOfBlocks){
		curr=cache[key][i].fifo;
		if(curr<lowest){
			lowestPos=i;
		}
		i++;
	}
	return lowestPos;
}

void fifoPrinter(int ** fifo, int r, int c){
	int i=0;
	int j=0;
	for(i=0; i<r; i++){
		for(j=0; j<c; j++){
			printf("%d	", fifo[i][j]);
		}
		printf("\n");
		i++;
	}
}

int checkPowerTwo(int a){
	int i=1;
	while(i<a){
		i=i*2;
	}
	if(i==a){
		return 1;
	}
	return -1;
}






