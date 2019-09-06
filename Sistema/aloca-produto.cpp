#include <stdio.h>
#include <stdlib.h>

typedef struct peca{
    int  num;
    char nome[10];
    }peca;
        
void aloca(peca **p,int tam);
void leitura(peca *p);
void imprime(peca *p,int tam);

int main(){
	peca *p_peca=NULL;
	char op;
	int cont=0;
	
	do{
		aloca(&p_peca,cont+1);
		leitura(p_peca+cont);
		cont++;
		printf("\nDeseja continuar <S/N>: ");
		scanf("%c",&op);
		fflush(stdin);
	}while(op!='n'&& op!='N');
		
		imprime(p_peca,cont);
		system("pause");
	}//main
  
void aloca(peca **p,int tam){
	if((*p=(peca*)realloc(*p,tam*sizeof(peca)))==NULL)
	exit(1);
}//aloca

void leitura(peca *p){
	static int n=1;
	p->num=n;
	n++;
	printf("\nDigite o produto:");
	gets(p->nome);
	fflush(stdin);
}//leitura

void imprime(peca *p,int tam){
	int i;
	
	for(i=0;i<tam;i++)
		printf("\nNumero: %i \nProduto: %s\n",(p+i)->num,(p+i)->nome);	
}//imprime
  
  
  
  






