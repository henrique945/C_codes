#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dados{
	int reg;
	char nome[80];
	float nota;
}dados;

void cadastro(dados *p);
void aloca(dados **p, int tam);
void grava(dados *p);
void leitura(dados *p, int tam);
int verifica(dados *p);

int main(){
	char opt;
	dados *p = NULL;
	int quant;
	
	aloca(&p,1);
	do{
		cadastro(p);
		
		printf("Deseja continuar: <S/N>\n");
		fflush(stdin);
		scanf("%c",&opt);
	}while(opt != 'N' && opt != 'n');
	
	quant = verifica(p);
	leitura(p,quant);
	
	return 0;
}

void aloca(dados **p, int tam){
	if((*p=(dados*)realloc(*p,tam*sizeof(dados))) == NULL){
		printf("ERRO\n");
		exit(1);
	}
}

void cadastro(dados *p){
	int quant;
	
	quant = verifica(p);
	p->reg = quant+1;
	printf("REGISTRO: %d\n\n",p->reg);
	printf("Digite seu nome: ");
	scanf("%s",p->nome);
	printf("Digite sua nota: ");
	scanf("%f",&(p->nota));
	grava(p);
}

void grava(dados *p){
	FILE *fptr = NULL;
	
	fseek(fptr,0,SEEK_END);
	if((fptr = fopen("arqbin.bin","ab")) == NULL)
		printf("Erro ao abrir o arquivo\n");
	else{
		fwrite(p,sizeof(dados),1,fptr);
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
		fseek(fptr,0,SEEK_SET);
		for(i=0;i<tam;i++){
			fread(p,sizeof(dados),1,fptr);
			printf("\nReg %d\n",(p->reg));
			printf("Nome: %s\n",(p->nome));
			printf("Nota: %.2f\n",(p->nota));
		}
		fclose(fptr);
	}
}

int verifica(dados *p){
	int cont=0;
	FILE *fptr = NULL;
	
	if((fptr = fopen("arqbin.bin","rb")) == NULL){
		printf("Erro ao abrir o arquivo3\n");
	}
	else{
		fseek(fptr,0,SEEK_END);
		cont = ftell(fptr);
		cont = cont/sizeof(dados);
		fclose(fptr);
	}
	
	return cont;
}









