#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char ** argv){
	char * input=NULL;
	if(argc<2){
		return 0;
	}
	
	
	int length=0;
	int totalLength=0;
	int a=1;
	//int totalWords=0;
	for(a=1; a!=argc;a++){
		length=strlen(argv[a]);
		totalLength=totalLength+length;
	}
	//printf("total length %d\n", totalLength);
	input=(char*) malloc((totalLength+argc)*sizeof(char));
	int i=0;
	int place=0;
	int j=1;
	//int spaces=0;
	for(;j!=argc;j++){
		//printf("loop at index %d\n", j);
		length=strlen(argv[j]);
		//printf("length of %d at index %d\n", length, j);
		for(i=0;i<length;i++){
			input[place]=argv[j][i];
			//printf("the string %s at place %d\n", input, place);
			place++;
			
		}
		input[place]=' ';
		//spaces++;
		place++;
		//i=0;
	}
	//printf("char at totalLength, %c\n", input[totalLength+argc-2]);
	input[totalLength+argc-2]='\0';
	//printf("spaces inside array: %d\n", totalLength+argc);
	//printf("index assigned delimiter: %d\n", totalLength+argc-1);
	i=0;
	/*printf("yoooooo\n");*/
	/*while(input[i]!='\0'){
		printf("%c", input[i]);
		i++;
	}*/
	//printf("\n");
	//printf("%s",input);
	//printf("\n");
	char* answer=(char*) malloc((argc-1)*sizeof(char));
	i=0;
	/*for(;i<argc-1;i++){
		answer[i]=NULL;
	}*/
	i=0;
	j=0;
	place=0;
	totalLength=strlen(input);
	
	//printf("total length: %d\n", totalLength);
	while(input[i]!='\0'){
		//printf("value of index: %d\n", i);
		
		if(input[i]==' ' && i!=0){
			answer[place]=input[i-1];
			//printf("char added: %c\n", input[i-1]);
			place++;
		}else if(input[i+1]=='\0'){
			//printf("char added!!!!!!: %c\n", input[i]);
			answer[place]=input[i];
			place++;
			break;
			
		}
		i++;
	
	}
	i=0;
	for(;i<argc-1;i++){
		printf("%c", answer[i]);
	}
	//printf("\n");
	free(answer);
	free(input);
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
