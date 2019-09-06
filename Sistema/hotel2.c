//Henrique Rodrigues Silva - RA: 190898

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamq 5                                         //entradas possiveis no final do codigo

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
void trocar_q(hospede *hp,int tam,quarto *q, int t_quarto);
void lucro_hotel(hospede *hp,int tam, quarto *q, int t_quarto);


int main(){
	hospede *hosp=NULL;
	quarto *room=NULL;
	int opt,cont=0;
	
	aloca_room(&room,tamq); //quantidade de quartos 5 (neste caso)
	cadastro_quarto(room,tamq);

	do{
		printf("\nBEM VINDO AO HOTEL\n1-Check In\n2-Check Out\n3-Trocar Quarto\n4-Lucro Total\n5-Sair\n");
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
				
			case 3:									//funcao troca_q -> caso o usuario esteja incontente com seu quarto e quiser mudar				
				trocar_q(hosp,cont,room,tamq);   	//basta digitar o numero do quarto e seu nome para confirmar que eh seu quarto, e o quarto muda     
				break;								//O check do quarto anterior nao pode ser feito e o do novo quarto eh efetuado com sucesso
				
			case 4:
				lucro_hotel(hosp,cont,room,tamq);	//funcao para calcular o lucro dos quartos ocupados, restrito ao dono do hotel (senha: 1234)			
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
	maiuscula(aux,t_nome);
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
	int number,i,j,achou=0;
	float total;
	
	printf("\nCHECK OUT\nNumero do quarto: ");
	scanf("%d",&number);
	
	for(i=0;i<tam;i++){
		if(((hp+i)->quarto) == number){
			j = busca_quarto(q, number, t_quarto);
			if((q+j)->status == 'L'){
				printf("Quarto esta vago\n");
				achou++;
				break;
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
				
				(q+j)->status = 'L';
				printf("Check Out efetuado com sucesso!\n");
				achou++;
				break;
			}
		} 
	}
	if(achou == 0) printf("O Check Out falhou\n");
}

void trocar_q(hospede *hp,int tam,quarto *q, int t_quarto){
	int i,j,aux,achou=0,t;
	char name[30];
	
	printf("Em qual quarto esta: ");
	scanf("%d",&aux);
	
	for(i=0;i<tam;i++){
		if((hp+i)->quarto ==  aux){
			j = busca_quarto(q, aux, t_quarto);
			achou++;
			break;
		}
	}
	if(achou == 0){
		printf("Quarto inexistente\n");
		return 0;
	} 
		
	
	printf("Para meios de seguranca digite seu nome: ");
	fflush(stdin);
	gets(name);
	t=strlen(name);
	maiuscula(name,t);
	if(strcmp((hp+i)->nome,name) == 0){
		printf("Resposta correta\n");
		(q+j)->status = 'O';
		
		(hp+i)->quarto = disponivel((hp+i),(q+j),t_quarto);
		if((hp+i)->quarto == 0){
			printf("Nao ha quartos disponiveis para trocar\n");
		}
		else printf("\nNovo quarto: %d\n",(hp+i)->quarto);
	}
	else{
		printf("Desculpa, procedimento cancelado!\n");
	}
}

void lucro_hotel(hospede *hp,int tam, quarto *q, int t_quarto){  //por base todos os quartos ocupados ja possuem alguem usuario cadastrado
	int senha,i,j,aux; //a senha do dono do hotel eh 1234
	float lucro=0,total=0;
	
	printf("Acesso restrito ao dono do hotel, digite a senha:\n");
	scanf("%d",&senha);
	
	if(senha == 1234){
		for(i=0;i<t_quarto;i++){
			if((q+i)->status == 'L');
			else{			//quarto ocupada, gera dinheiro
				for(j=0;j<tam;j++){
					if(((hp+j)->quarto) == ((q+i)->num)){   //ve quem esta dentro do quarto ocupada e seus gastos
						if((hp+j)->categoria == 'S'){
							total = 85*(hp+j)->dias;
						}
						else{
							total = ((45*hp->acompanhante*(hp+j)->dias)+45);
						}
					lucro+=total;
					} //if
					
				} //segundo for
				
			} //else
			
		} //primeiro for
		printf("Lucro total: %.2f\n",lucro);
		
	}
	else{
		printf("Senha incorreta\n");
	}
		
}

/*
1
S
L
2
S 
l
3
S
L
4
F
L
5
F
L
*/


