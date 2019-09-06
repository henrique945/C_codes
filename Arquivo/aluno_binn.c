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
int verifica();

int main(){
	char opt;
	dados *p = NULL;
	int quant,cont=0;
	
	quant = verifica();
	do{
		aloca(&p,cont+1);
		cadastro(p+cont,quant+1);
		cont++;
		quant++;
		
		printf("Deseja continuar: <S/N>\n");
		fflush(stdin);
		scanf("%c",&opt);
	}while(opt != 'N' && opt != 'n');

	
	grava(p,cont);
	p = NULL;
	aloca(&p,quant);
	leitura(p,quant);
	
	return 0;
}

void aloca(dados **p, int tam){
	if((*p=(dados*)realloc(*p,tam*sizeof(dados))) == NULL){
		printf("ERRO\n");
		exit(1);
	}
}

void cadastro(dados *p, int tam){
	
	p->reg = tam;
	printf("REGISTRO: %d\n\n",p->reg);
	printf("Digite seu nome: ");
	scanf("%s",p->nome);
	printf("Digite sua nota: ");
	scanf("%f",&(p->nota));
}

void grava(dados *p, int tam){
	FILE *fptr = NULL;
	
	fseek(fptr,0,SEEK_END);
	if((fptr = fopen("arqbinn.binn","ab")) == NULL)
		printf("Erro ao abrir o arquivo\n");
	else{
		fwrite(p,sizeof(dados),tam,fptr);
	}
	fclose(fptr);
	
}

void leitura(dados *p, int tam){
	int i;
	FILE *fptr = NULL;
	
	if((fptr = fopen("arqbinn.binn","rb")) == NULL){
		printf("Erro ao abrir o arquivo2\n");
	}
	else{
		fseek(fptr,0,SEEK_SET);
		fread(p,sizeof(dados),tam,fptr);
		for(i=0;i<tam;i++){
			printf("\nReg %d\n",((p+i)->reg));
			printf("Nome: %s\n",((p+i)->nome));
			printf("Nota: %.2f\n",((p+i)->nota));
		}
		fclose(fptr);
	}
}

int verifica(){
	int cont=0;
	FILE *fptr = NULL;
	
	if((fptr = fopen("arqbinn.binn","rb")) == NULL){
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









