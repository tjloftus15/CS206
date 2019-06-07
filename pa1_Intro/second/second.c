#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//delimiter is space; atoi()

void SwapSort(int l [], int quantity){
	//int final[quantity];
	int j, t;
	int currj=0;
	int currt=0;
	int least=0;
	int leastPos=0;
	int temp=0;
	//char * temp;
	for(j=0;j<quantity;j++){
		currj=l[j];// - '0';
		least=currj;
		leastPos=j;
		//printf("index of outer loop: %d\n" , j);
		//printf("currj: %d\n" , currj);
		for(t=j+1; t<quantity;t++){
			currt=l[t];// - '0';
			//printf("index of inner loop: %d\n" , t);
			//printf("currt: %d\n" , currt);
			if(currt<least){
				/*l[j]=currt;// + '0';
				l[t]=currj;// + '0';\n"
				printf("swapped %d & %d\n" , currt, currj);*/
				least=currt;
				//printf("new least %d at pos %d\n" , least, leastPos);
				leastPos=t;
				
			}
		}
		if(leastPos!=j){
			temp=l[j];
			l[j]=l[leastPos];
			l[leastPos]=temp;
		}
		//printf("-----------------\n");
	}
	for(j=0;j<quantity;j++){
		printf("%d\t", l[j]);
	}
	//printf("\n");
	return;
}
int l[100];

int main( int argc, char ** argv){
	FILE *fp=NULL; //stands for file pointer
	char *fn=NULL; //stands for filename
	if(argc!=2){ //checks to see if txt file passed
		printf("error");
		exit(0);
	}
	
	fn=argv[1];
	int numOfItems;
	fp=fopen(fn, "r");
	
	if(fp==NULL){//if file not found
		printf("error");
		exit(0);
		return 0;
	}
	//char* line;
	fscanf(fp, "%d\n", &numOfItems);//gets first line which is number of 
	int items=0;
	//int items2=0;
	//int l[100];
	int i=0;
	while(!feof(fp)){
		fscanf(fp, "%d\n", &items);
		//printf("items %d\n :" , items); 
		l[i]=items;	
		i++;
	}
	//int f=0;
	/*for(;f<numOfItems;f++){
		printf("this number: %d\n" , l[f]);
	}*/
	
	/*
	fscanf(fp, "%d\n", &items);
	fscanf(fp, "%d\n", &items2);
	
	printf("items2 %d\n : " , items2);
	printf("numOfItems %d\n : " , numOfItems);
	ssize_t read;
	size_t n;
	char *line;

	read=getline(&line, &n, fp);
	printf("Retrieved line of length %zu :\n", read);
   printf("%c\n", line[1]);
   printf("length of read %zd :\n" , n);*/
   
  /* read=getdelim(&line, &n, 32, fp);
   printf("line 2 %c\n", line[2]);
   int that=NULL;
   that=line[2];//keep pointer to most recent space in the text line
   printf("that %c\n", that);
   */
   /*(
   char this=NULL;
   char ** string=NULL;
   int yes[]=NULL;
   int i=0;
   int s=0;
   int y=0;
   while(i<n){
   	this=line[i];
   	string[s]=this;
   	s++;
   	i++;
   	this=line[i];
   	while(this!=' ');
   		string[s]=this;
   		s++;
   		i++;
   		this=line[i];
   	}
   	yes [y]=atoli(string);
   	i++;
   	s=0;
   	string=NULL;
   		
   	
   }
   
   
   
   
   
   
   
   
   
   int i=0;//outside count loop
   int j=0;//inside count loop
   int k=0;//digit count
   int f=0;//fin position counter
   int y=0;//holds digit value in inner inner while
   //char ch=NULL;
   int hold [100];
   int mid=0;//holds the value of numbers to be added
   int fin [100];
   for(; i<n; i++){
   	//ch=line[i];
   	j=i;
   	while(line[i]!=' '){
   		hold[j]=line[i] - '0';
   		k++;
   		i++;
   		j++;
   	}
   	int p=0;//holder to find where current number ends/begins in hold
   	int tempo=0;//holds value to be added to fin
   	while(k!=1){//gets correct size number
   		p=j-k; //finds first point in hold where number begins
   		y=k;
   		while(y!=1){
   			tempo=hold[p]*10;
   			y--;
   		}
   		k--;
   		p++;
   		mid=tempo+mid;
   		
   		
   	}
   	mid=mid+(line[i]- '0');
   	fin[f]=mid;
   	f++;
   	mid=0;
   	
   	
   	
   	
   	*/
   //}
  /* char *token;
   char **last=NULL;;
   token= strtok_r(line, " " , last);
   printf(" -> %s\n", token);
  // int val;*/
   
   //val= atoi(line);
  // printf("value of val %d : \n", val);
   //printf("here\n");
  // int l2[100];
	SwapSort(l, numOfItems);
	fclose(fp);
	/*f=0;
	for(;f<numOfItems;f++){
		printf("this number: %d\n" , l[f]);
	}*/
	
	
	return 0;
}
