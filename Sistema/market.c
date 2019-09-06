#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct prod{
	char *nome;
	float valor;
}produto;

void aloca(produto **p,int tam);
void aloca_char(char **pc, int tam);
void pagamento(produto *p, int tam);
void cadastra_prod(produto *p, int tam);
void show_prod(produto *p, int tam);
int maiuscula(char *opt,int tam);

int main(){
	produto *p=NULL;
	int opt=1,cont=0;
	
	while(opt != 0){
		scanf("%d",&opt);
		switch(opt){
			case 1: aloca(&p,cont+1);
					cadastra_prod(p,cont);
					cont++;
					break;
					
			case 2: pagamento(p,cont);  //total a pagar
					break;
					
			case 0: break;
			default: printf("Numero invalido\n");		
		}
	}
	show_prod(p,cont);	
}

void aloca(produto **p,int tam){
	if((*p=(produto*)realloc(*p,tam*sizeof(produto))) == NULL){
		printf("Erro\n");
		exit(1);
	}
}

void aloca_char(char **pc, int tam){
	if((*pc=(char*)realloc(*pc,tam*sizeof(char))) == NULL){
		printf("Erro\n");
		exit(1);
	}
}

void cadastra_prod(produto *p, int tam){
	char aux[30];
	int t_aux;
	
	printf("Digite o nome do produto:\n");
	fflush(stdin);
	gets(aux);
	t_aux=strlen(aux);
	(p+tam)->nome = NULL;
	aloca_char(&((p+tam)->nome),t_aux+1);
	strcpy(((p+tam)->nome),aux);
	
	printf("Digite o valor do produto:\n");
	scanf("%f",&((p+tam)->valor));
}

void pagamento(produto *p, int tam){
	int i, quant=0;
	float total;
	char opt='s', aux[30];
	
	
	while(opt != 'N'){
		printf("Nome do produto: ");
		fflush(stdin);
		gets(aux);
		
		for(i=0;i<tam;i++){
			if(strcmp(((p+i)->nome),aux) == 0){
				printf("Quantidade: ");
				scanf("%d",&quant);
				total+= quant * (p+i)->valor;
				break;
			}
		}
		printf("Cadastra produto <S/N>\n");
		fflush(stdin);
		scanf("%c",&opt);
		opt=maiuscula(&opt,tam);
	}
	printf("Valor total: %.2f\n",total);
}

void show_prod(produto *p, int tam){
	int i;
	
	for(i=0;i<tam;i++){
		printf("Produto: %s - Preco: %.2f\n",((p+i)->nome),((p+i)->valor));
	}
}

int maiuscula(char *opt, int tam){
	int i;
	
	for(i=0;i<tam;i++){
		if(*opt >= 'a' && *opt <= 'z'){
			return *opt-=32;	
		}
	}
}






