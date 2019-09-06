#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamq 5

typedef struct hospede{
	int quarto;
	char *nome;
	int acompanhante;
	char categoria;
	int dias;
}hospede;

typedef struct quarto{
	int num;
	char categoria;
	char status;
}quarto;

void cadastro(hospede *hosp, quarto *q, int t_quarto);
void cadastro_quarto(quarto *p, int tam);
void aloca(hospede **p, int tam);
void aloca_room(quarto **p, int tam);
void aloca_char(char **p,int tam);	
void maiuscula(char *p, int tam);
int disponivel(hospede *hosp, quarto *q, int t_quarto);
void out(hospede *hp, int tam, quarto *q, int t_quarto);
int busca_quarto (quarto* q, int num, int tam);


int main(){
	hospede *hosp=NULL;
	quarto *room=NULL;
	int opt,cont=0;
	
	aloca_room(&room,tamq); //quantidade de quartos 5
	cadastro_quarto(room,tamq);

	do{
		printf("\nBEM VINDO AO HOTEL\n1-Check In\n2-Check Out\n5-Sair\n");
		scanf("%d",&opt);
		switch(opt){
			case 1:
				aloca(&hosp,cont+1);
				cadastro(hosp+cont,room,tamq);
				cont++;
				break;
			case 2:
				out(hosp,cont,room,tamq);
				break;
				
		}
		
	}while(opt != 5);
	
	
}

void aloca(hospede **p, int tam){
	if((*p=(hospede*)realloc(*p,tam*sizeof(hospede))) == NULL){
		printf("ERRO\n");
	}
}

void aloca_room(quarto **p, int tam){
	if((*p=(quarto*)realloc(*p,tam*sizeof(quarto))) == NULL){
		printf("ERRO\n");
	}
}

void aloca_char(char **p, int tam){
	if((*p=(char*)realloc(*p,tam*sizeof(char))) == NULL){
		printf("ERRO\n");
	}
}


void maiuscula(char *p, int tam){
	int i;
	
	for(i=0;i<tam;i++){
		if(*(p+i) >= 'a' && *(p+i) <= 'z'){
			*(p+i) -= 32;
		}
	}
}

void cadastro(hospede *hosp, quarto *q, int t_quarto){
	char aux[80];
	int t_nome,a;
	
	fflush(stdin);
	printf("\nNome: ");
	gets(aux);
	t_nome=strlen(aux);
	hosp->nome=NULL;
	aloca_char(&(hosp->nome),t_nome+1);
	strcpy(hosp->nome,aux);
	
	printf("\nQuantidade de acompanhantes: ");
	scanf("%d",&hosp->acompanhante);
	
	if(hosp->acompanhante > 0){
		hosp->categoria='F';
	}
	else{
		hosp->categoria='S';
	}
		
	printf("\nQuantas diarias: ");
	scanf("%d",&hosp->dias);
	
	hosp->quarto = disponivel(hosp, q, t_quarto);
	if(hosp->quarto == 0){
		printf("Nao ha quartos disponiveis\n");
	}
	else printf("\nNumero do quarto: %d\n",hosp->quarto);
}

void cadastro_quarto(quarto *p, int tam){
	int i;
	
	for(i=0;i<tam;i++){
		printf("\nNumero do quarto: ");
		scanf("%d",&((p+i)->num));
		
		fflush(stdin);
		printf("\nCategoria [S]olteiro / [F]amiliar: ");
		scanf("%c",&((p+i)->categoria));
		maiuscula(&((p+i)->categoria),1);
		
		fflush(stdin);
		printf("\nStatus [L]ivre / [O]cupado: ");
		scanf("%c",&((p+i)->status));
		maiuscula(&((p+i)->status),1);
	}

}

int disponivel(hospede *hosp, quarto *q, int t_quarto){
	int i;
	char aux='L';
	
	for(i=0;i<t_quarto;i++){
		if((q+i)->status == aux){
			if((hosp->categoria) == ((q+i)->categoria)){
				(q+i)->status = 'O';
				return ((q+i)->num);	
			}
		}
	}
	return 0;
}

int busca_quarto (quarto* q, int num, int tam) {
	int i;
	for(i = 0; i < tam; i++) {
		if((q+i)->num == num) return i;
	}
	return -1;
}
	
void out(hospede *hp, int tam, quarto *q, int t_quarto){
	int number,i,achou=0;
	float total;
	
	printf("\nCHECK OUT\nNumero do quarto: ");
	scanf("%d",&number);
	
	for(i=0;i<tam;i++){
		if((hp+i)->quarto == number){
			int j = busca_quarto(q, number, t_quarto);
			if((q+j)->status == 'L'){
				printf("Quarto esta vago\n");
				achou++;
				break;
			}
			else{
				printf("\nQUARTO: %d\n\nNome: %s\nAcompanhantes: %d - ",number,(hp+i)->nome,(hp+i)->acompanhante);
				if((hp+i)->categoria == 'S'){
				printf("Solteiro\n");
				total = 85*(hp+i)->dias;
				}
				else{
				printf("Familiar\n");
				total = 45*hp->acompanhante*(hp+i)->dias;
				}
				
				printf("Diarias: %d\n\nVALOR TOTAL: %.2f\n\n",(hp+i)->dias,total);
				
				(q+j)->status = 'L';
				printf("Check Out efetuado com sucesso!\n");
				achou++;
				break;
			}
		} 
	}
	if(achou == 0) printf("O Check Out falhou\n");
}








