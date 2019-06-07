#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"first.h"
void prefetch(unsigned long int, int, int);
struct hash ** cache;
int cacheSize=0;//bytes in cache
int numOfSets=0;//number of sets
int numOfBlocks=0;//number of blocks per set (associativity)
int bytesPerBlock=0;//number of bytes per block
int hit=0;
int miss=0;
int read=0;
int write=0;
int fifoNum=1;
int eviction=0;;



void prefetch(unsigned long int addr, int nindexBits, int nblockBits){
	int L=findBinaryLength(addr);
	int blockBits=getBlockBits(addr, nblockBits, L);
	int indexBits=getIndexBits(addr, nindexBits, nblockBits, L);
	unsigned long int tagBits= getTagBits(addr, nindexBits, nblockBits);
	int key=0;
	if(numOfSets==1){
		key=0;
	}
	else{
		key=indexBits%numOfSets;
	}
	unsigned long int cTag=0;
	int cvalidBit;
	int i=0;
	int openPos=-1;
	int found=0;
	while(i<numOfBlocks){
		cvalidBit=cache[key][i].valid;
		if(cvalidBit==0){
			openPos=i;
		}
		else if(cvalidBit==1){
			cTag=cache[key][i].tag;
			if(cTag==tagBits){
				found++;
				break;
			}
		}
		i++;
	}
	if(found==0 && openPos!=-1){//so if no hit and found empty space
		read++;
		cache[key][openPos].tag=tagBits;
		cache[key][openPos].valid=1;
		cache[key][openPos].blockMin=blockBits;
		cache[key][openPos].blockMax=blockBits+bytesPerBlock;
		cache[key][openPos].index=indexBits;
		cache[key][openPos].fifo=fifoNum;
		fifoNum++;
	}else if(found==0 && openPos==-1){//so if no hit and no empty space
		read++;
		eviction=findVictim(cache, key, numOfBlocks);
		cache[key][eviction].tag=tagBits;
		cache[key][eviction].blockMin=blockBits;
		cache[key][eviction].blockMax=blockBits+bytesPerBlock;
		cache[key][eviction].index=indexBits;
		cache[key][eviction].fifo=fifoNum;
		fifoNum++;
	}
	return;
}

