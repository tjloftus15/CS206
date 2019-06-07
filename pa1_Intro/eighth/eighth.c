#include<stdio.h>
#include<stdlib.h>

struct node{
	int value;
	struct node * left;
	struct node * right;
};

struct node * head;
char * cprinter;//holds result char
int * iprinter;//holds height. Is -1 if duplicate
int p=0;
int absent=0;
//pass reference & height and make recursive
void finder(int num, struct node * curr, int height, char id){
	//printf("doing %c at height %d with value %d\n", id, height, num);
	if(head==NULL){
		struct node * new = (struct node*) malloc(sizeof(struct node));
		head=new;
		height=1;
		new->value=num;
		new->left=NULL;
		new->right=NULL;
		cprinter[p]='i';
		iprinter[p]=height;
		//printf("inserted %d\n", height);
		absent=1;
		//curr==NULL;
		return;
	}
	height++;
	//curr=head;
	if(curr->value==num){
		height--;
		if(id=='s'){//number is present
			cprinter[p]='p';
			iprinter[p]=height;
			//printf("present %d\n", height);
			absent=1;
			//curr==NULL;
			return;
		}
		if(id=='i'){//it is duplicate
			cprinter[p]='d';
			iprinter[p]=-1;
			//printf("duplicate\n");
			absent=1;
			return;
		}
	}
	if(curr->left!=NULL && curr->right!=NULL){
		//printf("inside main if\n");
		if(num<curr->value){
			curr=curr->left;
			//height++;
			finder(num, curr, height, id);
		}
		else if(num>curr->value){
			curr=curr->right;
			//height++;
			finder(num, curr, height, id);
		}
	}
	else if(curr->left!=NULL && num<curr->value){
		//printf("if only left node\n");
		curr=curr->left;
		//height++;
		finder(num, curr, height, id);
		
	}
	else if(curr->right!=NULL && num>curr->value){
		//printf("if only right node\n");
		curr=curr->right;
		//height++;
		finder(num, curr, height, id);
	}
	//height--;
	if(curr->left==NULL && num<curr->value){
		//make recursive here
		if(curr->value==num){
			if(id=='s'){
				cprinter[p]='p';
				iprinter[p]=height;
				//printf("present %d\n", height);
				absent=1;
				//curr==NULL;
				return;
			}
			if(id=='i'){
				cprinter[p]='d';
				iprinter[p]=-1;
				//printf("duplicate\n");
				absent=1;
			}
		}
		if(id=='s'){
			if(absent<1){
				cprinter[p]='a';
				iprinter[p]=-1;
				//printf("absent\n");
				absent=1;
				//curr==NULL;
				return;
			}
			else if(absent>=1){
				return;
			}
		}
		struct node * new = (struct node*) malloc(sizeof(struct node));
		
		curr->left=new;
		new->value=num;
		new->left=NULL;
		new->right=NULL;
		cprinter[p]='i';
		iprinter[p]=height;
		//printf("inserted %d\n", height);
		absent=1;
		//curr==NULL;
		return;
		
	}
	else if(curr->right==NULL && num>curr->value){
		//make recursive here
		if(curr->value==num){
			if(id=='s'){
				cprinter[p]='p';
				iprinter[p]=height;
				//printf("present %d\n", height);
				absent=1;
				//curr==NULL;
				return;
			}
			if(id=='i'){
				cprinter[p]='d';
				iprinter[p]=-1;
				//printf("duplicate\n");
				absent=1;
			}
		}
		if(id=='s'){
			if(absent<1){
				cprinter[p]='a';
				iprinter[p]=-1;
				//printf("absent\n");
				absent=1;
				//curr==NULL;
				return;
			}
			else if(absent>=1){
				return;
			}
		}
		struct node * new = (struct node*) malloc(sizeof(struct node));
		curr->right=new;
		new->value=num;
		new->left=NULL;
		new->right=NULL;
		cprinter[p]='i';
		iprinter[p]=height;
		//printf("inserted %d\n", height);
		absent=1;
		//curr==NULL;
		return;
	}
	/*if(curr==NULL){
		return;
	}*/
	
	if(absent==0){
		cprinter[p]='a';
		iprinter[p]=-1;
		//printf("absent\n");
		absent++;
		return;
	}
	
	
	
	//printf("----------------------------\n");
	return;
}

