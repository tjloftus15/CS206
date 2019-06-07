#include<stdio.h>
#include<stdlib.h>
void insert(int);
void search(int);
struct node{
	//char *key;
	//char *visit='n';
	int value;
	struct node * next;
};

struct node ** table;

char * printer;
int p=0;

void insert(int num){
	int holder=0;
	if(num<0){
		holder=num;
		num=num*-1;
	}
	int k= num%10000;
	//printf("obtained key: %d\n", k);
	if(table[k]==NULL){//if nothing at that key yet
		//printf("initial node inserted, for value %d and key %d\n", num, k);
		struct node * first=malloc(sizeof(struct node));
		table[k]=first;
		if(holder<0){
			first->value=holder;
			printer[p]='i';
			return;
		}
		first->value=num;
		printer[p]='i';
		return;
	}
	else if(table[k]!=NULL){
		//printf("spot on table already has key for value %d and key %d\n", num, k);
		struct node *curr;//malloc(sizeof(struct node));
		curr=table[k];
		if(curr->value==num || curr->value==holder){
				printer[p]='d';
				return;
		}
		//printf("found that not duplicate\n");
		//curr=table[k]->next;
		//printf("hhh\n");
		while(curr->next!=NULL){
			//printf("hhh\n");
			curr=curr->next;
			if(curr->value==num || curr->value==holder){
				printer[p]='d';
				return;
			}
		}
		//printf("located end of linked list\n");
		struct node * new=malloc(sizeof(struct node));
		
		new->next=NULL;
		if(holder<0){
			new->value=holder;
			curr->next=new;
			printer[p]='i';
			return;
		}
		new->value=num;
		curr->next=new;
		printer[p]='i';
		return;
		
	}
	return;
}

void search(int num){
	int holder=0;
	if(num<0){
		holder=num;
		num=num*-1;
	}
	int k= num%10000;
	//printf("after key found in search\n");
	if(table[k]==NULL){//if nothing at that key yet
		//printf("inside initial if for first element\n");
		printer[p]='a';
		//printf("item searched for and not found (not at key)\n");
		return;
	}
	else if(table[k]!=NULL){
		struct node * curr=malloc(sizeof(struct node));
		curr=table[k];
		if(curr->value==num || curr->value==holder){
					printer[p]='p';
					return;
		}
		curr=table[k]->next;
		while(curr!=NULL){
			if(curr->value==num || curr->value==holder){
				printer[p]='p';
				return;
			}
			curr=curr->next;
		}
	}
	printer[p]='a';
	return;
}



int main(int argc, char ** argv){
	FILE *fp=NULL; //stands for file pointer
	char *fn=NULL; //stands for filename
	if(argc!=2){ //checks to see if txt file passed
		printf("error");
		exit(0);
		return 0;
	}
	fn=argv[1];
	
	char id; //stands for identification of operation from file
	int num; //the number value found in txt file
	
	fp=fopen(fn, "r");//tries to open file specified;
	if(fp==NULL){//if file not found
		
		printf("error");
		exit(0);
		return 0;
	}
	int length=0;
	while(!feof(fp)){
		fscanf(fp, "%c %d\n", &id, &num);
		length++;
	}
	fclose(fp);
	fp=fopen(fn, "r");
	printer=(char *) malloc(length*sizeof(char));
	
	table=(struct node **) malloc(10000 * sizeof(struct node*));
	int b=0;
	for(b=0; b<10000; b++){
		table[b]=NULL;//(struct node*) malloc(sizeof(struct node));
		
		//table[b]->value=-1;
	}
	
	
	
	while(!feof(fp)){ //searching for end of file. returns true when eof reached
		//printf("inside main loop\n");
		fscanf(fp, "%c %d\n", &id, &num);
		//printf("after file read\n");
		/*if(num<0){
			num=num*-1;
		}*/
		//printf("read number: %d\n", num);
		//printf("read action: %c\n" , id);
		if(id=='i'){
			//printf("inside
			//printer[p]=id;
			insert(num);
			p++;
		}
		else if(id=='s'){
			//printer[p]=id;
			search(num);
			p++;
		}
		//printf("------------------------------------");
	}
	int h=0;
	for(h=0; h<p; h++){
		if(printer[h]=='i'){
			printf("inserted");
		}
		else if(printer[h]=='a'){
			printf("absent");
		}
		else if(printer[h]=='d'){
			printf("duplicate");
		}
		else if(printer[h]=='p'){
			printf("present");
		}
		if(h<p-1){
			printf("\n");
		}
		
	}
	//put in propper print here
	
	return 0;
	
}
