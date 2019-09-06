#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct aluno{
	char nome[30];
	int ra;
	int reg;
}aluno;

void aloca(aluno **p, int tam);
void cadastro(aluno *p);
int verifica();
void grava(aluno *p);
void leitura(aluno *p, int tam);
void maiuscula(char *p);
void busca(aluno *p);

int main(){
	aluno *p = NULL;
	int quant,opt;
	
	aloca(&p, 1);
	printf("BEM VINDO\n");
	do{
		system("PAUSE");
		system("cls");
		printf("1-Cadastro\n2-Busca registro\n3-Sair\n");
		scanf("%d",&opt);
		
		switch(opt){
			case 1:
				cadastro(p);
				break;
			case 2:
				busca(p);
				break;
		}
		
	}while(opt != 3);
	
	quant = verifica();
	leitura(p,quant);	
}

void aloca(aluno **p, int tam){
	if((*p=(aluno*)realloc(*p,tam*sizeof(aluno))) == NULL){
		printf("ERRO");
		exit(1);
	}
}

void cadastro(aluno *p){
	int cont;
	char aux[30];
	
	cont = verifica();
	p->reg = cont+1;
	printf("Registro %d\n",p->reg);
	printf("Digite seu nome:\n");
	fflush(stdin);
	gets(aux);
	maiuscula(aux);
	strcpy(p->nome,aux);
	printf("Digite seu RA:\n");
	scanf("%d",&(p->ra));
	
	grava(p);	
	
}

void grava(aluno *p){
	FILE *fptr = NULL;
	
	if((fptr = fopen("aluno.bin","ab")) == NULL){
		printf("Erro na gravacao\n");
	}
	else{
		fwrite(p,sizeof(aluno),1,fptr);
	}
	fclose(fptr);
}

void leitura(aluno *p, int tam){
	FILE *fptr = NULL;
	int i;
	
	if((fptr = fopen("aluno.bin","rb")) == NULL){
		printf("Erro na gravacao3\n");
	}
	else{
		fseek(fptr,0,SEEK_SET);
		for(i=0;i<tam;i++){
			fread(p,sizeof(aluno),1,fptr);
			printf("Registro %d\n",p->reg);
			printf("Nome: %s\n",p->nome);
			printf("RA: %d\n\n",p->ra);
		}
		fclose(fptr);
	}
}

int verifica(){
	int cont=0;
	FILE *fptr = NULL;
	
	if((fptr = fopen("aluno.bin","rb")) == NULL){
		printf("Erro na gravacao2\n");
	}
	else{
		fseek(fptr,0,SEEK_END);
		cont = ftell(fptr)/sizeof(aluno);
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

void busca(aluno *p){
	int cont,aux;
	FILE *fptr = NULL;
	
	cont = verifica();
	printf("O arquivo possui %d registros\nQual deseja:\n",cont);
	scanf("%d",&aux);
	
	if((fptr = fopen("aluno.bin","rb")) == NULL){
		printf("Erro de gravacao4\n");
	}
	else{
		fseek(fptr,((aux-1)*sizeof(aluno)),SEEK_SET);
		fread(p,sizeof(aluno),1,fptr);
		printf("Registro %d\n",p->reg);
		printf("Nome: %s\n",p->nome);
		printf("RA: %d\n\n",p->ra);
		fclose(fptr);
	}
	
}



