#include<stdio.h>
#include <stdlib.h>

struct node *head=NULL;

struct node {
	int value;
	struct node *next;

};
/*
struct * node traverse(){
	struct * node traveler=head;
	while(head->next!=NULL){
		traveler=head->next;
	}
	return traveler;
}*/

void print(){
	struct node * t=head;
	int count=0;
	//printf("HERE\n");
	while(t!=NULL){
		count++;
		t=t->next;
	}
	printf("%d\n", count);
	t=head;
	while(t!=NULL){
		printf("%d\t", t->value);
		t=t->next;
	}
	//printf("\n");
	return;
}

void insert(int num){
	if(head==NULL){
		struct node *temp=malloc(sizeof(struct node));//creates first node
		temp->value=num;
		temp->next=NULL;
		head=temp;
		return;
	}
	struct node *temp=head;
	struct node *before;
	//int count=0;
	while(temp!=NULL){ //searches for value until end of list
		if(temp->value==num){
			return;
		}
		if(temp->value > num){//if num is smaller than current node's value (found where it goes)
			struct node *new=malloc(sizeof(struct node));
			//printf("right before line 46 error\n");
			if(temp==head){//if num is smaller than entire list
				//printf("line 46 error\n");
				//printf("value of head %d\n" , head->value);
				new->next=temp;
				
				new->value=num;
				//printf("value of new %d\n" , new->value);
				head=new;
				//printf("value of head %d\n" , head->value);
				return;
			}
			before->next=new;
			new->next=temp;
			new->value=num;
			return;
			
		}
		before=temp;//keeps tract of one before (or last visited node)
		temp=temp->next;//moves pointer to next node
	}
	if(temp==NULL){ //if num is largest in list
			//printf("largest value\n");
			struct node *last=head;
			while(last->next!=NULL){
				last=last->next;
			}
			temp= malloc(sizeof(struct node));
			last->next=temp;
			temp->next=NULL;
			temp->value=num;
	}
	return;
	
}

void delete(num){
	//printf("delete function reached\n");
	if(head==NULL){//if nothing in list
		return;
	}/*else if(head->next==NULL && head->value==num){//this line is problem, line 92 error never reached.
		head=NULL;
		return;
	}*/
	//printf("past first if\n");
	struct node *temp=head->next;
	struct node *before=head;
	if(before->value==num){
		head=before->next;
		before->next=NULL;
		return;
	}
	//printf("right before while\n");
	while(temp!=NULL){
		//printf("inside while\n");
		//maybe use head to change any pointer since global
		if(temp->value==num){
			//printf("found right node\n");
			if(temp->next==NULL){
				//printf("line 92 delete error\n");
				before->next=NULL;
				return;
			}
			//printf("middle node\n");
			before->next=temp->next;
			return;
		}
		before=temp;
		temp=temp->next;
	}
	/*if(temp->value==num){
		//printf("line 92 delete error\n");
		//before->next==NULL;
		return;*/
	//}
	return;
	
}






int main(int argc, char ** argv){
	FILE *fp=NULL; //stands for file pointer
	char *fn=NULL; //stands for filename
	if(argc!=2){ //checks to see if txt file passed
		printf("error");
		exit(0);
	}
	fn=argv[1];
	
	char id; //stands for identification of operation from file
	int num; //the number value found in txt file
	
	fp=fopen(fn, "r");//tries to open file specified;
	if(fp==NULL){//if file not found
		//FILL ME IN -------------------how to properly tell of error ????????
		//printf("error locating file\n");
		printf("error");
		exit(0);
		return 0;
	}
	while(!feof(fp)){ //searching for end of file. returns true when eof reached
		fscanf(fp, "%c %d\n", &id, &num);
		/*if(num==NULL){
			return 0;
		}*/
		
		//printf("read values %c\t%d\n", id, num);
		if(id=='i'){
			//printf("insert\n");
			insert(num);
		}
		else if(id=='d'){
			delete(num);
		}
		//print();
	}
	if(head==NULL){
		printf("0");
		//printf("\n");
		return 0;
	}
	print();
	fclose(fp);
		
	return 0;
}








