#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
	char *nome;
	char *curso;
}aluno;

void aloca(aluno **p,int tam);
void aloca_char(char **p,int tam);
void cadastra(aluno *p,int tam);
void mostra(aluno *p,int tam);
char* busca(aluno *p,int tam,char *aux);
void maiuscula(char *p,int tam);

int main(){
	char opt;
	int cont=0;
	aluno *p=NULL;
	
	while(opt!='n'&& opt!='N'){
		aloca(&p,cont+1);
		cadastra(p,cont);
		cont++;
		printf("Deseja continuar: <s/n>\n");
		scanf(" %c",&opt);
		fflush(stdin);
	}
	mostra(p,cont);
}

void aloca(aluno **p,int tam){
	if((*p=(aluno*)realloc(*p,tam*sizeof(aluno))) == NULL) printf("Erro");
}

void aloca_char(char **p,int tam){
	if((*p=(char*)realloc(*p,tam*sizeof(char))) == NULL) printf("Erro");
}

void cadastra(aluno *p, int tam){
	char aux[30];
	int t;
	
	printf("Digite o nome: \n");
	gets(aux);
	fflush(stdin);
	t=strlen(aux);
	maiuscula(aux,t);
	(p+tam)->nome=NULL;
	aloca_char(&((p+tam)->nome),t+1);
	strcpy((p+tam)->nome,aux);
	
	printf("Digite o curso: \n");
	gets(aux);
	fflush(stdin);
	t=strlen(aux);
	maiuscula(aux,t);
	(p+tam)->curso=NULL;
	
	(p+tam)->curso=busca(p,tam,aux); //recebe a posição se o curso ja existir ou NUll se não existir
	if((p+tam)->curso==NULL){
  		aloca_char(&((p+tam)->curso),t+1);
		strcpy((p+tam)->curso,aux);
    }	
}

void mostra(aluno *p, int tam){
	int i;
	
	for(i=0;i<tam;i++){
		printf("Nome: %s\n",(p+i)->nome);
		printf("Curso: %s\n",(p+i)->curso);
	}
}

void maiuscula(char *p,int tam){
	int i;
	
	for(i=0;i<tam;i++){
		if(*(p+i)>='a'&& *(p+i)<='z'){
			*(p+i)-=32; //por causa da tabela ASCII A=65 e a=97 
		}			
	}
}

char* busca(aluno *p,int tam,char *aux){
	int i;
	for(i=0;i<tam;i++){
	  	if(strcmp((p+i)->curso,aux)==0){
	   	 	return((p+i)->curso); //se achar um curso igual, retorna a posição desse curso já alocado
		  }
	}
	return NULL;
}

