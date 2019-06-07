#include<stdlib.h>
#include<stdio.h>
//#include"learn.h"
//#include"learn.h"
void finalPrint(double **, int, int);
//void progressPrint(double **, int, int);
//void flipper(double**, int, int);
void inverter(double**, int, int);
void transposer(double**, int, int);
void multiplier(double**, int, int, double **, int, int);
//void mpracticer(double **);

//W=(Xt X)^-1 Xt Y
/*
double * X; //X, will modify this throughout
double * trainHolder;//holds original X values
double * trainTranspose;//the transpose of the original X
double * trainInverse;//the inverse of the original X
double * Y;
double * test;
double * answer;//final answer of x * W = Y
int K;
int ccols, crows, ctotalDim;//dimensions
int trows, tcols, ttotalDim;
int xrows, xcols, xtotalDim;*/
//double ** F;flipped version
double ** In;//inverse
double ** Hx;//holder!!!!!!!!!!! for X
double ** T;//transposed matrix
double ** X; //train
double ** Y; //house prices from train 
double ** Z; //test
//double ** practice;
int ccols, crows, ctotalDim;
int R, C, totalDim, K;
int trows, tcols, ttotalDim;
int irows, icols, itotalDim;



void finalPrint(double ** a, int row, int col){
	int i=0;
	double value;
	while(i<row){
		value=a[i][0];
		printf("%0.0lf\n", value);
		i++;
	}
}/*
void practicer(double ** a){
	int prows;
	int pcols;
	
	printf("please enter number of rows.\n");
	scanf("%d\n", &prows);
	printf("please enter number of cols.\n");
	scanf("%d\n", &pcols);
	a=(double**)malloc(prows*sizeof(double*));
	
	int i=0;
	int j=0;
	while(i<prows){
		a[i]=(double*)malloc(pcols*sizeof(double));
		i++;
	}
	i=0;
	j=0;
	double hi=0;
	while(i<prows){
		printf("enter value\n: ");
		scanf("%lf", &hi);
		a[i][j]=hi;
		j++;
		if(j==pcols){
			i++;
			j=0;
		}
	}
	transposer(a, prows, pcols);
	
}*/
/*void progressPrint(double ** a, int row, int col){
	int i=0;
	//int n=0;
	int j=0;
	int place=0;
	while(i<row){
		if(j==col){
			i++;
			if(i==row){
				return;
			}
			j=0;
			//place=0;
			printf("\n");
		}
		printf("%d) %lf\n", place, a[i][j]);
		j++;
		place++;
	}
	printf("==================================================\n");
}*/

void transposer(double ** a, int r, int c){
	int row=c;
	int col=r;
	
	double ** b = (double**)malloc(row*sizeof(double*));
	int i=0;
	int j=0;
	while(i<row){
		b[i]=(double*)malloc(col*sizeof(double));
		i++;
	}
	
	i=0;//belongs to transpose (row)
	j=0;//belongs to transpose (col)
	int k=0;//belong to X (row)
	int t=0;//belong to X (col)
	while(k<row){
		//printf("inside loop\n");
		while(i<r){
			b[k][t]=a[i][j];
			i++;
			t++;
		}
		j++;
		k++;
		i=0;
		t=0;
	}
	//progressPrint(b, row, col);
	T=b;
	trows=row;
	tcols=col;
	//progressPrint(T, trows, tcols);
	return;
}

void multiplier(double ** a, int r1, int c1, double ** b, int r2, int c2){
	int i=0;
	int j=0;
	int curr1=0;
	int curr2=0;
	int k=0;
	int t=0;
	crows=r1;
	ccols=c2;
	double sum=0;
	double ** c = (double **)malloc(crows*sizeof(double*));
	while(i<crows){
		c[i]=(double*)malloc(ccols*sizeof(double));
		i++;
	}
	//printf("after first while\n");
	i=0;
	while(i!=r1){
		//printf("inside first while\n");
		while(t!=c2){
			while(k<r2){
				//printf("found value of a[%d][%d]= %lf\n", i, j, a[i][j]);
				//printf("found value of b[%d][%d]= %lf\n", k, t, b[k][t]);
				//printf("-------------------------------------------------\n");
				sum=sum+a[i][j]*b[k][t];
				//printf("sum found: %lf\n", sum);
				k++;
				j++;
			}
			c[curr1][curr2]=sum;
			//printf("///////////////////////////////////\n");
			//printf("sum added: %lf\n", sum);
			//printf("///////////////////////////////////\n");
			curr2++;
			if(curr2==ccols){
				curr1++;
				curr2=0;
			}
			sum=0;
			j=0;
			t++;
			k=0;
		}
		i++;
		k=0;
		t=0;
		j=0;
	}
	X=c;
	//progressPrint(X, crows, ccols);
	return;
}

