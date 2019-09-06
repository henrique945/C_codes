#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data{
	int dia;
	int mes;
	int ano;
}data;

typedef struct aluno{
	char *nome;
	char *RA;
	float *nota;
	float media;
	data niver;
}aluno;

void aloca(aluno **p,int tam){
	if((*p=(aluno*)realloc(*p,tam*sizeof(aluno)))==NULL) printf("ERRO");	
}

void aloca_char(aluno **p, int tam){
	if((*p=(char*)realloc(*p,tam*sizeof(char)))==NULL) printf("ERRO");
}

void aloca_float(aluno **p, int tam){
	if((*p=(float*)realloc(*p,tam*sizeof(float)))==NULL) printf("ERRO");
}

void cadastro(aluno *p){
	char aux[80];
	static int RA = 1000;
	int tam,j=0;
	
	//itoa ( int value, char * str, int base )
	
	printf("Digite o nome do aluno:\n");
	fflush(stdin);
	gets(aux);
	fflush(stdin);
	tam=strlen(aux);
	p->nome=NULL;
	aloca_char(&(p->nome),tam+1);
	strcpy(p->nome,aux);
	
	itoa(RA, aux, 10);
	tam=strlen(aux);
	p->RA=NULL;
	aloca_char(&(p->RA),tam+1);
	strcpy(p->RA,aux);
	printf("RA: %s\n", p->RA);
	RA++;
	p->nota=NULL;
	aloca_float(&(p->nota),3);
	
	printf("Data de nascimento: DD MM AAAA\n");
	scanf(" %d %d %d",&(p->niver.dia),&(p->niver.mes),&(p->niver.ano));
	for(j=0;j<2;j++){
		*(p->nota+j) = 0;
	}
	p->media = 0;
}

void controle(aluno *p, int tam){
	char aux[80];
	int i,j,achou=0;
	
	printf("Digite o RA do aluno:\n");
	fflush(stdin);
	gets(aux);
	
	for(i=0;i<tam;i++){
		if(strcmp((p+i)->RA,aux) == 0){
			printf("RA -> %s \n", (p+i)->nome);
			printf("Digite a primeira nota:\n");
			scanf(" %f", (p+i)->nota+j);
			(p+i)->media += *((p+i)->nota+j);
			j++;
			printf("Digite a segunda nota:\n");
			scanf(" %f", (p+i)->nota+j);
			(p+i)->media += *((p+i)->nota+j);
			(p+i)->media = ((p+i)->media)/2;
			printf("Media: %.2f\n", (p+i)->media);
			achou++;
		}			
	}
	if(achou == 0) printf("RA nao encontrado\n");
}

void mostra(aluno *p,int tam){
	int i;
	
	for(i=0;i<tam;i++){
		printf("Nome: %s\n", (p+i)->nome);
		printf("RA: %s\n", (p+i)->RA);
		printf("Nascimento: %d/%d/%d\n",p->niver.dia,p->niver.mes,p->niver.ano);
		printf("Media: %.2f\n\n", (p+i)->media);
	}
}


int main(){
	aluno *p=NULL;
	int aux,i; //i contador e auxiliar do ponteiro
	
    while(aux!=4){
        printf("CONTROLE DE NOTAS\n1-Cadastro\n2-Controle\n3-Mostrar\n4-Sair\n");
        scanf(" %d", &aux);
          
        if(aux == 1){
            aloca(&p,i+1);
            cadastro(p+i);
            i++;
        }
        else if(aux == 2) controle(p,i);
        else if(aux == 3) mostra(p,i);
        else if(aux != 4) printf("Numero invalido\n");      
    }
	
}
