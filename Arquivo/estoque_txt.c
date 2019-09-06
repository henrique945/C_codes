//Emanuel Lourençon RA: 180281
//Henrique Rodrigues Silva RA: 190898
//Luiza Helena Camargo RA: 171162

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct estoque{
	int reg;
	char produto[30];
	int quant;
	float preco;
}estoque;

void aloca(estoque **p, int tam);
void cadastro(estoque *p);
int verifica(estoque *p);
void grava(estoque *p);
void leitura(estoque *p, int tam);
void maiuscula(char *p);
void modifica(estoque *p);

int main(){
	estoque *p = NULL;
	int quant,opt;
	
	aloca(&p, 1);
	printf("ESTOQUE\n");
	do{
		system("PAUSE");
		system("cls");
		printf("1-Cadastro\n2-Altera\n3-Mostra\n4-Sair\nInforme a opcao deseja: ");
		scanf("%d",&opt);
		
		switch(opt){
			case 1:
				cadastro(p);
				break;
			case 2:
				modifica(p);
				break;
			case 3:
				quant = verifica(p);
				leitura(p,quant);	
				break;
		}
		
	}while(opt != 4);
	
	
}

void aloca(estoque **p, int tam){
	if((*p=(estoque*)realloc(*p,tam*sizeof(estoque))) == NULL){
		printf("ERRO");
		exit(1);
	}
}

void cadastro(estoque *p){
	int cont;
	char aux[30];
	
	cont = verifica(p);
	p->reg = cont+1;
	printf("Registro %i\n",p->reg);
	printf("Digite seu nome do produto:\n");
	fflush(stdin);
	gets(p->produto);
	maiuscula(p->produto);
	printf("Digite a quantidade:\n");
	scanf("%i",&(p->quant));
	printf("Digite o preco:\n");
	scanf("%f",&(p->preco));
	
	grava(p);	
	
}

void grava(estoque *p){
	FILE *fptr = NULL;
	
	if((fptr = fopen("estoque.txt","a")) == NULL){
		printf("Erro na gravacao\n");
	}
	else{
		fprintf(fptr," %i %s %i %f",p->reg,p->produto,p->quant,p->preco);
	}
	fclose(fptr);
}

void leitura(estoque *p, int tam){
	FILE *fptr = NULL;
	int i;
	
	if((fptr = fopen("estoque.txt","r")) == NULL){
		printf("Erro na gravacao\n");
	}
	else{
		while(getc(fptr)!=EOF){
			fscanf(fptr,"%i %s %i %f",&(p->reg),p->produto,&(p->quant),&(p->preco));
			printf("Registro: %i\nProduto: %s\nQuantidade: %i\nPreco: %.2f\n\n",p->reg,p->produto,p->quant,p->preco);
		}
		fclose(fptr);
	}
}

int verifica(estoque *p){
	int cont=0;
	FILE *fptr = NULL;
	
	if((fptr = fopen("estoque.txt","r")) == NULL){
		return cont;
	}
	else{
		while(getc(fptr)!=EOF){
			fscanf(fptr,"%i %s %i %f",&(p->reg),p->produto,&(p->quant),&(p->preco));
			cont=p->reg;
		}
		fclose(fptr);
		return cont;
	}
}

void maiuscula(char *p){
	int i;
	
	for(i=0;i<strlen(p);i++){
		if( *(p+i) >= 'a' && *(p+i) <= 'z'){
			*(p+i) -= 32;
		}
	}
}

void modifica(estoque *p){
	int cont,aux,qq;
	FILE *fptr = NULL;
	
	cont = verifica(p);
	leitura(p,cont);
	printf("\n\nInforme o registro a ser alterado: ");
	scanf("%i",&aux);
	
	if((fptr = fopen("estoque.txt","r+")) == NULL){
		printf("Erro de gravacao\n");
	}
	else{
		while(getc(fptr)!=EOF){
			fscanf(fptr,"%i %s %i %f",&(p->reg),p->produto,&(p->quant),&(p->preco));
			if(p->reg == aux){
				printf("Registro: %i\n",p->reg);
				printf("Produto: %s\n",p->produto);
				printf("Quantidade: %i\n",p->quant);
				printf("Preco: %.2f\n",p->preco);
				printf("Digite a nova quantidade:\n");
				scanf("%i",&qq);
				(p->quant) = qq;
				fprintf(fptr," %i %s %i %f",p->reg,p->produto,p->quant,p->preco); //nao está atualizando
				break;
			}
		}
		fclose(fptr);
		
	}
	
}



