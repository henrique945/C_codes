//Henrique Rodrigues Silva - RA: 190898
//Lucas Carvalho Rocha Fernandes - RA: 180352

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

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

void aloca(loja **p, int tam);
void cadastro(loja *p, int cont);
void maiuscula(char *p);
void grava(loja *p);
int verifica();
void mostra(loja *p, int tam);
void consulta(loja *p, int tam);

int main(){
	char opt;
	loja *p = NULL;
	int quant;
	
	aloca(&p,1);
	printf("BEM VINDO\n");

	
	do{
		system("PAUSE");
		system("cls");
		printf("1-Cadastro\n2-Mostra\n3-Consulta\n4-Sair\n");
		scanf("%d",&opt);
		quant = verifica();
		
		switch(opt){
			case 1:
				if(quant < 5){
					cadastro(p,quant);  //cadastra no arquivo direto na posicao final até no maximno 5
				}
				else{
					printf("Limite maximo de cadastros\n");
				}
				break;
			case 2:
				mostra(p,quant);  //apenas le o arquivo e mostra o que tem no arquivo
				break;
			case 3:
				consulta(p,quant); //busca o carro por meio do CNPJ
				break;
		}
		
	}while(opt != 4);
	
	
	
	return 0;
}

void aloca(loja **p, int tam){
	if((*p=(loja*)realloc(*p,tam*sizeof(loja))) == NULL){
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
	
	printf("\nDigite o endereco:\n");
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
		printf("Erro na gravacao2\n");
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
		printf("Erro ao abrir2\n");
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
		printf("Erro ao abrir\n");
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



