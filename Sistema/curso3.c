#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct aluno{
	char RA[7];
	char *nome;
	char *curso;
}aluno;

void aloca(aluno **p, int tam);
void aloca_char(char **pc, int tam);
void aloca_lista(char ***pl, int tam);
void cadastro(aluno *p, int tam, char ***lista, int *t_lista);
void maiuscula(char *p, int tam);
void mostra_aluno(aluno *p, int tam);
void mostra_lista(char **pl,int tam);
char* busca_lista(char **pl, int tam, char *aux);
void troca(aluno *p, int tam, char ***lista,int *t_lista);
int busca_ra(aluno *p, int tam, char *aux);

int main(){
	aluno *al=NULL;
	char **lista=NULL;
	int opt,cont=0,c_lista=0;
	
	do{
		printf("1-CADASTRO\n2-MOSTRA ALUNO\n3-MOSTRA CURSO\n4-ALTERA CURSO\n5-SAIR\n");
		scanf("%d",&opt);
		
		switch(opt){
			case 1:
				aloca(&al,cont+1);
				cadastro(al,cont,&lista,&c_lista);
				cont++;
				break;
			case 2:
				mostra_aluno(al,cont);
				break;
			case 3:
				mostra_lista(lista,c_lista);
				break;
			case 4:
				troca(al,cont,&lista,&c_lista);
				break;
		}
		
	}while(opt != 5);
	
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

void aloca_lista(char ***pl, int tam){
	if((*pl=(char**)realloc(*pl,tam*sizeof(char*))) == NULL){
		exit(1);
	}
}

void maiuscula(char *p, int tam){
	int i;
	
	for(i=0;i<tam;i++){
		if( *(p+i) >= 'a' && *(p+i) <= 'z'){
			*(p+i) -= 32;
		}
	}
}

void cadastro(aluno *p, int tam, char ***lista, int *t_lista){
	char aux[30];
	int t_aux;
	
	printf("Digite seu nome:\n");
	fflush(stdin);
	gets(aux);
	t_aux = strlen(aux);
	maiuscula(aux,t_aux);
	
	(p+tam)->nome=NULL;
	aloca_char(&((p+tam)->nome),t_aux+1); 
	strcpy((p+tam)->nome,aux);
	
	printf("Digite seu RA:\n");
	gets((p+tam)->RA);
	
	mostra_lista(*lista,*t_lista);
	printf("Digite seu curso:\n");
	fflush(stdin);
	gets(aux);
	t_aux = strlen(aux);
	
	maiuscula(aux,t_aux);
	(p+tam)->curso = busca_lista(*lista,*t_lista,aux);
	if((p+tam)->curso == NULL){
		aloca_lista(lista,*t_lista+1);
		*(*lista+*t_lista) = NULL;
		aloca_char(*lista+*t_lista,t_aux+1);
		strcpy(*(*lista+*t_lista),aux);
		(p+tam)->curso = *(*lista+*t_lista);
		(*t_lista)++;
	}
}

void mostra_aluno(aluno *p, int tam){
	int i;
	
	for(i=0;i<tam;i++){
		printf("Nome: %s\nRA: %s\nCurso: %s\n",(p+i)->nome,(p+i)->RA,(p+i)->curso);
	}
}

void mostra_lista(char **pl,int tam){
	int i;
	
	for(i=0;i<tam;i++){
		printf("Curso: %s\n",*(pl+i));
	}
}

char* busca_lista(char **pl, int tam, char *aux){
	int i;
	
	for(i=0;i<tam;i++){
		if(strcmp(*(pl+i),aux) == 0){
			return (*(pl+i));
		}
	}
	return NULL;
}

void troca(aluno *p, int tam, char ***lista,int *t_lista){
	char aux[30];
	int ind,t_aux;
	
	printf("Digite seu RA:\n");
	fflush(stdin);
	gets(aux);
	
	ind = busca_ra(p,tam,aux);
	if(ind == -1){
		printf("RA nao existe\n");
	}
	else{
		mostra_lista(*lista,*t_lista);
		printf("Novo curso:\n");
		fflush(stdin);
		gets(aux);
		t_aux = strlen(aux);
		maiuscula(aux,t_aux);

		(p+ind)->curso = busca_lista(*lista,*t_lista,aux);
		
		if((p+ind)->curso == NULL){
			aloca_lista(lista,*t_lista+1);
			
			*(*lista+*t_lista) = NULL;
			aloca_char(*lista+*t_lista,t_aux+1);
			strcpy(*(*lista+*t_lista),aux);
			
			(p+ind)->curso = *(*lista+*t_lista);
			(*t_lista)++;
		}		
	}
}

int busca_ra(aluno *p, int tam, char *aux){
	int i;
	
	for(i=0;i<tam;i++){
		if(strcmp(((p+i)->RA),aux) == 0){
			return i;
		}
	}
	return -1;
}



















