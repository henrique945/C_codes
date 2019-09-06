#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct aluno{
	char *nome;
	char *curso;
}aluno;

void aloca(aluno **p, int tam);
void aloca_char(char **pc, int tam);
void cadastra(aluno *p, int tam);
void mostra(aluno *p, int tam);
void maiscula(char *p, int tam);
char* busca_curso(aluno *p, int tam, char *aux);

int main(){
	aluno *al = NULL;
	int cont=0;
	char opt;
	
	
	do{
		aloca(&al,cont+1);
		cadastra(al,cont);
		cont++;
		
		printf("Deseja continuar: <S/N>\n");
		scanf("%c",&opt);
		fflush(stdin);
	}while(opt != 'n' && opt != 'N');
	
	mostra(al,cont);
	
	
	
	return 0;
}

void aloca(aluno **p, int tam){
	if((*p=(aluno*)realloc(*p,tam*sizeof(aluno))) == NULL){
		exit(1);
	}
}

void aloca_char(char **pc, int tam){
	if((*pc=(char*)realloc(*pc,tam*sizeof(char))) == NULL){
		exit(1);
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

char* busca_curso(aluno *p, int tam, char *aux){
	int i;
	
	for(i=0;i<tam;i++){
		if(strcmp((p+i)->curso,aux) == 0){
			return ((p+i)->curso);
		}
	}
	return NULL;
	
}

void cadastra(aluno *p, int tam){
	char aux[30];
	int t_aux;
		
	printf("Digite seu nome:\n");
	fflush(stdin);
	gets(aux);
	t_aux=strlen(aux);
	maiuscula(aux,t_aux);
	
	(p+tam)->nome = NULL;
	aloca_char((&(p+tam)->nome),t_aux+1);
	strcpy((p+tam)->nome,aux);
	
	printf("Digite seu curso:\n");
	fflush(stdin);
	gets(aux);
	t_aux=strlen(aux);
	maiuscula(aux,t_aux);
	
	(p+tam)->curso = busca_curso(p,tam,aux);
	
	if((p+tam)->curso == NULL){
		aloca_char(&((p+tam)->curso),t_aux+1);
		strcpy((p+tam)->curso,aux);
	}
}

void mostra(aluno *p, int tam){
	int i;
	
	for(i=0;i<tam;i++){
		printf("NOME: %s\n",(p+i)->nome);
		printf("CURSO: %s\n",(p+i)->curso);
	}
}


