void inverter(double ** a, int r, int c){
	
	irows=r;
	icols=c;
	In=(double**)malloc(irows*sizeof(double*));
	int p=0;
	while(p<irows){
		In[p]=(double*)malloc(icols*sizeof(double));
		p++;
	}
	int augCols=c*2;
	int augRows=r;
	double ** aug = (double**)malloc(augRows*sizeof(double*));
	int i=0;
	while(i<augRows){
		aug[i]=(double*)malloc(augCols*sizeof(double));
		i++;
	}
	i=0;
	int j=0;
	while(i<augRows){//created augmented matrix
		j=0;
		while(j<c){
			aug[i][j]=a[i][j];
			j++;
		}
		while(j<augCols){
			aug[i][j]=0.0;
			j++;
		}
		i++;
	}
	j=c;
	i=0;
	while(i<augRows){
		aug[i][j]=1.0;
		j++;
		i++;
	}
	//printf("augmented matrix before invertion\n");
	//progressPrint(aug, augRows, augCols);
	double curr=0;
	double next=0;
	i=0;
	j=0;
	int Q;//i in traversal
	int W;//j in traVERSAL
	int movew;
	int movej;
	
	while(i<augRows){//makes below pivot points to be zero
		//printf("inside below pivot while\n");
		curr=aug[i][j];
		//printf("value of curr: %lf\n", curr);
		if(curr!=1){
			Q=i;
			W=j;
			while(W<augCols){
				//printf("aug[Q][W] = %lf\n", aug[Q][W]);
				aug[Q][W]=aug[Q][W]/curr;
				//printf("aug[Q][W] = aug[Q][W]/curr = aug[%d][%d]/%lf = %lf\n", Q, W, curr, aug[Q][W]);
				W++;
			}
		}
		
		if(i==augRows-1){
			break;
		}
		curr=aug[i][j];
		//printf("curr after made 1\n");
		Q=i+1;
		W=j;
		int per=0;
		while(Q<augRows){
			
			next=aug[Q][W];
			
			if(next!=0.0){
				//if(next>1 && next<
				//printf("next = %lf\n", next);
				
				movew=W;
				movej=j;
				while(movew<augCols){
					//aug[Q][movew]=aug[i][movej]*next-aug[Q][movew];
					aug[Q][movew]=aug[Q][movew]-aug[i][movej]*next;
					per++;
					//printf("opperation performed for %d time\n", per);
					movew++;
					movej++;
				}
				per=0;
			}
			Q++;
		}
		i++;
		j++;
	}
	/*printf("all pivots below should be zero:\n");
	progressPrint(aug, augRows, augCols);*/
	
	i=1;
	j=1;
	Q=i-1;
	W=j;
	
	//printf("after below pivot while\n");
	while(i<augRows){//makes above pivots to be zero
		//printf("inside while\n");
		Q=i-1;
		W=j;
		while(Q>=0){
			
			next=aug[Q][W];
			
			if(next!=0){
				
				movew=W;
				movej=j;
				while(movew<augCols){
					//aug[Q][movew]=aug[i][movej]*next-aug[Q][movew];
					aug[Q][movew]=aug[Q][movew]-aug[i][movej]*next;
					//aug[moveQ][moveW]=aug[movei][movej]-aug[moveQ][moveW]*next;
					movew++;
					movej++;
				}
				
			}
			
			Q--;
		}
		i++;
		j++;
	}
	i=0;
	j=c;
	int j2=0;
	while(i<augRows){
		while(j<augCols){
			In[i][j2]=aug[i][j];
			j++;
			j2++;
		}
		i++;
		j=c;
		j2=0;
		
		
	}
	/*printf("\n");
	printf("augmented after inversion\n");
	progressPrint(aug, augRows, augCols);
	printf("\n");*/
	//X=In;
	//progressPrint(In, irows, icols);
	
	
}

