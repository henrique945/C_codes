#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct treino{
	int ex;
	char nome_ex[30];
}treino;


void aloca(treino **p, int tam);
void cadastra(treino *p, int tam);
int verifica();
void grava(treino *p);
void mostra(treino *p, int tam);
//int busca();
//void remove();


int main(){
	int opt, quant;
	treino *p = NULL;
	
	
	aloca(&p,1);
	printf("BEM VINDO\n");
	do{
		system("PAUSE");
		system("cls");
		printf("1-Cadastra\n2-Remove\n3-Mostra\n4-Sair\n");
		scanf("%d", &opt);
		
		quant = verifica();
		
		switch(opt){
			case 1:
				cadastra(p,quant);				
				break;
			
			case 2:
				
				break;
			
			case 3:
				mostra(p, quant);
				break;
				
			case 4:
				break;
		}
		
	}while(opt != 4);


}

void aloca(treino **p, int tam){
	if((*p=(treino*)realloc(*p,tam*sizeof(treino))) == NULL){
		printf("erro\n");
		exit(1);
	}
}

int verifica(){
	int cont = 0;
	FILE *fptr = NULL;
	
	if((fptr = fopen("treino.bin","rb")) == NULL){
		printf("erroo!\n");
	}
	else{
		fseek(fptr,0,SEEK_END);
		cont = ftell(fptr)/sizeof(treino);
		fclose(fptr);
	}
	
	return cont;
}

void maiuscula(char *p){
	int i;
	
	for(i=0;i<strlen(p);i++){
		if( *(p+i) >= 'a' && *(p+i) <= 'z'){
			*(p+i) -= 32;	
		}
	}	
	
}

void cadastra(treino *p, int tam){
	char aux[30];
	
	p->ex = tam+1;
	
	printf("nome do exercicio %d:\n",p->ex);
	fflush(stdin);
	gets(aux);
	maiuscula(aux);
	strcpy(p->nome_ex,aux);
	
	grava(p);
	
}

void grava(treino *p){
	FILE *fptr = NULL;
	
	if((fptr = fopen("treino.bin","ab")) == NULL){
		printf("erro ao gravar\n");
	}
	else{
		fwrite(p,sizeof(treino),1,fptr);
	}
	fclose(fptr);
	
	
}

void mostra(treino *p, int tam){
	int i;
	FILE *fptr = NULL;
	
	if((fptr = fopen("treino.bin","rb")) == NULL){
		printf("erro ao mostrar\n");
	}
	else{
		fseek(fptr,0,SEEK_SET);
		for(i=0;i<tam;i++){
			fread(p, sizeof(treino),1,fptr);
			printf("Exercicio %d : %s\n",p->ex,p->nome_ex);
		}
		fclose(fptr);
	}
	
	
	
}
