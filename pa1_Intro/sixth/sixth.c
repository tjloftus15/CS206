#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct node{
	char letter;
	int value;
	struct node * next;
};

struct node * head;

int main(int argc, char ** argv){
	char * input=NULL;
	if(argc!=2){
		printf("error");
		exit(0);
		return 0;
	}
	
	//printf("the string: %s\n", argv[1]);
	//int length=strlen(argv[1]);
	int length=strlen(argv[1]);
	input=(char *) malloc((length+1)*sizeof(char));
	int i=0;
	for(;i<length;i++){
		
		if(isdigit(argv[1][i])){
			printf("error");
			exit(0);
			return 0;
		}
		if(argv[1][i]==' '){
			printf("error");
			exit(0);
			return 0;
		}
		input[i]=argv[1][i];
		
	}
	input[length]='\0';
	i=0;
	
	//length=sizeof(input);//correct length not being found
	//printf("size obtained\n");
	//printf("length of input: %d\n", length);
	/*while(input[i]!='\0'){
		printf("%c", input[i]);
		i++;
	}*/
	//printf("\n");
	//printf("%s", input);
	
	//printf("-----------------\n");
	/*while(input[i]!=NULL){
		length++;
		i++;
	}*/
	i=0;
	int j=0;
	int repeat=1;
	//printf("here\n");
	//char curr=input[i];
	//printf("curr = %c\n", curr);
	
	while(i<length){
		//printf("while loop at %d", i);
		char curr=input[i];
		if(isdigit(curr)){
			printf("error");
			exit(0);
			return 0;
		}
		if(curr==' '){
			printf("error");
			exit(0);
			return 0;
		}
		repeat=1;
		j=i+1;
		for(;j<length+1;j++){
			
			char temp=input[j];
			if(curr==temp){
				repeat++;
				if(j==length || (j==length && repeat==1)){
					if(head==NULL){
						struct node * new=(struct node*)malloc(sizeof(struct node));
						new->letter=curr;
						new->value=repeat;
						head=new;
					}
					else if(head!=NULL){
						struct node * new;
						new=head;
						while(new->next!=NULL){
							new=new->next;
						}
						struct node * last=(struct node*)malloc(sizeof(struct node));
						last->letter=curr;
						last->value=repeat;
						new->next=last;
					}
					break;
				}
			}/*
			else if(i==length-1 && repeat==1){
				if(head==NULL){
						struct node * new=(struct node*)malloc(sizeof(struct node));
						new->letter=curr;
						new->value=repeat;
						head=new;
					}
					else if(head!=NULL){
						struct node * new;
						new=head;
						while(new->next!=NULL){
							new=new->next;
						}
						struct node * last=(struct node*)malloc(sizeof(struct node));
						last->letter=curr;
						last->value=repeat;
						new->next=last;
					}
					break;
			}*/
			else if(curr!=temp){
				if(head==NULL){
					struct node * new=(struct node*)malloc(sizeof(struct node));
					new->letter=curr;
					new->value=repeat;
					head=new;
				}
				else if(head!=NULL){
					struct node * new;
					new=head;
					while(new->next!=NULL){
						new=new->next;
					}
					struct node * last=(struct node*)malloc(sizeof(struct node));
					last->letter=curr;
					last->value=repeat;
					new->next=last;
				}
				break;
			}
		}
		repeat=0;
		i=j;
	}
	//printf("reached after whiole\n");
	int compressLength=0;
	i=0;
	struct node * traveler=head;
	while(traveler!=NULL){
		compressLength=compressLength+2;
		traveler=traveler->next;
	}
	//print original
	if(compressLength>length){	
		for(;i<length;i++){
			printf("%c", input[i]);
		}
		//printf("\n");
		return 0;
	}
	//print compressLength;
	traveler=head;
	while(traveler!=NULL){
		printf("%c%d" , traveler->letter, traveler->value);
		traveler=traveler->next;
	}
	//printf("\n");
	return 0;

}
