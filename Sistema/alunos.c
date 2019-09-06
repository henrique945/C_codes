//ponteiros para estruturas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
	char *nome;
	float nota;
}aluno;

void aloca(aluno **p,int tam){
	if((*p=(aluno*)realloc(*p,tam*sizeof(aluno))) == NULL) printf("ERRO");
}

void aloca_char(char **p, int tam){
	if((*p=(char*)realloc(*p,tam*sizeof(char))) == NULL) printf("ERRO");
}

void cadastra(aluno *p){
	char nome[30];
	int tam;	
	printf("Digite o nome do aluno:\n");
	gets(nome);
	fflush(stdin);
	tam=strlen(nome);
	p->nome=NULL;
	aloca_char(&(p->nome),tam+1);
	strcpy(p->nome,nome);
	printf("Digite a nota do aluno:\n");
	scanf(" %f", &p->nota);
	fflush(stdin);
}

void mostra(aluno *p, int tam){
	int i;
	
	for(i=0; i<tam;i++){
		printf("Nome:  %s    ",(p+i)->nome);
		printf("Nota:  %f\n",(p+i)->nota);
	}
	
}

int main(){
	aluno *p=NULL;
	int cont=0;
	char aux;
	
	
	while(aux!='n'){
		aloca(&p,cont+1);
		cadastra(p+cont);		
		printf("Cadastrar aluno <s/n>\n");
		scanf("%c",&aux);
		fflush(stdin);
		cont++;
	}
	mostra(p,cont);
	
}
