//Henrique Rodrigues Silva - RA: 190898
//Lucas Carvalho Rocha Fernandes - RA: 180352

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//loja
typedef struct endereco{
	char logradouro[80];
	char bairro[15];
	char CEP[10];
	char cidade[15];
	char estado[3];
	char fone[12];
	char email[40];
}endereco;

typedef struct infocarro{
	char sigla;
	int regcarro;
}infocarro;

typedef union dadoscarro{
	char sigla;
	infocarro reservado;	
}dadoscarro;

typedef struct loja{
	int regloja;
	char nome[30];
	char CNPJ[19];
	endereco end;
	int sold;
	int reserved;
	dadoscarro tabela[3];
}loja;

//carros
typedef struct infoloja{
	char sigla;
	char CNPJ[19];
}infoloja;

typedef union dadosloja{
	char sigla;
	infoloja reserva;
}dadosloja;

typedef struct montadora{
	int regcarro;
	char modelo[20];
	char cor[10];
	float valor;
	dadosloja status;
}montadora;

void aloca(loja **p, int tam);
void cadastro(loja *p, int cont);
void maiuscula(char *p);
void grava(loja *p);
int verifica();
void mostra(loja *p, int tam);
void consulta(loja *p, int tam);
void cadastro_car(montadora *q, int cont, loja *p, int tam);
void mostra_car(montadora *q, int tam, int op);
void grava_car(montadora *q);
void aloca_car(montadora **q, int tam);
int verifica_car();
void consulta_car(loja *p, int tam, montadora *q, int cont);
void reserva(loja *p, int tam, montadora *q, int cont);
void reserva_final(loja *p, int tam, montadora *q, int cont);

int main(){
	char opt;
	loja *p = NULL;
	montadora *q = NULL;
	int quant,qcar;
	
	aloca(&p,1);
	aloca_car(&q,1);
	printf("BEM VINDO\n");
	
	do{
		system("PAUSE");
		system("cls"); //funcao reserva final ainda nao concluida
		printf("1-Cadastra Lojas\n2-Mostra Lojas\n3-Consulta Loja\n4-Cadastra Carro\n5-Consulta Carros\n6-Consulta Carros Parcial\n7-Reservar carro\n8-Reserva final\n9-Sair\n");
		scanf("%d",&opt);
		quant = verifica();
		qcar = verifica_car();
		
		switch(opt){
			case 1:
				if(quant < 5){
					cadastro(p,quant);  //cadastra no arquivo direto na posicao final até no maximno 5
				}
				else{
					printf("Limite maximo de lojas\n");
				}
				break;
				
			case 2:
				mostra(p,quant);  //apenas le o arquivo e mostra o que tem no arquivo
				break;
				
			case 3:
				consulta(p,quant); //busca o carro por meio do CNPJ
				break;
				
			case 4:
				if(qcar < 50){
					cadastro_car(q,qcar,p,quant);
				}
				else{
					printf("Limite maximo de carros\n");
				}
				break;
				
			case 5:
				mostra_car(q,qcar,0);
				break;
				
			case 6:
				consulta_car(p,quant,q,qcar);
				break;
				
			case 7:
				reserva(p,quant,q,qcar);
				break;
				
			case 8:
				reserva_final(p,quant,q,qcar);
				break;
				
			case 9:
				break;

			default:
				printf("Digite uma opcao valida\n");
				break;
		}
		
	}while(opt != 9);
	
	
	
	return 0;
}

void aloca(loja **p, int tam){
	if((*p=(loja*)realloc(*p,tam*sizeof(loja))) == NULL){
		printf("Erro de alocacao\n");
		exit(1);
	}
}

