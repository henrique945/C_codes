#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dados{
	int reg;
	char nome[80];
	float nota;
}dados;

void cadastro(dados *p, int tam);
void aloca(dados **p, int tam);
void grava(dados *p, int tam);
void leitura(dados *p, int tam);

int main(){
	char opt,cont=0;
	dados *p = NULL;
	
	do{
		aloca(&p,cont+1);
		cadastro(p,cont);
		cont++;		
		
		
		printf("Deseja continuar: <S/N>\n");
		fflush(stdin);
		scanf("%c",&opt);
	}while(opt != 'N' && opt != 'n');
	leitura(p,cont);
	
	return 0;
}

void aloca(dados **p, int tam){
	if((*p=(dados*)realloc(*p,tam*sizeof(dados))) == NULL){
		printf("ERRO\n");
		exit(1);
	}
}

void cadastro(dados *p, int tam){
	int static reg = 100;
	
	printf("Digite seu nome: ");
	scanf("%s",(p+tam)->nome);
	printf("Digite sua nota: ");
	scanf("%f",&((p+tam)->nota));
	
	(p+tam)->reg = reg;
	grava(p,tam);
	reg++;
}

void grava(dados *p,int tam){
	FILE *fptr = NULL;
	
	if((fptr = fopen("arqbin.bin","wb")) == NULL)
		printf("Erro ao abrir o arquivo\n");
	else{
		fwrite(p,sizeof(dados),tam,fptr);
	}
	fclose(fptr);
}

void leitura(dados *p, int tam){
	int i;
	FILE *fptr = NULL;
	
	if((fptr = fopen("arqbin.bin","rb")) == NULL){
		printf("Erro ao abrir o arquivo2\n");
	}
	else{
		fread(p,sizeof(dados),tam+1,fptr);
		fclose(fptr);
	}
	
	for(i=0;i<tam;i++){
		printf("\nReg %d\n",((p+i)->reg));
		printf("Nome: %s\n",((p+i)->nome));
		printf("Nota: %.2f\n",((p+i)->nota));
	}
	
}