int main(int argc, char ** argv){
	FILE *fp=NULL;
	char *fn=NULL;
	if(argc!=3){
		printf("error");
		exit(0);
		return 0;
	}
	fn=argv[1];
	double value=0;
	int i=0;
	fp=fopen(fn,"r");
	if(fp==NULL){
		printf("error");
		exit(0);
		return 0;
	}
	//attributes
	
	fscanf(fp, "%d", &K);//sets number of rows, below adds one for attributes
	C=K+1;
	fscanf(fp, "%d", &R);//sets number of rows
	totalDim=R*C;
	//printf("# of rows: %d , # of cols: %d , with total diminesions of %d\n", R, C, totalDim);
	Hx=(double **)malloc(R*sizeof(double*));
	X=(double **)malloc(R*sizeof(double*));
	Y=(double **)malloc(R*sizeof(double*));
	i=0;
	while(i<R){
		X[i]=(double*) malloc(C*sizeof(double));
		Hx[i]=(double*) malloc(C*sizeof(double));
		Y[i]=(double*) malloc(1*sizeof(double));
		i++;
	}
	i=0;
	int j=0;
	int xc=0;//Y counter
	int y=0;//place in Y
	char hold;
	while(!feof(fp)){//ttrain assigned: holder matrix, transpose matrix, and basic matrix
		if(i>=R){
			break;
		}
		if(j==0){
			X[i][j]=1.0;
			Hx[i][j]=1.0;
			j++;
			continue;
		}
		if(j==C-1){
			fscanf(fp, "%lf %c", &value, &hold);
			X[i][j]=value;
			Hx[i][j]=value;
			j=0;
			i++;
			fscanf(fp, "%lf", &value);
			Y[y][0]=value;
			y++;
			continue;
		}
			fscanf(fp, "%lf %c", &value, &hold);
			X[i][j]=value;
			Hx[i][j]=value;
			j++;
	}
	
	i=0;
	j=0;
	fclose(fp);
	fn=argv[2];
	fp=fopen(fn, "r");
	if(fp==NULL){
		printf("error");
		exit(0);
		return 0;
	}
	
	//'test' matrix
	int zCols=K+1;
	int zRows;
	i=0;
	
	xc=0;
	
	fscanf(fp, "%d", &zRows);//finds number of house prices to estimate
	int zDim=zRows*zCols;
	
	Z=(double **) malloc(zDim*sizeof(double));
	while(i<zRows){
		Z[i]=(double *)malloc(zCols*sizeof(double));
		i++;
	}
	i=0;
	while(!feof(fp)){//ttrain assigned: holder matrix, transpose matrix, and basic matrix
		if(j==0){
			Z[i][j]=1.0;
			j++;
			continue;
		}
		
		if(xc==zCols-2){
			fscanf(fp, "%lf", &value);
			Z[i][j]=value;
			xc=0;
			i++;
			j=0;
			if(i>=zRows){
				break;
			}
		}else{
			fscanf(fp, "%lf %c", &value, &hold);
			Z[i][j]=value;
			j++;
			xc++;
		}
		
	}
	i=0;
	j=0;/*
	int prows;
	int pcols;
	double **a;
	//printf("please enter number of rows.\n");
	scanf("%d\n", &prows);
	//printf("please enter number of cols.\n");
	scanf("%d\n", &pcols);
	a=(double**)malloc(prows*sizeof(double*));
	
	i=0;
	j=0;
	while(i<prows){
		a[i]=(double*)malloc(pcols*sizeof(double));
		i++;
	}
	i=0;
	j=0;
	double hi=0;
	while(i<prows){
		//printf("enter value\n: ");
		scanf("%lf", &hi);
		a[i][j]=hi;
		j++;
		if(j==pcols){
			i++;
			j=0;
		}
	}
	inverter(a, prows, pcols);*/
	//practicer(practice);
	
	/*printf("original:\n");
	progressPrint(X, R, C);
	printf("\n");*/
	
	transposer(X, R, C);
	//printf("transposed X:\n");
	//progressPrint(T, trows, tcols);
	//printf("\n");
	
	multiplier(T, trows, tcols, X, R, C);
	/*printf("transposed X * X:\n");
	progressPrint(X, crows, ccols);
	printf("\n");*/
	
	inverter(X, crows, ccols);
	/*printf("inverted (transposed X * X (In):\n");
	progressPrint(In, irows, icols);
	
	printf("\n");*/
	
	multiplier(In, irows, icols, T, trows, tcols);
	/*printf("inverted(transposed X * X) * transposed X:\n");
	progressPrint(X, crows, ccols);
	printf("\n");*/
	
	multiplier(X, crows, ccols, Y, R, 1);
	/*printf("((xt*x)^-1*xt)* Y:\n");
	progressPrint(X, crows, ccols);
	printf("\n");*/
	
	multiplier(Z, zRows, zCols, X, crows, ccols);
	/*printf("after final multiplication, test (Z) * W:\n");
	progressPrint(X, crows, ccols);
	printf("\n");*/
	
	finalPrint(X, crows, ccols);
	free(X);
	free(Y);
	free(Z);
	free(Hx);
	free(In);
	///////////
	/*
	while(!feof(fp)){
		fscanf(fp, "%lf", &value);
		test[i]=value;
		i++;
	}*/
	/*printf("the following print is the transposed matrix X^t\n");
	progressPrint(trainTranspose, trows, tcols);
	printf("all following prints are progressPrint\n");
	multiplier(trainTranspose, trows, tcols, X, xrows, xcols);
	progressPrint(X, crows, ccols);
	////////////////////
	inverter(X, crows, ccols);
	progressPrint(X, crows, ccols);
	////////////////////
	multiplier(X, crows, ccols, trainTranspose, trows, tcols);
	progressPrint(X, crows, ccols);
	///////////////////
	multiplier(X, crows, ccols, Y, xrows, 1);
	progressPrint(X, crows, ccols);
	//////////////////
	multiplier(X, crows, ccols, test, testRows, testCols);
	printer(X, crows);*/
	return 0;
}