int main(int argc, char ** argv){
	FILE *fp=NULL;
	char *fn=NULL;
	if(argc!=6){
		printf("error");
		exit(0);
	}
	fn=argv[5];
	fp=fopen(fn, "r");
	if(fp==NULL){
		printf("error");
		exit(0);
	}
	int check=0;
	char * CS=argv[1];
	sscanf(CS, "%d", &cacheSize);
	check=checkPowerTwo(cacheSize);
	if(check==-1){
		printf("error");
		exit(0);
	}
	char *BPB=argv[4];
	sscanf(BPB, "%d", &bytesPerBlock);
	check=checkPowerTwo(bytesPerBlock);
	if(check==-1){
		printf("error");
		exit(0);
	}
	char * assoc = argv[2];
	int LRU=0;
	char * replacement=argv[3];
	if(replacement[0]=='L' || replacement[0]=='l'){
		LRU=1;
	}
	if(assoc[0]=='d'){//direct mapped cache
		numOfBlocks=1;
	}
	else{
		int b= strlen(assoc);
		if(b==5){//1 set (fully associative)
			numOfBlocks=cacheSize/bytesPerBlock;
		}
		else{//more than one set, more than one block per (set assoc cache)
			if(b>7){
				int c=6;
				int cl=0;
				char a2[b-5];
				while(c<b){
					a2[cl]=assoc[c];
					cl++;
					c++;
				}
				int A=0;
				sscanf(a2, "%d", &A);
				check=checkPowerTwo(A);
				if(check==-1){
					printf("error");
					exit(0);
				}
				numOfBlocks=A;
			}else{
				int A=assoc[6]-'0';
				check=checkPowerTwo(A);
				if(check==-1){
					printf("error");
					exit(0);
				}
				numOfBlocks=A;
			}
		}
	}
	numOfSets=cacheSize/(numOfBlocks*bytesPerBlock);
	if(numOfSets==0){
		numOfSets=1;
	}
	cache=(struct hash **)malloc(numOfSets*sizeof(struct hash*));
	int i=0;
	int j=0;
	for(i=0;i<numOfSets;i++){
		cache[i]=(struct hash *) malloc(numOfBlocks*sizeof(struct hash));
		for(j=0; j<numOfBlocks;j++){
			cache[i][j].tag=0;
			cache[i][j].valid=0;
			cache[i][j].fifo=0;
			cache[i][j].blockMin=0;
			cache[i][j].blockMax=0;
			cache[i][j].index=0;
		}
	}
	int nblockBits;
	int nindexBits;
	nblockBits=findBits(bytesPerBlock);
	nindexBits=findBits(numOfSets);
	i=0;
	char *line= NULL;
	size_t length=0;
	int PF=0;
	read=0;
	write=0;
	fifoNum=1;
	eviction=0;
	while(PF<2){
		if(PF==1){
			hit=0;
			miss=0;
			read=0;
			write=0;
			fifoNum=1;
			fclose(fp);
			fp=fopen(fn, "r");
			for(i=0;i<numOfSets;i++){
				for(j=0; j<numOfBlocks;j++){
					cache[i][j].tag=0;
					cache[i][j].valid=0;
					cache[i][j].fifo=0;
					cache[i][j].blockMin=0;
					cache[i][j].blockMax=0;
					cache[i][j].index=0;
				}
			}
		}
		while(!feof(fp)){
			unsigned long int addr=0;
			getline(&line, &length, fp);
			if(line[0]=='#'){
				break;
			}
			int len=strlen(line);
			len=len-1;
			addr=getAddr(line, len);
			char action=getInstruction(line);
			int L=findBinaryLength(addr);
			int blockBits=getBlockBits(addr, nblockBits, L);
			int indexBits=getIndexBits(addr, nindexBits, nblockBits, L);
			unsigned long int tagBits= getTagBits(addr, nindexBits, nblockBits);
			int key=0;
			if(action=='W'){
				write++;
			}
			if(numOfSets==1){
				key=0;
			}else{
				key=indexBits%numOfSets;
			}
			unsigned long int cTag=0;
			int cvalidBit;
			i=0;
			int openPos=-1;
			int found=0;
			while(i<numOfBlocks){
				cvalidBit=cache[key][i].valid;
				if(cvalidBit==0){
					openPos=i;
				}
				else if(cvalidBit==1){
					cTag=cache[key][i].tag;
					if(cTag==tagBits){
						hit++;
						found++;
						if(LRU==1){
							cache[key][i].fifo=fifoNum;
							fifoNum++;
						}
						break;
					}
				}
				i++;
			}
			if(found==0 && openPos!=-1){//so if no hit and found empty space
				miss++;
				read++;
				cache[key][openPos].tag=tagBits;
				cache[key][openPos].valid=1;
				cache[key][openPos].blockMin=blockBits;
				cache[key][openPos].blockMax=blockBits+bytesPerBlock;
				cache[key][openPos].index=indexBits;
				cache[key][openPos].fifo=fifoNum;
				fifoNum++;
				if(PF==1){
					unsigned long int x=addr+bytesPerBlock;
					prefetch(x, nindexBits, nblockBits);
				}
			}else if(found==0 && openPos==-1){//so if no hit and no empty space
				miss++;
				read++;
				eviction=findVictim(cache, key, numOfBlocks);
				cache[key][eviction].tag=tagBits;
				cache[key][eviction].blockMin=blockBits;
				cache[key][eviction].blockMax=blockBits+bytesPerBlock;
				cache[key][eviction].index=indexBits;
				cache[key][eviction].fifo=fifoNum;
				fifoNum++;
				if(PF==1){
					unsigned long int x=addr+bytesPerBlock;
					prefetch(x, nindexBits, nblockBits);
				}
			}
		}
		if(PF==1){
			printf("with-prefetch\n");
			printf("Memory reads: %d\n", read);
			printf("Memory writes: %d\n", write);
			printf("Cache hits: %d\n", hit);
			printf("Cache misses: %d\n", miss);
			PF++;
		}
		else if(PF==0){
			printf("no-prefetch\n");
			printf("Memory reads: %d\n", read);
			printf("Memory writes: %d\n", write);
			printf("Cache hits: %d\n", hit);
			printf("Cache misses: %d\n", miss);
			PF++;
		}
	}
	return 0;
} 
	
	
	