void aloca_car(montadora **q, int tam){
	if((*q=(montadora*)realloc(*q,tam*sizeof(montadora))) == NULL){
		printf("Erro de alocacao\n");
		exit(1);
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

void cadastro(loja *p, int cont){
	char aux[30];
	
	p->regloja = cont+1;
	printf("Registro %d\n",p->regloja);
	printf("Digite o nome da loja:\n");
	fflush(stdin);
	gets(aux);
	maiuscula(aux);
	strcpy(p->nome,aux);
	
	printf("Digite seu CNPJ:\n");
	fflush(stdin);
	gets(aux);
	strcpy(p->CNPJ,aux);
	
	printf("\nDigite o endereco\n");
	printf("Logradouro:\n");
	fflush(stdin);
	gets(aux);
	maiuscula(aux);
	strcpy(p->end.logradouro,aux);
	printf("Bairro:\n");
	fflush(stdin);
	gets(aux);
	maiuscula(aux);
	strcpy(p->end.bairro,aux);
	printf("CEP:\n");
	fflush(stdin);
	gets(aux);
	strcpy(p->end.CEP,aux);
	printf("Cidade:\n");
	fflush(stdin);
	gets(aux);
	maiuscula(aux);
	strcpy(p->end.cidade,aux);
	printf("Estado:\n");
	fflush(stdin);
	gets(aux);
	maiuscula(aux);
	strcpy(p->end.estado,aux);
	printf("Telefone:\n");
	fflush(stdin);
	gets(aux);
	strcpy(p->end.fone,aux);
	printf("Email:\n");
	fflush(stdin);
	gets(aux);
	strcpy(p->end.email,aux);
	
	p->sold = 0;
	p->reserved = 0;
	
	(p->tabela[0]).sigla = 'L';
	(p->tabela[1]).sigla = 'L';
	(p->tabela[2]).sigla = 'L';
	
	grava(p);	
	
}

void grava(loja *p){
	FILE *fptr = NULL;
	
	if((fptr = fopen("concessionaria.bin","ab")) == NULL){
		printf("Erro na gravacao\n");
	}
	else{
		fwrite(p,sizeof(loja),1,fptr);
	}
	fclose(fptr);
}

int verifica(){
	int cont=0;
	FILE *fptr = NULL;
	
	if((fptr = fopen("concessionaria.bin","rb")) == NULL){
		//printf("Erro na gravacao2\n");
	}
	else{
		fseek(fptr,0,SEEK_END);
		cont = ftell(fptr)/sizeof(loja);
		fclose(fptr);
	}
	
	return cont;
}

void mostra(loja *p, int tam){
	FILE *fptr = NULL;
	int i;
	
	if((fptr = fopen("concessionaria.bin","rb")) == NULL){
		printf("Nao ha lojas cadastradas\n");
	}
	else{
		fseek(fptr,0,SEEK_SET);
		for(i=0;i<tam;i++){
			fread(p,sizeof(loja),1,fptr);
			printf("Registro %d\n",p->regloja);
			printf("Nome: %s\n",p->nome);
			printf("CNPJ: %s\n",p->CNPJ);
			
			printf("\nEndereco:\n");
			printf("Logradouro: %s\n",p->end.logradouro);
			printf("Bairro: %s\n",p->end.bairro);
			printf("CEP: %s\n",p->end.CEP);
			printf("Cidade: %s\n",p->end.cidade);
			printf("Estado: %s\n",p->end.estado);
			printf("Telefone: %s\n",p->end.fone);
			printf("Email: %s\n",p->end.email);
			
			printf("\nVendidos: %d  Reservados: %d\n",p->sold,p->reserved);
			printf("Tabela 0: %c\n",(p->tabela[0]).sigla);
			printf("Tabela 1: %c\n",(p->tabela[1]).sigla);
			printf("Tabela 2: %c\n\n\n",(p->tabela[2]).sigla);
			
		}
		fclose(fptr);
	}
}

void consulta(loja *p, int tam){
	char aux[20];
	FILE *fptr = NULL;
	int i,vdd = 0;
	
	printf("Digite o CNPJ desejado:\n");
	fflush(stdin);
	gets(aux);
	
	if((fptr = fopen("concessionaria.bin","rb")) == NULL){
		printf("Nao ha lojas cadastradas\n");
	}
	else{
		fseek(fptr,0,SEEK_SET);
		for(i=0;i<tam;i++){
			if(strcmp(aux,p->CNPJ) == 0){
				vdd++;
				printf("Nome: %s\n",(p+i)->nome);
				printf("\nVendidos: %d  Reservados: %d\n",(p+i)->sold,(p+i)->reserved);
				if((p+i)->reserved == 1){
					printf("\nTabela 0: %c - %i", ((p+i)->tabela[0]).reservado.sigla, ((p+i)->tabela[0]).reservado.regcarro);
				}
				else if((p+i)->reserved == 2){
					printf("\nTabela 1: %c - %i", ((p+i)->tabela[1]).reservado.sigla, ((p+i)->tabela[1]).reservado.regcarro);
				}
				else if((p+i)->reserved == 3){
					printf("\nTabela 2: %c - %i", ((p+i)->tabela[2]).reservado.sigla, ((p+i)->tabela[2]).reservado.regcarro);
				}
				
				break;
			}
			
		}
		
		if(vdd == 0){
			printf("CNPJ nao encontrado\n");
		}
		fclose(fptr);
	}
	
}


void cadastro_car(montadora *q, int cont, loja *p, int tam){ //a funcao verifica antes ja retorna a posicao correta da estrutura
	char aux[30], opt, opt2;
	int achou = 0, i;
	FILE *fptr = NULL;
	
	q->regcarro = cont+101;
	printf("Registro %d\n",q->regcarro);
	printf("Digite o modelo do carro:\n");
	fflush(stdin);
	gets(aux);
	maiuscula(aux);
	strcpy(q->modelo,aux);
	
	printf("Digite a cor do carro:\n");
	fflush(stdin);
	gets(aux);
	maiuscula(aux);
	strcpy(q->cor,aux);
	
	printf("Digite o preco do carro:\n");
	scanf("%f",&(q->valor));
	
	printf("O carro possui loja <S/N> ?\n");
	fflush(stdin);
	scanf("%c",&opt);
	if(opt == 'N' || opt == 'n'){
		q->status.sigla = 'L';
	}
	else{
		do{
			printf("Digite o CNPJ da loja: \n");
			fflush(stdin);
			gets(aux);
			
			if((fptr = fopen("concessionaria.bin","rb")) == NULL){
				printf("nao ha lojas cadastradas\n");
			}
			else{
				fseek(fptr,0,SEEK_SET);
				for(i=0;i<tam;i++){
					fread(p,sizeof(loja),1,fptr);
					if(strcmp(aux,p->CNPJ) == 0){
						strcpy(q->status.reserva.CNPJ,aux);
						q->status.reserva.sigla = 'R';
						achou = 1;
					}
				}
				fclose(fptr);
			}
			
			if(achou == 0){
				printf("CNPJ nao existe\n");
				printf("Continuar como carro livre <s/n> ?\n");
				fflush(stdin);
				scanf("%c",&opt2);
				if(opt2 == 's' || opt2 == 's'){
					achou = 1;
					q->status.sigla = 'L';
				}
			}
		}while(achou == 0);
	}
	
	grava_car(q);	
}

void grava_car(montadora *q){
	FILE *fptr = NULL;
	
	if((fptr = fopen("carro.bin","ab")) == NULL){
		printf("Erro na gravacao\n");
	}
	else{
		fwrite(q,sizeof(montadora),1,fptr);
	}
	fclose(fptr);
}

void mostra_car(montadora *q, int tam, int op){
	int i;
	FILE *fptr = NULL;
	
	if((fptr = fopen("carro.bin","rb")) == NULL){
		printf("Erro ao abrir o arquivo\n");
	}
	else{
		fseek(fptr,0,SEEK_SET);
		for(i=0;i<tam;i++){
			fread(q,sizeof(montadora),1,fptr);
			if(q->status.reserva.sigla != 'R' || op == 0){
				printf("\nRegistro %d\n",q->regcarro);
				printf("Mdodelo do carro: %s\n",q->modelo);
				printf("Cor do carro: %s\n",q->cor);
				printf("Preco do carro: %.2f\n",q->valor);
				if(q->status.sigla == 'L'){
					printf("Status: %c\n",q->status.sigla);			
				}
				else{
					printf("Status: %c - %s\n",q->status.reserva.sigla,q->status.reserva.CNPJ);
				}
			}
		}
		fclose(fptr);
	}
}

int verifica_car(){
	int cont = 0;
	FILE *fptr = NULL;
	
	if((fptr = fopen("carro.bin","rb")) == NULL){
		//printf("erro ao abrir o arquivo2\n");
	}
	else{
		fseek(fptr,0,SEEK_END);
		cont = ftell(fptr)/sizeof(montadora);
		fclose(fptr);
	}	
	return cont;	
}

void consulta_car(loja *p, int tam, montadora *q, int cont){
	char opt,aux[30];
	int i,achou = 0, achou2 = 0;
	FILE *fptr = NULL;
	
	printf("Carros Livres ou Registrados <L/R> ?\n");
	fflush(stdin);
	scanf("%c",&opt);
	
	if((fptr = fopen("carro.bin","rb")) == NULL){
		printf("erro\n");
	}
	else{
		if(opt == 'L' || opt == 'l'){
			for(i=0;i<cont;i++){
				fread(q,sizeof(montadora),1,fptr);
				if(q->status.sigla == 'L'){
					printf("\nRegistro %d\n",q->regcarro);
					printf("Mdodelo do carro: %s\n",q->modelo);
					printf("Cor do carro: %s\n",q->cor);
					printf("Preco do carro: %.2f\n",q->valor);
					printf("Status: L\n");
					achou = 1;
				}
			}
			printf("\nModelo:\n");
			fflush(stdin);
			gets(aux);
			maiuscula(aux);
			system("cls");
			
			fseek(fptr,0,SEEK_SET);
			for(i=0;i<cont;i++){
				fread(q,sizeof(montadora),1,fptr);
				if((strcmp(aux,q->modelo) == 0) && (q->status.sigla == 'L')){
					printf("\nRegistro %d\n",q->regcarro);
					printf("Mdodelo do carro: %s\n",q->modelo);
					printf("Cor do carro: %s\n",q->cor);
					printf("Preco do carro: %.2f\n",q->valor);
					printf("Status: L\n");
					achou2 = 1;
				}
			}
			if(achou2 == 0){
				printf("nao achou modelo\n");
			}		
		}
		else if(opt == 'R' || opt == 'r'){
			for(i=0;i<cont;i++){
				fread(q,sizeof(montadora),1,fptr);
				if(q->status.reserva.sigla == 'R'){
					printf("\nRegistro %d\n",q->regcarro);
					printf("Mdodelo do carro: %s\n",q->modelo);
					printf("Cor do carro: %s\n",q->cor);
					printf("Preco do carro: %.2f\n",q->valor);
					printf("Status: R - %s\n",q->status.reserva.CNPJ);
					achou = 1;
				}		
			}
			printf("\nModelo:\n");
			fflush(stdin);
			gets(aux);
			maiuscula(aux);
			system("cls");
			
			fseek(fptr,0,SEEK_SET);
			for(i=0;i<cont;i++){
				fread(q,sizeof(montadora),1,fptr);
				if((strcmp(aux,q->modelo) == 0) && (q->status.reserva.sigla == 'R')){
					printf("\nRegistro %d\n",q->regcarro);
					printf("Mdodelo do carro: %s\n",q->modelo);
					printf("Cor do carro: %s\n",q->cor);
					printf("Preco do carro: %.2f\n",q->valor);
					printf("Status: R - %s\n",q->status.reserva.CNPJ);
					achou2 = 1;
				}
			}
			if(achou2 == 0){
				printf("nao achou modelo\n");
			}
		}
		
		if(achou == 0){
			printf("carro nao encontrado\n");
		}
		fclose(fptr);
	}
	
}

void reserva(loja *p, int tam, montadora *q, int cont){
	int i,achou = 0,num;
	char aux[19],opt;
	FILE *fptr = NULL;
	
	printf("Digite o CNPJ da loja:\n");
	fflush(stdin);
	gets(aux);
	
	if((fptr = fopen("concessionaria.bin","rb+")) == NULL){
				printf("cnpj nao encontrado\n");
	}
	else{
		for(i=0;i<tam;i++){
			fseek(fptr,i*sizeof(loja),SEEK_SET);
			fread(p,sizeof(loja),1,fptr);
			if(strcmp(aux,p->CNPJ) == 0){
				if(p->reserved < 3){
					p->reserved += 1;
					fseek(fptr,i*sizeof(loja),SEEK_SET);
					fwrite(p,sizeof(loja),1,fptr);
					achou = 1;
				}
				break;				
			}
		}
	fclose(fptr);
	}
	
	if(achou == 0){
		printf("cnpj invalido ou limite maximo atingido\n");
	}
	else{
		printf("Deseja consultar os carros disponiveis? <S/N>\n");
		scanf("%c",&opt);
		if(opt == 'S' || opt == 's'){
			mostra_car(q,cont,1);		
		}
		
		printf("\nDigite o registro do carro:\n");
		scanf("%d",&num);
		achou = 0;
		
		if((fptr = fopen("carro.bin","rb+")) == NULL){
				printf("Carro nao encontrado\n");
		}
		else{
			for(i=0;i<cont;i++){
				fseek(fptr,i*sizeof(montadora),SEEK_SET);
				fread(q,sizeof(montadora),1,fptr);
				if(q->regcarro == num){
					if(q->status.reserva.sigla != 'R'){
						q->status.reserva.sigla = 'R';
						strcpy(q->status.reserva.CNPJ,p->CNPJ);
						fseek(fptr,i*sizeof(montadora),SEEK_SET);
						fwrite(q,sizeof(montadora),1,fptr);
						achou = 1;
					}
				}
					
			}
		}
		fclose(fptr);
		
		if(achou == 0){
			printf("Carro indisponivel\n");
		}
		else{
			printf("Reserva realizada com sucesso\n");
		}
	}
	
}
	
void reserva_final(loja *p, int tam, montadora *q, int cont){
	FILE *fptr = NULL;
	int numReg, achou = 0, compra = 0, i;
	char opt;
	
	printf("Digite o registro do carro:\n");
	scanf("%d", &numReg);
	
	if((fptr = fopen("carro.bin","rb+")) == NULL){
		printf("Carro nao encontrado\n");
	}
	else{
		for(i=0;i<cont;i++){
			fseek(fptr,i*sizeof(montadora),SEEK_SET);
			fread(q,sizeof(montadora),1,fptr);
			if(q->regcarro == numReg){
				achou = 1;
				printf("Mdodelo do carro: %s\n",q->modelo);
				printf("Cor do carro: %s\n",q->cor);
				printf("Preco do carro: %.2f\n",q->valor);
				
				if(q->status.sigla == 'L'){
					printf("Status: %c\n",q->status.sigla);			
				}
				else{
					printf("Status: %c - %s\n",q->status.reserva.sigla,q->status.reserva.CNPJ);
				}
				
				if(q->status.reserva.sigla == 'R'){
					printf("Deseja comprar? <S/N>\n");
					fflush(stdin);
					scanf("%c",&opt);
					
					if(opt == 'S' || opt == 's'){ //comprando o carro
						compra = 1;
					}
					else{ //liberando o carro
						q->status.sigla = 'L';
						fseek(fptr,i*sizeof(montadora),SEEK_SET);
						fwrite(q,sizeof(montadora),1,fptr);	
					}
				}
				else{
					printf("Carro está livre\n");
				}
				break;
			}
				
		}
	}
	fclose(fptr);
	
	if(compra == 1){
		if((fptr = fopen("concessionaria.bin","rb+")) == NULL){
			printf("carro nao encontrado\n");
		}
		else{
			for(i=0;i<tam;i++){
				fseek(fptr,i*sizeof(loja),SEEK_SET);
				fread(p,sizeof(loja),1,fptr);
				if(strcmp(q->status.reserva.CNPJ,p->CNPJ) == 0){
					p->reserved -= 1;
					p->sold += 1;
					fseek(fptr,i*sizeof(loja),SEEK_SET);
					fwrite(q,sizeof(loja),1,fptr);	
					
					break;				
				}
			}
		fclose(fptr);
		}
	}
	
	if(achou == 0){
		printf("Carro nao encontrado\n");
	}
	else{
		printf("Realizada com sucesso\n");
	}
	
}


