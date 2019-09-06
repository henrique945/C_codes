#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamq 15                                    

typedef struct composto{
	char sigla;  //O
	int num;    //num
}composto;

typedef union estado{
	char sigla;  //L
	composto campo;
}estado;

typedef struct hospede{
	int quarto;
	int reg;
	char *nome;
	int acompanhante;
	char categoria;
	int dias;
	estado tabela;
}hospede;

typedef struct quarto{
	int num;
	char categoria;
	estado status;
}quarto;

void check_in(hospede *hosp, int tam, quarto *q, int t_quarto);
void cadastro_h(hospede *hosp);
void cadastro_quarto(quarto *p, int tam);
void aloca(hospede **p, int tam);
void aloca_room(quarto **p, int tam);
void aloca_char(char **p,int tam);	
void maiuscula(char *p, int tam);
int disponivel(hospede *hosp, quarto *q, int t_quarto);
void out(hospede *hp, int tam, quarto *q, int t_quarto);
int busca_quarto(quarto* q, int num, int tam);
int busca_h(hospede *h, int tam, char *aux);
void mostra_h(hospede *h,int tam);
void mostra_q(quarto *q,int tam);

int main(){
	hospede *hosp=NULL;
	quarto *room=NULL;
	int opt,cont=0;
	
	aloca_room(&room,tamq); //quantidade de quartos 15 (neste caso)
	cadastro_quarto(room,tamq);
	mostra_q(room,tamq);
	

	do{
		system("PAUSE");
		system("cls");
		printf("\nBEM VINDO AO HOTEL\n1-Cadastro Hospede\n2-Check In\n3-Check Out\n4-Mostra Hospede\n5-Mostra Quarto\n6-Sair\n\n");
		scanf("%d",&opt);
		switch(opt){
			case 1:
				aloca(&hosp,cont+1);
				cadastro_h(hosp+cont);
				cont++;
				break;
			case 2:
				check_in(hosp,cont,room,tamq);
				break;
			case 3:
				out(hosp,cont,room,tamq);
				break;
			case 4:												
				mostra_h(hosp,cont);				
				break;
			case 5:
				mostra_q(room,tamq);
				break;
		}															
	}while(opt != 6);
	
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

void cadastro_h(hospede *hosp){
	char aux[30];
	int t_aux;
	static int num=100;
	
	fflush(stdin);
	printf("Nome: ");
	gets(aux);
	t_aux = strlen(aux);
	hosp->nome = NULL;
	aloca_char(&(hosp->nome),t_aux+1);
	maiuscula(aux,t_aux);
	strcpy(hosp->nome,aux);
	printf("Cadastrado com sucesso - %s - Numero: %d\n\n",(hosp->nome),num);
	
	hosp->reg = num;
	hosp->quarto = 0;
	num++;
	hosp->acompanhante = 0;
	hosp->dias = 0;
	hosp->categoria = '-';
	hosp->tabela.sigla = 'L';
	
}

void check_in(hospede *hosp, int tam, quarto *q, int t_quarto){
	int i,t_aux;
	char aux[30];
	
	printf("Digite o nome do hospede: ");
	fflush(stdin);
	gets(aux);
	t_aux = strlen(aux);
	maiuscula(aux,t_aux);
	
	i = busca_h(hosp,tam,aux);
	if(i == -1){
		printf("Nome invalido\n");
	}
	else{
		printf("\nQuantidade de acompanhantes: ");
		scanf("%d",&((hosp+i)->acompanhante));
		if((hosp+i)->acompanhante > 0){
			(hosp+i)->categoria='F';
		}
		else{
			(hosp+i)->categoria='S';
		}
				
		printf("\nQuantas diarias: ");
		scanf("%d",&((hosp+i)->dias));		
		
		(hosp+i)->quarto = disponivel(hosp+i, q, t_quarto);
		if((hosp+i)->quarto == 0){
			printf("Nao ha quartos disponiveis\n\n");
		}
		else printf("\nNumero do quarto: %d\n\n",(hosp+i)->quarto);
		
		(hosp+i)->tabela.sigla = 'O';
	}//busca nome
}

int busca_h(hospede *h, int tam, char *aux){
	int i;
	
	for(i=0;i<tam;i++){
		if(strcmp(aux,((h+i)->nome)) == 0){
			return i;
		}
	}
	return -1;
}

void cadastro_quarto(quarto *p, int tam){
	int i;
	
	for(i=0;i<tam;i++){
		if(i<10){
			(p+i)->num = i+1;
			(p+i)->categoria = 'S';
			(p+i)->status.sigla = 'L';
		}
		else{
			(p+i)->num = i+1;
			(p+i)->categoria = 'F';
			(p+i)->status.sigla = 'L';
		}
	}
}

int disponivel(hospede *hosp, quarto *q, int t_quarto){
	int i;
	char aux='L';
	
	for(i=0;i<t_quarto;i++){
		if((q+i)->status.sigla == aux){
			if((hosp->categoria) == ((q+i)->categoria)){
				(q+i)->status.campo.sigla = 'O';
				(q+i)->status.campo.num = (q+i)->num;
				return ((q+i)->num);	
			}
		}
	}
	return 0;
}

int busca_quarto (quarto *q, int num, int tam) {
	int i;
	
	for(i = 0; i < tam; i++) {
		if((q+i)->num == num) return i;
	}
	return -1;
}
	
void out(hospede *hp, int tam, quarto *q, int t_quarto){
	int number,i,j,achou=0;
	float total;
	
	printf("\nCHECK OUT\nNumero do quarto: ");
	scanf("%d",&number);
	
	j = busca_quarto(q,number,t_quarto);
	if(j == -1){
		printf("Quarto nao existe\n");
	}
	else if((q+j)->status.sigla == 'L'){
		printf("Quarto esta vago\n");
		
	}
	else{
		for(i=0;i<tam;i++){
			if((q+j)->status.campo.num == (hp+i)->quarto){
				achou++;	
				break;
			}
		}
	}
	//check out
	if(achou == 0){
		printf("O Check Out falhou\n");
	}
	else{
		printf("\nQUARTO: %d\n\nNome: %s\nAcompanhantes: %d - ",number,((hp+i)->nome),((hp+i)->acompanhante));
		if((hp+i)->categoria == 'S'){
			printf("Solteiro\n");
			total = 85*(hp+i)->dias;
		}
		else{
			printf("Familiar\n");
			total = (45 * ((hp+i)->acompanhante) * ((hp+i)->dias)) + 45;
		}
		printf("Diarias: %d\n\nVALOR TOTAL: %.2f\n\n",(hp+i)->dias,total);
		
		(q+j)->status.sigla = 'L';
		(hp+i)->tabela.sigla = 'L';
	}
}

void mostra_q(quarto *q,int tam){
	int i;
	
	for(i=0;i<tam;i++){
		if((q+i)->status.sigla == 'L'){
			printf("Quarto %d  Categoria %c  Status %c\n",(q+i)->num,(q+i)->categoria,(q+i)->status.sigla);
		}
		else{
			printf("Quarto %d  Categoria %c  Status %c-%d\n",(q+i)->num,(q+i)->categoria,(q+i)->status.campo.sigla,(q+i)->status.campo.num);
		}
	}
}

void mostra_h(hospede *h,int tam){
	int i;
	
	for(i=0;i<tam;i++){
		printf("Nome: %s\t\tQuarto: %d\nRegistro: %d\nAcompanhantes: %d\nCategoria: %c\nDias: %d\nStatus: %c\n\n",(h+i)->nome,(h+i)->quarto,(h+i)->reg,(h+i)->acompanhante,(h+i)->categoria,(h+i)->dias,(h+i)->tabela.sigla);
	}
}





