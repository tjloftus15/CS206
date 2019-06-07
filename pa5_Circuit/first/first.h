#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

struct var{
	int value; //either 1 or 0
	char * key; //the actual variable name
	int length;
};
extern struct var * table;
int checkString(char * a, int al, char * b, int bl){
	int i=0;
	if(al!=bl){
		return 0;
	}
	while(i<al){
		if(a[i]!=b[i]){
			return 0;
		}
		i++;
		if(i==al || i==bl){
			return 1;
		}
	}
	return 1;
}

int findCorrectHash(struct var * table, int key, int hashSize, char * t1, int length){
	int i=key;
	if(i==hashSize){
		i=0;
	}
	while(table[i].key!=NULL){
		char * a = table[i].key;
		int equal=checkString(a, table[i].length, t1, length);
		if(equal==1){
			return i;
		}
		i++;
		if(i==hashSize){
			i=0;
		}
	}
	
	return i;
}
char * getVarName(char * line, int pos){
	int i=pos;
	int start=pos;
	int len=strlen(line);
	len--;
	while(line[i]!=' '){
		i++;
		if(i>=len){
			break;
		}
	}
	int end=i;
	len=end-start;
	char * a=(char *)malloc(len*sizeof(char));
	i=start;
	int j=0;
	while(i<end){
		a[j]=line[i];
		j++;
		i++;
	}
	return a;
}

int getFirstInput(char * a, int numInputs){
	int i=0;
	if(a[0]=='D'){
		if(numInputs>9){
			i=8+2+2;
			i--;
		}else{
			i=8+2+1;
			i--;
		}
	}else if(a[0]=='M'){
		if(numInputs>9){
			i=11+2+2;
			i--;
		}else{
			i=11+2+1;
			i--;
		}
	}
	return i;
}

int hash(char * a, int length, int hashSize){
	int i=0;
	char curr;
	unsigned long int sum=11;
	while(i<length){
		curr=a[i];
		
		sum=sum*33+curr*27+curr*13;
		sum=sum*67;
		i++;
	}
	sum=sum/length;
	if(sum>hashSize){
		int temp=sum%hashSize;
		sum=temp;
	}
	else{
		sum=hashSize%sum;
	}
	int s=(int)sum;
	return s;
	
}

int inputAmountFinder(char * line){
	int i=0;
	while(line[i]!=' '){
		i++;
	}
	while(line[i]==' '){
		i++;
	}
	int start=i;
	while(line[i]!=' '){
		i++;
	}
	int end=i;
	int nl=end-start;
	char a[nl];
	if(nl==1){
		return line[start]-'0';
	}
	i=0;
	while(start<end){
		a[i]=line[start];
		i++;
		start++;
	}
	
	int answer=0;
	sscanf(a, "%d", &answer);
	return answer;
}


int powerTwo(int n){
	int answer=1;
	while(n!=0){
		answer=answer*2;
		n--;
	}
	return answer;
}

unsigned long int * produceGrayCode(int n){//n inputs
	int grayNum=powerTwo(n);
	unsigned long int * answer = (unsigned long int *) malloc(grayNum*sizeof(unsigned long int));
	int w=0;
	while(w<grayNum){
		answer[w]=2;
		w++;
	}
	if(grayNum==2){
		answer[0]=0;
		answer[1]=1;
		return answer;
	}
	int leadingOne=4;
	int i=4;
	int basePos=3;
	unsigned long int * base;
	answer[0]=0;
	answer[1]=1;
	answer[2]=3;
	answer[3]=2;
	int j=0;
	int mult=1;
	while(i<grayNum){
		base=(unsigned long int *)malloc(4*mult*sizeof(unsigned long int));
		while(j<4*mult){
			base[j]=answer[j];
			j++;
		}
		j=0;
		while(i<4*mult){
			answer[i]=base[basePos] | leadingOne;
			base[basePos]=answer[i]; //this change base to be answer[i], therefor changing the b
			basePos--;
			if(basePos==-1){
				leadingOne=leadingOne*2;
				basePos=4*mult-1;
			}
			i++;
		}
		mult++;
	}
	return answer;
}

