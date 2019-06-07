#include<stdio.h>
#include<stdlib.h>

void addCols(int);
void addRows(int);
void addDiags(int);


int* sums; //array to hold all sums (has column sums=dim, row sums=dim, diag sums=dim-1)
int s=0; //counter for next open position in sums array
int *matrix;//array to store the matrix


void addCols(int dim){
	int i=0;
	int j=0;
	int sum=0;
	while(i<dim){
		j=i;
		while(j<(dim*dim)){
			sum=sum+matrix[j];
			j=j+dim;
		}sums[s]=sum;
		i++;
		s++;
		sum=0;
	}
}

void addRows(int dim){
	int i=0;
	int j=0;
	int sum=0;
	int c;
	while(i<(dim*dim)){
		j=i;
		c=0;
		while(c<dim){
			sum=sum+matrix[j];
			j=j+1;
			c++;
		}sums[s]=sum;
		s++;
		i=i+dim;
		sum=0;
		
	}
}

void addDiags(int dim){
	int i=0;
	int sum=0;
	while(i<(dim*dim)){//left to right diagonal
		sum=sum+matrix[i];
		i=i+1+dim;
	}
	sums[s]=sum;
	sum=0;
	s++;
	i=dim-1;
	
	while(i<(dim*dim-1)){//right to left diagonal
		sum=sum+matrix[i];
		i=i+dim-1;
	}
	sums[s]=sum;
	s++;
}




int main(int argc, char ** argv){
	FILE *fp=NULL;
	char *fn=NULL;
	if(argc!=2){
		printf("error\n");
		return 0;
	}
	fn=argv[1];
	fp=fopen(fn, "r");
	if(fp==NULL){
		printf("error");
		exit(0);
		return 0;
	}
	int dim=0;
	fscanf(fp, "%d\n", &dim);
	//printf("dimensions are %d\n" , dim);
	
	matrix= (int*) malloc(dim*dim*sizeof(int));
	s=0;
	
	int curr=0;
	int i=0;
	
	while(i<(dim*dim)){
		fscanf(fp, "%d\n", &curr);
		matrix[i]=curr;
		curr=0;
		i++;
	}
	
	int j=0;
	curr=0;//the value to be compared in matrix
	int temp=0;//the second value in the matrix
	for(i=0; i<(dim*dim); i++){//makes sure all number are unique
		curr=matrix[i];
		if(curr<=0 || curr>(dim*dim)){
			printf("not-magic");
			return 0;
		}
		if((i+1)==(dim*dim)){
			break;
		}
		for(j=i+1; j<(dim*dim); j++){
			temp=matrix[j];
			if(temp<=0 || temp>(dim*dim)){
				printf("not-magic");
				return 0;
			}
			if(curr==temp){//all numbers are not unique ---------------------
				printf("not-magic");
				return 0;
			}
		}
	
	}
	sums= (int*) malloc(dim*dim*sizeof(int));
	/*for(i=0; i<(dim*dim);i++){
		sums[i]=NULL;
	}*/
	addCols(dim);
	addRows(dim);
	addDiags(dim);
	/*if(s==(dim*3-1)){
		printf("correct sums found\n");
	}*/
	/*for(i=0; i<dim*3-1; i++){
		printf("%d\t" , sums[i]);
	}
	printf("\n");*/
	i=0;
	j=1;
	while(i<(dim*3-2) && j<(dim*3-1)){//checks to see if all sums are equal
		//printf("value of i, %d and j, %d\n", i, j);
		if(sums[i]!=sums[j]){
			printf("not-magic");
			return 0;
		}
		i++;
		j++;
	}
	
	printf("magic");
	free(matrix);
	free(sums);
	fclose(fp);
	
	
	
	
	
	
	
	
	return 0;
}
