#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"first.h"

struct var * table;
//int * varValue;
//struct var * varName;
int ** vars;
int ** varNumber;
int * actionCodes;

int main(int argc, char ** argv){
	FILE *fp=NULL;
	char *fn=NULL;
	if(argc!=2){
		printf("error");
		exit(0);
	}
	fn=argv[1];
	fp=fopen(fn, "r");
	if(fp==NULL){
		printf("error");
		exit(0);
	}
	char * line=NULL;
	size_t length=0;
	//first line
	//
	getline(&line, &length, fp);
	int len=strlen(line);
	len=len-1;
	int key=0;
	int numInputVar=inputAmountFinder(line);
	
	int fileLength=getFileLength(fn);
	int actionLines=fileLength-2;
	int totalGray=powerTwo(numInputVar);
	int numTempVar=fileLength*totalGray;
	getline(&line, &length, fp);
	int numOutputVar=inputAmountFinder(line);
	//printf("num out = %d\n", numOutputVar);
	
	int hashSize=numTempVar+numInputVar+numOutputVar;
	//unsigned long int * grayCode=produceGrayCode(numInputVar);//the values of each binary encoding
	table = (struct var *)malloc(hashSize*sizeof(struct var));//the hash tableF
	//varName=(struct var *)malloc(hashSize*sizeof(struct var));
	//varValue=(int*)malloc(hashSize*sizeof(int));
	int * outputVar=(int*)malloc(numOutputVar*sizeof(int));
	int * inputVar=(int*)malloc(numInputVar*sizeof(int));
	vars=(int**)malloc(actionLines*sizeof(int*));
	varNumber=(int**)malloc(actionLines*sizeof(int*));
	actionCodes=(int *)malloc(actionLines*sizeof(int));//codes for each line on the action to take
	
	int varPos=0;
	int numPos=0;
	int outPos=0;
	//int * grayValuePos=(int*)malloc((totalGray+1)*sizeof(int));
	/*	LEGEND:
			1 = Multiplexer	4 = And		7 = NAND
			2 = Decoder			5 = OR		8 = NOR
			3 = Not				6 = XOR
																	*/
																	
		//each line of decodeInput is a line in which a decode action was found. saves inputVar keys
		//each line of decodeOutput is a line in which a decode action was found, saves outputVar keys
	int i=0;
	while(i<actionLines){
		varNumber[i]=(int*) malloc(2*sizeof(int));
		i++;
	}
	i=0;
	/*
	while(i<totalGray){
		//printf("i=%d total=%d\n", i, totalGray);
		int t5=grayCode[i];
		grayValuePos[t5]=i;
		i++;
	}*/
	int intPos=0;
	fclose(fp);
	fp=fopen(fn, "r");
	getline(&line, &length, fp);
	len=strlen(line);
	len=len-1;
	i=0;
	int runs=0;
	//int DE_place=0;
	//this loop will assign the inputVar/outputVar to their locations in table and give them inital values
	while(runs<=1){
		if(runs==1){
			getline(&line, &length, fp);
			len=strlen(line);
			len=len-1;
			i=0;
		}
		while(line[i]!=' '){//skips INPUTVAR
			i++;
		}
		while(line[i]==' '){//skips space between INPUTVAR and #INPUTVAR
			i++;
		}
		while(line[i]!=' '){//skips # of INPUTVAR
			i++;
		}
		while(line[i]==' '){//skips space between #INPUTVAR and first varName
			i++;
		}
		while(i<len){
			int length=0;
			int t=i;
			while(line[i]!=' '){
				length++;
				i++;
				if(i>=len){
					break;
				}
			}
			char * name = getVarName(line, t);
			key=hash(name, length, hashSize);
			table[key].value=0;
			table[key].key=name;
			table[key].length=length;
			if(runs==0){
				inputVar[intPos]=key;
				intPos++;
			}
			else if(runs==1){
				outputVar[outPos]=key;
				outPos++;
			}
			i++;//skips space between variable names
			length=0;
		}
		runs++;
	}
	runs=0;
	int t=0;
	i=0;
	int numOutputs=0;
	int numInputs=0;
	int read=1;
	int totalVar=0;
	//printf("before fetcher\n");
	while(read<actionLines){
		getline(&line, &length, fp);
		//printf("line = %s\n", line);
		i=0;
		char curr = line[0];
		switch(curr){
			case ' ':
				break;
			case 'M':
				actionCodes[t]=1;
				t++;
				numInputs=inputAmountFinder(line);
				varNumber[numPos][0]=numInputs;
				i=getFirstInput(line, numInputs);
				numOutputs=LogTwo(numInputs);
				varNumber[numPos][1]=numOutputs;
				totalVar=numOutputs+numInputs+1;
				vars[varPos]=(int*)malloc(totalVar*sizeof(int));
				vars[varPos]=getKeys(line, table, i, totalVar, hashSize);
				varPos++;
				numPos++;
				break;
			case 'D':
				actionCodes[t]=2;
				t++;
				numInputs=inputAmountFinder(line);
				i=getFirstInput(line, numInputs);
				numOutputs=powerTwo(numInputs);
				totalVar=numOutputs+numInputs;
				vars[varPos]=(int*)malloc((numOutputs+numInputs)*sizeof(int));
				vars[varPos]=getKeys(line, table, i, totalVar, hashSize);
				varNumber[numPos][0]=numInputs;
				varNumber[numPos][1]=numOutputs;
				numPos++;
				varPos++;
				break;
			case 'A':
				actionCodes[t]=4;
				t++;
				numInputs=2;
				i=4;
				numOutputs=1;
				vars[varPos]=(int*)malloc(3*sizeof(int));
				vars[varPos]=getKeys(line, table, i, 3, hashSize);
				varPos++;
				varNumber[numPos][0]=numInputs;
				varNumber[numPos][1]=numOutputs;
				numPos++;
				break;
			case 'O':
				actionCodes[t]=5;
				t++;
				numInputs=2;
				i=3;
				numOutputs=1;
				vars[varPos]=(int*)malloc(3*sizeof(int));
				vars[varPos]=getKeys(line, table, i, 3, hashSize);
				varPos++;
				varNumber[numPos][0]=numInputs;
				varNumber[numPos][1]=numOutputs;
				numPos++;
				break;
			case 'X':
				actionCodes[t]=6;
				t++;
				numInputs=2;
				i=4;
				numOutputs=1;
				vars[varPos]=(int*)malloc(3*sizeof(int));
				vars[varPos]=getKeys(line, table, i, 3, hashSize);
				//arrayPrinter(vars[varPos], "vars[varPos]= ", 3);
				varPos++;
				varNumber[numPos][0]=numInputs;
				varNumber[numPos][1]=numOutputs;
				numPos++;
				break;
			case 'N':
				if(line[2]=='T'){
					actionCodes[t]=3;
					t++;
					numInputs=1;
					i=4;
					numOutputs=1;
					vars[varPos]=(int*)malloc(2*sizeof(int));
					vars[varPos]=getKeys(line, table, i, 2, hashSize);
					varPos++;
					varNumber[numPos][0]=numInputs;
					varNumber[numPos][1]=numOutputs;
					numPos++;
					break;
				}else{
					if(line[1]=='A'){
						actionCodes[t]=7;
						t++;
						numInputs=2;
						i=5;
						numOutputs=1;
						vars[varPos]=(int*)malloc(3*sizeof(int));
						vars[varPos]=getKeys(line, table, i, 3, hashSize);
						varPos++;
						varNumber[numPos][0]=numInputs;
						varNumber[numPos][1]=numOutputs;
						numPos++;
						break;
					}else{
						actionCodes[t]=8;
						t++;
						numInputs=2;
						i=4;
						numOutputs=1;
						vars[varPos]=(int*)malloc(3*sizeof(int));
						vars[varPos]=getKeys(line, table, i, 3, hashSize);
						varPos++;
						varNumber[numPos][0]=numInputs;
						varNumber[numPos][1]=numOutputs;
						numPos++;
						break;
					}
				}
			break;
				
		}read++;
		//printf("after\n");	
	}
	//printf("after fetcher\n");
	int KH=0;
	unsigned long int * gray;
	runs=0;
	while(runs<totalGray){//this part gets each new gray code  sequence!!!!!/////
		if(runs>0){
			intPos=0;
			unsigned long int currGray=getGray(runs);
			//printf("gray value = %lu\n", currGray);
			//grayCodes[runs];
			gray=(unsigned long int *)malloc(numInputVar*sizeof(unsigned long int));
			int j=0;
			//int d=0;
			while(j<numInputVar){
				int b=currGray&1;
				gray[j]=b;
				j++;
				currGray>>=1;
			}
			int b=numInputVar-1;	
			while(b>=0){
				printf("%lu ", gray[b]);
				b--;
			}
			j=numInputVar-1;
			while(j>=0){//assigns new gray code to proper input var
				int t6=inputVar[intPos];
				table[t6].value=gray[j];
				//printf("assigned gray[%d] to table[%d] --> %s.value = %lu\n", j, t6, table[t6].key, gray[j]);
				j--;
				intPos++;
			}
			
			KH=0;
			varPos=0;
			numPos=0;

		}else if(runs==0){
			//linesPassed=4;
			varPos=0;
			numPos=0;
			int b=numInputVar;
			int b2=0;
			while(b2<b){
				printf("0 ");
				b2++;
			}
			
		}
		KH=0;
		//printf("before KH\n");
		int * inputs;
		while(KH<actionLines-1){
			int j=0;
			int f;
			int ckey;
			int fkey;
			int skey;
			int tkey;
			int a;
			int b;
			int c;
			i=0;
		//	printf("KH=%d\n", KH);
		//printf("------------------------------------------------------------------------\n");
			int action=actionCodes[KH];
			if(action==0){
				break;
			}
			//printf("action = %d\n", action);
			/*if(runs<=2 && runs<=5){
				printf("\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("\n");
			}*/
			switch(action){
				case 1:
					//printf("M\n");
					numInputs=varNumber[numPos][0];
					numOutputs=varNumber[numPos][1];
					numPos++;
					gray=produceGrayCode(numOutputs);
					i=0;
					inputs=(int*)malloc(numInputs*sizeof(int));
					while(i<numInputs){
						ckey=vars[varPos][i];
						if(ckey==hashSize || ckey==hashSize+1){
							ckey=ckey-hashSize;
							inputs[i]=ckey;
						}else{
							inputs[i]=table[ckey].value;
						}
						i++;
					}
					//printf("before selectors\n");
					int * selectors=(int*) malloc(numOutputs*sizeof(int));
					i=numInputs;
					j=0;
					while(j<numOutputs){
						ckey=vars[varPos][i];
						
						if(ckey==hashSize || ckey==hashSize+1){
							ckey=ckey-hashSize;
							selectors[j]=ckey;
						}else{
							selectors[j]=table[ckey].value;
							//printf("value taken from table[%d] = %s\n", ckey, table[ckey].key);
						}
						i++;
						j++;
					}	
					//printf("after selector assignment\n");
					int out=MPsolver(inputs, selectors, gray, numOutputs);//returns value to be assigned to out
					//printf("out value = %d\n", out);
					//printf("after out\n");
					i=0;
					int op=numInputs+numOutputs;
					//printf("total variables: %d\n", (numInputs+numOutputs));
					int outkey=vars[varPos][op];
					if(outkey==hashSize || outkey==hashSize+1){
						outkey=outkey-hashSize;
					}
					//printf("outkey = %d hashSize=%d\n", outkey, hashSize);
					//printf("assigned %d to table[%d] = %s\n", out, outkey, table[outkey].key);
					table[outkey].value=out;
					varPos++;
					//printf("after M\n");
					//free(selectors);
					//free(gray);
					//free(inputs);
					break;
				case 2:
					i=0;
					numInputs=varNumber[numPos][0];
					numOutputs=varNumber[numPos][1];
					numPos++;
					gray=makeGrayCode(numOutputs);
					//gray=
					i=0;
					inputs=(int*)malloc(numInputs*sizeof(int));
					while(i<numInputs){
						ckey=vars[varPos][i];
						if(ckey==hashSize || ckey==hashSize+1){
							ckey=ckey-hashSize;
							inputs[i]=ckey;
						}else{
							inputs[i]=table[ckey].value;
						}
						i++;
					}
					int inputNum=translateBinary(inputs, numInputs);
					//printf("i when all inputs found = %d\n", i);
					i=numInputs;
					//printf("i's new pos= %d\n", i);
					//printf("output + input = %d\n", numOutputs+numInputs);
					j=0;
					//printf("hashSize = %d, inputNum = %d\n", hashSize, inputNum);
					int openPos=0;
					i=0;
					while(i<numOutputs){
						if(inputNum==gray[i]){
							openPos=i;
							break;
						}
						i++;
					}
					//printf("t3 = %d\n", t3);
					j=0;
					i=numInputs;
					/*i=i+t3;
					ckey=vars[varPos][i];
					table[ckey].value=1;*/
					
					while(j<numOutputs){
						//printf("in loop at j=%d and i=%d\n", j, i);
						
						ckey=vars[varPos][i];
						//printf("assign to %s\n", table[ckey].key);
						if(j==openPos){
							table[ckey].value=1;
						}else{
							table[ckey].value=0;
						}
						i++;
						j++;
					}
					//free(inputs);
					//free(selectors);
					//free(gray);
					varPos++;
					break;
				case 3:
					//printf("in NOT\n");
					fkey=vars[varPos][0];
					if(fkey>=hashSize)
						fkey=fkey-hashSize;
					skey=vars[varPos][1];
					if(skey>=hashSize)
						skey=skey-hashSize;
					f=table[fkey].value;
					
					if(f==0){
						table[skey].value=1;
						//printf("new value = 1\n");
					}else{
						table[skey].value=0;
						//printf("new value = 0\n");
					}
					//printf("input string-->%s\n", table[fkey].key);
					//printf("output string-->%s\n", table[skey].key);
					//printf("%d = f\n", f);
					//printf("%d = actual value at table[skey].value\n", table[skey].value);
					
					varPos++;
					numPos++;
					break;
				case 4:
					//printf("in AND\n");
					fkey=vars[varPos][0];
					skey=vars[varPos][1];
					tkey=vars[varPos][2];
					//printf("hashSize: %d, fkey: %d, skey: %d, tkey: %d\n", hashSize, fkey, skey, tkey);
					a=-1;
					b=-1;
					c=0;
					if(fkey>=hashSize){
						a=fkey-hashSize;
					}else{
						a=table[fkey].value;
						//printf("fkey =%s ", table[fkey].key);
					}if(skey>=hashSize){
						b=skey-hashSize;
					}else{
						b=table[skey].value;
						//printf("skey=%s \n", table[skey].key);
					}
					//printf("tkey=%s \n", table[tkey].key);
					c=a&b;
					table[tkey].value=c;
					//printf("%d = %d & %d\n", c, a,b);
					//printf("%d = actual table[tkey].value\n", table[tkey].value);
					
					//printf("%d = %d & %d (actual=%d)\n", (table[fkey].value & table[skey].value), table[fkey].value, table[skey].value, table[tkey].value);
					varPos++;
					numPos++;
					//printf("after and\n");
					break;
				case 5:
					//printf("in OR\n");
					fkey=vars[varPos][0];
					skey=vars[varPos][1];
					tkey=vars[varPos][2];
					a=-1;
					b=-1;
					c=0;
					//printf("hashSize: %d, fkey: %d, skey: %d, tkey: %d\n", hashSize, fkey, skey, tkey);
					if(fkey>=hashSize){
						a=fkey-hashSize;
					}else{
						a=table[fkey].value;
						//printf("fkey =%s ", table[fkey].key);
					}if(skey>=hashSize){
						b=skey-hashSize;
					}else{
						b=table[skey].value;
						//printf("skey=%s \n", table[skey].key);
					}
					//printf("tkey=%s \n", table[tkey].key);
					c=a|b;
					table[tkey].value=c;
					//printf("%d = %d | %d\n", c, a,b);
					//printf("%d = actual table[tkey].value\n", table[tkey].value);
					
					varPos++;
					numPos++;
					break;
				case 6:
					//XOR
					fkey=vars[varPos][0];
					skey=vars[varPos][1];
					tkey=vars[varPos][2];
					a=-1;
					b=-1;
					c=0;
					if(fkey>=hashSize){
						a=fkey-hashSize;
					}else{
						a=table[fkey].value;
					}if(skey>=hashSize){
						b=skey-hashSize;
					}else{
						b=table[skey].value;
					}
					c=a^b;
					//printf("%d= %d ^ %d\n", c, a,b);
					table[tkey].value=c;
					varPos++;
					numPos++;
					break;
				case 7:
					//printf("in NAND\n");
					fkey=vars[varPos][0];
					skey=vars[varPos][1];
					tkey=vars[varPos][2];
					a=-1;
					b=-1;
					c=0;
					if(fkey>=hashSize){
						a=fkey-hashSize;
					}else{
						a=table[fkey].value;
					}if(skey>=hashSize){
						b=skey-hashSize;
					}else{
						b=table[skey].value;
					}
					c=a&b;
					table[tkey].value=~c;
					varPos++;
					numPos++;
					break;
				case 8:
					//printf("in NOR\n");
					fkey=vars[varPos][0];
					skey=vars[varPos][1];
					tkey=vars[varPos][2];
					a=-1;
					b=-1;
					c=0;
					if(fkey>=hashSize){
						a=fkey-hashSize;
					}else{
						a=table[fkey].value;
					}if(skey>=hashSize){
						b=skey-hashSize;
					}else{
						b=table[skey].value;
					}
					c=a|b;
					table[tkey].value=~c;
					varPos++;
					numPos++;
					break;
			}
			KH++;
			
		}
		i=0;
		outPos=0;
		//printf("numOutputVar = %d\n", numOutputVar);
		while(i<numOutputVar){
			int ckey=outputVar[outPos];
			printf("%d ", table[ckey].value);
			i++;
			outPos++;
		}
		if(runs<totalGray-1){
			printf("\n");
		}
		outPos=0;
		runs++;
	}
	printf("\n");
	return 0;
}
		