int getFileLength(char * fn){
	FILE* ptr=NULL;
	ptr=fopen(fn, "r");
	char * curr=NULL;
	size_t len=0;
	int i=0;
	while(!feof(ptr)){
		getline(&curr, &len, ptr);
		i++;
	}
	fclose(ptr);
	return i;
}
int LogTwo(int a){
	int times=0;
	while(a!=1){
		a=a/2;
		times++;
	}
	return times;
}

int translateBinary(int * a, int length){
	int power=length-1;
	int i=0;
	int sum=0;
	int mult=1;
	while(i<length){
		int curr=a[i];
		if(curr==0){
			i++;
			power--; 
			continue;
		}
		mult=1;
		int temp=power;
		if(temp==0){
			sum=sum+curr;
		}
		else if(temp!=0){
			while(temp!=0){
				mult=mult*2;
				temp--;
			}
			sum=sum+mult*curr;
		}
		i++;
		power--;
	}
	return sum;
}

int MPsolver(int * inputs, int * secondary, unsigned long int * gray, int numSecondary){
	int secondaryValue=translateBinary(secondary, numSecondary);
	int i=0;
	int totalInputs=powerTwo(numSecondary);
	while(i<totalInputs){
		int curr=gray[i];
		if(curr==secondaryValue){
			return inputs[i];
		}
		i++;
	}
	return -1;
}

int * getKeys(char * a, struct var * table, int i, int numOfVar, int hashSize){
	int * keys=(int*)malloc(numOfVar*sizeof(int));
	int k=0;
	int l;
	char * n;
	int key=0;
	int len=strlen(a);
	len--;
	if(a[i]==' '){
		i++;
	}
	
	while(i<len){
		int start=i;
		l=0;
		while(a[i]!=' '){
			i++;
			l++;
			if(i>=len){
				break;
			}
		}
		int end=i;
		i=start;
		n=(char*)malloc(l*sizeof(char));
		int j=0;
		while(i<end){
			n[j]=a[i];
			i++;
			j++;
		}
		//printf("found name = %s\n", n);
		if(l==1 && (n[0]=='0' || n[0]=='1')){
			int dig=n[0]-'0';
			keys[k]=dig+hashSize;
		}else{
			key=hash(n, l, hashSize);
			//printf("----------------------------------------------------\n");
			//printf("trying to assign %s to table[%d], while table[%d] has %s\n", n, key, key, table[key].key);
			if(table[key].key!=n){
				int open=findCorrectHash(table, key, hashSize, n, l);
				key=open;
				if(table[key].key==NULL){
					table[key].key=n;
					table[key].length=l;
				}
			}
			//printf("found key: %d\n", key);
			keys[k]=key;
			//printf("actually assigned to key = %d\n", key);
		}
		k++;
		if(i>=len){
			//printf("k=%d i=%d\n", k, i);
			i=0;
			while(i<k){
				//printf("%d ", keys[i]);
				i++;
			}
			k=0;
			//printf("\n");
			return keys;
		}
		if(i<len){
			while(a[i]==' '){
				i++;
				if(i>=len){
					return keys;
				}
			}
		}
	}
	return keys;
}


int skipAction(char * line){
	int i=0;
	while(line[i]!=' '){
		i++;
	}i++;
	return i;
}

void arrayPrinter(int * a, char * b, int length){
	printf("%s ", b);
	int i=0;
	while(i<length){
		printf("%d ", a[i]);
		i++;
	}
	printf("\n");
	return;
}

unsigned long int getGray(int x){
	return x ^ (x>>1);
}

unsigned long int * makeGrayCode(int numOutputs){
	int grayNum=numOutputs;
	unsigned long int * answer = (unsigned long int *) malloc(grayNum*sizeof(unsigned long int));
	int i=0;
	//int gray=0;
	unsigned long int temp=0;
	while(i<grayNum){
		temp= i ^ (i>>1);
		answer[i]=temp;
		i++;
	}
	return answer;
}








