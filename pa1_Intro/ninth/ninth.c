#include<stdio.h>
#include<stdlib.h>

struct node{
	int value;
	struct node * left;
	struct node * right;
};

struct node * head;
//struct node * deleteListPointer;
int absent=0;
char id;
int num;

int p=0;
char * cprinter;
int * iprinter;

void finder(int, struct node *, int, char);
void deleter(int, struct node*,int);

//pass reference & height and make recursive
void finder(int num, struct node * curr, int height, char id){
	//printf("doing %c at height %d with value %d\n", id, height, num);
	if(head==NULL){
		if(id=='s'){
			cprinter[p]='a';
			iprinter[p]=-1;
			//printf("absent\n");
			return;
		}else{
			struct node * new = (struct node*) malloc(sizeof(struct node));
			head=new;
			height=1;
			new->value=num;
			new->left=NULL;
			new->right=NULL;
			if(id=='i'){
				cprinter[p]='i';
				iprinter[p]=height;
				//printf("inserted %d\n", height);
				absent=1;
				//curr==NULL;
				return;
			}
		}
		 
	}
	height++;
	//curr=head;
	if(curr->value==num){
		height--;
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
				return;
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
				return;
			}
		}
		if(id=='s'){
			if(absent<1){
				cprinter[p]='a';
				iprinter[p]=-1;
				//printf("absent\n");
				absent=1;
				//curr==NULL;
				//free(del);
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
		//
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

void deleter(int num, struct node * curr, int height){//
	//printf("value searching for: %d\n" , num);

	if(curr!=head && curr==NULL){
		cprinter[p]='f';
		iprinter[p]=-1;
		//printf("fail\n");
		absent=1;
		return;
	}
	//printf("past first if (if curr==NULL)\n");
	if(curr==head && curr->value==num){//if root to be deleted
		//printf("target is at the head\n");
		if(curr->left==NULL && curr->right==NULL){//root is only item
			head=NULL;
			//printf("head is null\n");
			
		}
		else if(curr->left==NULL && curr->right!=NULL){//only nodes on right of root
			head=curr->right; 
		}
		else if(curr->left!=NULL && curr->right==NULL){//only nodes on left of root
			head=curr->left;
		}
		else if(curr->left!=NULL && curr->right!=NULL){
			//printf("two kids\n");
			struct node * low = head->right;
			struct node * before=low;
			while(low->left!=NULL){
				before=low;
				low=low->left;
			}
			if(before==low){
				head=low;
				low->left=curr->left;
			}
			else{
				//head=low;
				before->left=low->right;
				low->right=head->right;
				low->left=head->left;
				head=low;
				//printf("head value: %d\n", head->value);
				//printf("head value left: %d\n", head->left->value);
				//printf("head value right: %d\n", head->right->value);
				
			}
		}
		cprinter[p]='s';
		iprinter[p]=-1;
		//printf("success\n");
		absent=1;
		return;
		
	}// new code starts here
	
	//printf("num: %d\n", num);
	//if(curr->right!=NULL)
		//printf("value of right curr before diseried if:::::::::::::::::: %d\n" , curr->right->value);
	if(curr->left!=NULL && curr->right!=NULL){//if curr has two kids
		//printf("it has two kids\n");
		if(curr->left->value==num){//if node to be deleted is on left of curr
			//printf("value is to left of curr\n");
			struct node * del = curr->left;//so del is node to be deleted
			if(del->left==NULL && del->right==NULL){//if no children
				curr->left=NULL;
				//free(del);
				if(absent==0){
					cprinter[p]='s';
					iprinter[p]=-1;	
					//printf("success\n");
					absent=1;
				}
				free(del);
				return;
			}else if(del->left==NULL && del->right!=NULL){//if no left child, and it has a right child
				//printf("has right child but not left\n");
				curr->left=del->right;
				if(absent==0){
					cprinter[p]='s';
					iprinter[p]=-1;
					//printf("success\n");
					absent=1;
				}
				free(del);
				return;
			
			}
			else if(del->left!=NULL && del->right==NULL){//if it has a left child, and no right child
				//printf("has left child but not right\n");
				curr->left=del->left;
				if(absent==0){
					cprinter[p]='s';
					iprinter[p]=-1;
					//printf("success\n");
					absent=1;
				}
				free(del);
				return;
			}
			else if(del->left!=NULL && del->right!=NULL){//if two children
				//printf("it has two kids\n");
				struct node * low = del->right;
				struct node * before=low;
				while(low->left!=NULL){
					before=low;
					low=low->left;
				}
				if(before==low){
						curr->left=low;
						low->left=del->left;
						if(absent==0){
						cprinter[p]='s';
						iprinter[p]=-1;
						//printf("success\n");
						absent=1;
						free(del);
						return;
						}
				}else{
					curr->left=low;
					before->left=low->right;
					low->left=del->left;
					low->right=del->right;
			
					if(absent==0){
						cprinter[p]='s';
						iprinter[p]=-1;
						//printf("success\n");
						absent=1;
					}
					free(del);
					return;
				}
			}
		}
			
			
		
		
		else if(curr->right->value==num){//if node to be deleted is on right of curr
			struct node * del = curr->right;//so del is the node to be deleted
			//printf("value is to right of curr");
				if(del->left==NULL && del->right==NULL){//if no children
					curr->right=NULL;
					//free(del);
					if(absent==0){
					cprinter[p]='s';
					iprinter[p]=-1;
					//printf("success\n");
					absent=1;
					}
					free(del);
					return;
				}
				else if(del->left==NULL && del->right!=NULL){//if no left child, and it has a right child
					//printf("right has child, left does not\n");
					curr->right=del->right;
					if(absent==0){
					cprinter[p]='s';
					iprinter[p]=-1;
					//printf("success\n");
					absent=1;
					}
					free(del);
					return;
				}
				else if(del->left!=NULL && del->right==NULL){//if it has a left child, and no right child
					//printf("left has child, right does not\n");
					curr->right=del->left;
					if(absent==0){
					cprinter[p]='s';
					iprinter[p]=-1;
					//printf("success\n");
					absent=1;
					}
					free(del);
					return;
				}
				else if(del->left!=NULL && del->right!=NULL){//if two children
					struct node * low = del->right;
					//printf("it has two children\n");
					struct node * before=low;
					while(low->left!=NULL){
						before=low;
						low=low->left;
					}
					if(before==low){
						curr->right=low;
						low->left=del->left;
						if(absent==0){
						cprinter[p]='s';
						iprinter[p]=-1;
						//printf("success\n");
						absent=1;
						free(del);
						return;
						}
					}else{
					curr->right=low;
					before->left=low->right;
					low->left=del->left;
					low->right=del->right;
					if(absent==0){
						cprinter[p]='s';
						iprinter[p]=-1;
						//printf("success\n");
						absent=1;
						}
						free(del);
					return;
					}
				}
			}
	
		else if(num<curr->value){
			//printf("1\n");
			curr=curr->left;
			deleter(num, curr, id);
		}
		else if(num>curr->value){
			//printf("2\n");
			curr=curr->right;
			deleter(num, curr, id);
		}
	}
	else if(curr->left==NULL && curr->right!=NULL){//so if only right child
		if(curr->right->value==num){
		//printf("it only has right child and curr->right is num\n");
			struct node * del = curr->right;//so del is the node to be deleted
			if(del->left==NULL && del->right==NULL){//if no children
				curr->right=NULL;
				//free(del);
				if(absent==0){
					cprinter[p]='s';
					iprinter[p]=-1;
					//printf("success\n");
					absent=1;
				}
				free(del);
				return;
			}
			else if(del->left==NULL && del->right!=NULL){//if no left child, and it has a right child
				//printf("has right child, no left child\n");
				curr->right=del->right;
				if(absent==0){
					cprinter[p]='s';
					iprinter[p]=-1;
					//printf("success\n");
					absent=1;
				}
				free(del);
				return;
			}
			else if(del->left!=NULL && del->right==NULL){//if it has a left child, and no right child
				//printf("has left child, no right child");
				curr->right=del->left;
				if(absent==0){
					cprinter[p]='s';
					iprinter[p]=-1;
					//printf("success\n");
					absent=1;
				}
				free(del);
				return;
			}
			else if(del->left!=NULL && del->right!=NULL){//if two children
				//printf("has two children\n");
				struct node * low = del->right;
				struct node * before=low;
				while(low->left!=NULL){
					before=low;
					low=low->left;
				}
				
				if(before==low){
						curr->right=low;
						low->left=del->left;
						if(absent==0){
						cprinter[p]='s';
						iprinter[p]=-1;
						//printf("success\n");
						absent=1;
						free(del);
						return;
						}
				}else{
				
					curr->left=low;
					before->left=low->right;
					low->left=del->left;
					low->right=del->right;
					if(absent==0){
						cprinter[p]='s';
						iprinter[p]=-1;
						//printf("success\n");
						absent=1;
					}
					free(del);
					return;
				}
			}
			
		
		}
		else if(num>curr->value){
			curr=curr->right;
			deleter(num, curr, id);
		}
		else{
			cprinter[p]='f';
			iprinter[p]=-1;
			//printf("fail\n");
			absent=1;
			return;
		}
	}
	else if(curr->left!=NULL && curr->right==NULL){//so if only left child
		//printf("curr has only left child\n");
		if(curr->left->value==num){
			//printf("left of curr is num\n");
			struct node * del = curr->left;//so del is node to be deleted
			if(del->left==NULL && del->right==NULL){//if no children
				curr->left=NULL;
				if(absent==0){
					cprinter[p]='s';
					iprinter[p]=-1;
					//printf("success\n");
					absent=1;
				}
				free(del);
				return;
			}else if(del->left==NULL && del->right!=NULL){//if no left child, and it has a right child
				//printf("has right child, no left child\n");
				curr->left=del->right;
				if(absent==0){
					cprinter[p]='s';
					iprinter[p]=-1;
					//printf("success\n");
					absent=1;
				}
				free(del);
				return;
			
			}
			else if(del->left!=NULL && del->right==NULL){//if it has a left child, and no right child
				//printf("has left child, no right child");
				curr->left=del->left;
				if(absent==0){
					cprinter[p]='s';
					iprinter[p]=-1;
					//printf("success\n");
					absent=1;
				}
				free(del);
				return;
			}
			else if(del->left!=NULL && del->right!=NULL){//if two children
				//printf("has two children\n");
				struct node * low = del->right;
				struct node * before=low;
				while(low->left!=NULL){
					before=low;
					low=low->left;
				}
				if(before==low){
						curr->left=low;
						low->left=del->left;
						if(absent==0){
						cprinter[p]='s';
						iprinter[p]=-1;
						//printf("success\n");
						absent=1;
						free(del);
						return;
						}
					}
				curr->left=low;
				before->left=low->right;
				low->left=del->left;
				low->right=del->right;
			
				if(absent==0){
					cprinter[p]='s';
					iprinter[p]=-1;
					//printf("success\n");
					absent=1;
				}
				return;
			
			}
		}
		else if(num<curr->value){
			curr=curr->left;
			deleter(num, curr, id);
		}
		else{
			cprinter[p]='f';
			iprinter[p]=-1;
			//printf("fail\n");
			absent=1;
			return;
		}
	}
	if(absent==0){
		cprinter[p]='f';
		iprinter[p]=-1;
		//printf("fail\n");
		absent++;
		return;
	}
	return;
}

int main(int argc, char ** argv){
	FILE *fp=NULL;
	char *fn=NULL;
	if(argc!=2){
		printf("error");
		exit(0);
		return 0;
	}
	fn=argv[1];
	
	
	
	fp=fopen(fn, "r");
	if(fp==NULL){
		printf("error");
		exit(0);
		return 0;
	}
	int L2=0;
	while(!feof(fp)){
		fscanf(fp, "%c %d\n", &id, &num);
		L2++;
	}
	fclose(fp);
	//printf("l2: %d\n", L2);
	
	cprinter=(char *) malloc(L2*sizeof(char));
	iprinter=(int *) malloc(L2*sizeof(int));
	
	fp=fopen(fn, "r");
	int height=0;
	struct node * curr=head;
	//struct node * d=deleteListPointer;
	while(!feof(fp)){
		curr=head;
		//d=deleteListPointer;
		absent=0;
		fscanf(fp, "%c %d\n", &id, &num);
		//printf("id %c and num %d\n", id, num);
		if(id!='i' && id!='s' && id!='d'){
			printf("error");
			return 0;
		}
		
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
	 	
	 	else if(id=='d'){
	 		deleter(num, curr, height);
	 		height=1;
	 		p++;/*
	 		struct node * noob=(struct node*)malloc(sizeof(struct node));
	 		while(d!=NULL){
	 			if(d->value==num){
	 				printf("fail\n");
	 				absent=1;
	 			}
	 			d=d->left;
	 		}
	 		if(d==NULL && absent==0){
	 			noob->value=num;
	 			noob->left=deleteListPointer;
	 			deleteListPointer=noob;
	 			deleter(num, curr, height);
	 			height=1;
	 		}*/
	 	}
	 	//if(head!=NULL)
	 		//printf("head value: %d\n", head->value);
	 	//printf("/////////////////////////////////////////////////////////\n");
	 	
	 }
	 int yes=0;
	 for(;yes<L2;yes++){
	 	if(cprinter[yes]=='i'){
	 		printf("inserted %d", iprinter[yes]);
	 	}
	 	else if(cprinter[yes]=='a'){
	 		printf("absent");
	 	}
	 	else if(cprinter[yes]=='d'){
	 		printf("duplicate");
	 	}
	 	else if(cprinter[yes]=='f'){
	 		printf("fail");
	 	}
	 	else if(cprinter[yes]=='s'){
	 		printf("success");
	 	}
	 	else if(cprinter[yes]=='p'){
	 		printf("present %d", iprinter[yes]);
	 	}
	 	if(yes<L2-1){
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
