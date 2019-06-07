#include<stdio.h>
#include<stdlib.h>

int main(int argc, char ** argv){
	FILE *fp=NULL;
	char *fn=NULL;
	if(argc!=2){
		printf("error");
		return 0;
	}
	fn=argv[1];
	fp=fopen(fn,"r");
	if(fp==NULL){
		printf("error");
		exit(0);
		return 0;
	}
	
	int dim=0;// the dimension of matrix, so if its 3x3, dim=3
	int power=0;// the power the matrix is to be raised to
	fscanf(fp, "%d\n" , &dim);//reading dim
	//printf("dimensions are %d\n" , dim);
	
	int *matrix = (int*) malloc(dim*dim *sizeof(int));//allocating matrix space
	int *keeper = (int*) malloc(dim*dim *sizeof(int));//keeps the original matrix in tact for power>2
	int *answer = (int*) malloc(dim*dim *sizeof(int));
	//printf("after malloc\n");
	int curr=0;
	int i=0;
	while(i<(dim*dim)){
		
		fscanf(fp, "%d\n", &curr);
		/*if(i==(dim*dim)){//if all parts of matrix read, this gets final line from file (power)
			fscanf(fp, "%d\n", &power);
			break;
		}*/
		//printf("after if in while at %d\n", i);
		//
		matrix[i]=curr;
		keeper[i]=curr;
		curr=0;
		i++;
		
	}
	fscanf(fp, "%d\n", &power);
	//printf("power %d : \n" , power);
	
	int holder=0;//holds value to be stored in that matrix spot once multi is done
	int j=0;//to cycle through list in order to multiply and add
	int k=0;
	int end=0;
	int input=0;
	int place;
	int temp=power;
	int w=0;
	while(temp!=1){
		for(k=0;k<(dim*dim);k=k+dim){
			input=k;
			end=0;
			while(end<dim){
				i=k;
				place=end;
				holder=0;
				while(j<dim && place<(dim*dim)){
					holder=holder+(matrix[i] * keeper[place]);
					//printf("matrix[i] (%d) and keeper[place] (%d) multiplied to get %d\n", matrix[i], keeper[place], holder);
					i++;
					place=place+dim;
					j++;
				}
				end++;
				j=0;
				//matrix[input]=/*matrix[input]*/holder;
				answer[input]=holder;
				//printf("matrix position %d value just inserted : %d at temp %d\n", input, matrix[input], temp);
				input++;
				i=k;
				holder=0;
				//printf("----------------------------------------------------------------------------------\n");
			
			}
			//holder=0;
		
		}
		for(w=0; w<(dim*dim); w++){
				matrix[w]=answer[w];
		}
		
		temp--;
	}
	int h=0;
	int d=0;
	for(h=0; h<(dim*dim);h++){
		if(d==dim){
			printf("\n");
			d=0;
		}
		printf("%d\t", matrix[h]);
		d++;
	}
	/*int f=0;
	int fc=0;//curr while printing
	for(f=0;f<(dim*dim); f++){
		fc=matrix[f];
		printf("%d\t", fc);
	}
	printf("\n");
	for(f=0;f<(dim*dim); f++){
		fc=keeper[f];
		printf("%d\t", fc);
	}*/
	//printf("\n");
	return 0;
}













