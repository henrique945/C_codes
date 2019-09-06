#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
	char *nome;
	char RA[7];
	float nota[2];
	float media;
}aluno;

void aloca(aluno **p,int tam){
	if((*p=(aluno*)realloc(*p,tam*sizeof(aluno)))==NULL) printf("ERRO");	
}

void aloca_char(aluno **p, int tam){
	if((*p=(char*)realloc(*p,tam*sizeof(char)))==NULL) printf("ERRO");
}

void cadastro(aluno *p){
	char aux[80];
	static int RA = 1000;
	int tam;
	
	//itoa ( int value, char * str, int base )
	
	printf("Digite o nome do aluno:\n");
	fflush(stdin);
	gets(aux);
	fflush(stdin);
	tam=strlen(aux);
	p->nome=NULL;
	aloca_char(&(p->nome),tam+1);
	strcpy(p->nome,aux);
	itoa(RA, p->RA, 10);
	printf("RA: %s\n", p->RA);
	RA++;
	p->nota[0] = 0;
	p->nota[1] = 0;
	p->media = 0;	
	
}

void controle(aluno *p, int tam){
	char aux[80];
	int i,achou=0;
	
	printf("Digite o RA do aluno:\n");
	fflush(stdin);
	gets(aux);
	
	for(i=0;i<tam;i++){
		if(strcmp((p+i)->RA,aux) == 0){
			printf("RA -> %s \n", (p+i)->nome);
			printf("Digite a primeira nota:\n");
			scanf(" %f", &((p+i)->nota[0]));
			printf("Digite a segunda nota:\n");
			scanf(" %f", &((p+i)->nota[1]));
			(p+i)->media = ((p+i)->nota[0] + (p+i)->nota[1])/2;
			printf("Media: %.2f\n", (p+i)->media);
			achou++;
		}
	}
	if(achou == 0) printf("RA nao encontrado\n");
}

int main(){
	aluno *p=NULL;
	int aux,i; //i contador e auxiliar do ponteiro
	
    while(aux!=3){
        printf("CONTROLE DE NOTAS\n1-Cadastro\n2-Controle\n3-Sair\n");
        scanf(" %d", &aux);
          
        if(aux == 1){
            aloca(&p,i+1);
            cadastro(p+i);
            i++;
        }
        else if(aux == 2) controle(p,i);
        else if(aux != 3) printf("Digite o numero valido\n");      
    }
	
}
