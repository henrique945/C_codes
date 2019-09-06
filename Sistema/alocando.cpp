#include <stdio.h>
#include <stdlib.h>

void aloca(int **p,int tam);
void registra(int **p,int tam);
void calc(int *p, int tam);
void show(int *p,int tam);

int main(){
	int *p=NULL;
	
	registra(&p,5);
	calc(p,5);
	show(p,5);	
	
	return 0;
}

void registra(int **p,int tam){
	int i;
	
	printf("Alocando...\n");
	aloca(p,tam);
	
	for(i=0;i<tam;i++){
		scanf("%d",*p+i);
	}
}

void aloca(int **p, int tam){
	if((*p=(int*)realloc(*p,tam*sizeof(int))) == NULL){
		printf("ERRO\n");
	}
}

void calc(int *p,int tam){
	int i,sum=0;
	
	for(i=0;i<tam;i++){
		sum+=*(p+i);
	}
	printf("%d\n",sum);
}

void show(int *p, int tam){
	int i;
	
	for(i=0;i<tam;i++){
		printf("%d\n",*p+i);
	}	
}