/*
void insert(int, int);
void search(int, int);

char * tree;

void insert(int num, int length){
	//printf("number to insert : %d\n", num);
	//printf("length passed: %d\n", length);
	int i=0;
	int height=1;
	if(tree[0]==' '){
		char n=num+'0';
		tree[i]=n;
		//printf("char inserted : %c\n", n);
		printf("inserted %d\n", height);
		return;
	}
	else if(tree[i]!=' '){
		while(i<length){
			if(tree[i]==' '){
				char n=num+'0';
				tree[i]=n;
				//printf("char inserted : %c\n", n);
				printf("inserted %d\n", height);
				return;
			}
			int curr=tree[i]-'0';
			if(num==curr){
				printf("duplicate %d\n", height);
				return;
			}
			else if(num<curr){
				i=2*i+1;
				height++;
				continue;
			}
			else if(num>curr){
				i=2*i+2;
				height++;
				continue;
			}
		}
	}
	return;
}
void search(int num, int length){
	int i=0;
	int height=1;
	while(i<length){
		if(tree[i]==' '){
			printf("absent\n");
			return;
		}
		int curr=tree[i]-'0';
		if(num==curr){
			printf("present %d\n", height);
			return;
		}
		else if(num<curr){
			i=2*i+1;
			height++;
			continue;
		}
		else if(num>curr){
			i=2*i+2;
			height++;
			continue;
		}
	}
	printf("absent\n");
	return;
}
	

*/
int main(int argc, char ** argv){
	FILE *fp=NULL;
	char *fn=NULL;
	if(argc!=2){
		printf("error");
		exit(0);
		return 0;
	}
	fn=argv[1];
	
	char id;
	int num;
	
	fp=fopen(fn, "r");
	if(fp==NULL){
		printf("error");
		exit(0);
		return 0;
	}
	int Len=0;
	//int LL=0;
	while(!feof(fp)){
		fscanf(fp, "%c %d\n", &id, &num);
		Len++;
	}
	fclose(fp);
	fp=fopen(fn, "r");
	cprinter=(char *) malloc(Len*sizeof(char));
	iprinter=(int *) malloc(Len*sizeof(int));
	//head;/
	/*
	int i=0;
	int numLines=0;
	while(!feof(fp)){
		fscanf(fp, "%c %d\n", &id, &num);
		numLines++;
	
	}
	fclose(fp);
	//printf("num of lines : %d\n", numLines);
	
	fp=fopen(fn, "r");
	int linesLeft=numLines;
	int k=0;*/
	/*
	while(linesLeft!=0){
		k=2*k+2;
		linesLeft--;
	}
	printf("one sided tree total spaces needed: %d\n", k);
	i=0;*/
	//tree=(char *) malloc(k*sizeof(char));
	//i=0;
	/*for(;i<k;i++){
		tree[i]=' ';
	}*/
	int height=0;
	struct node * curr=head;
	while(!feof(fp)){
		if(id!='i' && id!='s'){
			printf("error");
			return 0;
		}
		curr=head;
		absent=0;
		fscanf(fp, "%c %d\n", &id, &num);
	 	if(id=='i'){
	 		finder(num, curr, height,id);
	 		height=1;
	 		p++;
	 	}
	 	else if(id=='s'){
	 		
	 		finder(num, curr, height, id);
	 		height=1;
	 		p++;
	 	}
	 	
	 }
	 int r=0;
	 for(;r<Len;r++){
	 	if(cprinter[r]=='a'){
	 		printf("absent");
	 	}
	 	else if(cprinter[r]=='d'){
	 		printf("duplicate");
	 	}
	 	else if(cprinter[r]=='i'){
	 		printf("inserted %d", iprinter[r]);
	 	}
	 	else if(cprinter[r]=='p'){
	 		printf("present %d", iprinter[r]);
	 	}
	 	if(r<Len-1){
	 		printf("\n");
	 	}
	 }
	 free(cprinter);
	 free(iprinter);
	 fclose(fp);
	// free(tree);
	 //clear(tree);
	 //print here
	 return 0;
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
}
