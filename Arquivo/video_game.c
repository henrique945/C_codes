#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct game{
	int reg;
	char console[30];
	char game[30];
}game;

void aloca(game **p, int tam);
void cadastra(game *p, int tam);
int verifica(game *p);
void maiuscula(char *p);
void grava(game *p);
void show(game *p, int tam);

int main(){
	int opt,cont = 0;
	game *p = NULL;
	
	
	aloca(&p,1);
	printf("Bem vindo ao clube\n");
	do{
		cont = verifica(p);
		system("PAUSE");
		system("cls");	
		printf("1-Cadastra game\n2-Show games\n3-Sair\n");
		scanf("%d",&opt);
		
		switch(opt){
			case 1:
				cadastra(p,cont);
				break;
			
			case 2:
				show(p,cont);
				break;
				
			case 3:
				break;
			
			default:
				printf("Opcao invalida\n");
		}
		
	}while(opt != 3);
	
	return 0;
}

void aloca(game **p, int tam){
	if((*p=(game*)realloc(*p,tam*sizeof(game))) == NULL){
		printf("erro na alocacao\n");
		exit(1);
	}
	
}

void cadastra(game *p, int tam){
	char aux[30];
	
	p->reg = tam+1;
	printf("Registro %d:\n",p->reg);
	printf("Console: ");
	fflush(stdin);
	gets(aux);
	maiuscula(aux);
	strcpy(p->console,aux);
	printf("Game: ");
	fflush(stdin);
	gets(aux);
	maiuscula(aux);
	strcpy(p->game,aux);
	
	grava(p);
}

void grava(game *p){
	FILE *fptr = NULL;
	
	if((fptr = fopen("game.txt","a")) != NULL){
		fprintf(fptr," %d %s %s",p->reg,p->console,p->game);
	}
	fclose(fptr);
}

void show(game *p, int tam){
	FILE *fptr = NULL;
	
	if((fptr = fopen("game.txt","r")) != NULL){
		while(getc(fptr) != EOF){
			fscanf(fptr,"%d %s %s", &(p->reg),p->console,p->game);
			printf("Registro %d:\n",p->reg);
			printf("Console: %s\n",p->console);
			printf("Game: %s\n\n",p->game);
		}
		fclose(fptr);
	}
}

int verifica(game *p){
	int cont = 0;
	FILE *fptr = NULL;
	
	if((fptr = fopen("game.txt","r")) != NULL){
		while(getc(fptr) != EOF){
			fscanf(fptr,"%d %s %s",&(p->reg),p->console,p->game);
			cont = p->reg;
			
		}
		fclose(fptr);
	}
	
	return cont;
}

void maiuscula(char *p){
	int i;
	
	for(i=0;i<strlen(p);i++){
		if(*(p+i) >= 'a' && *(p+i) <= 'z'){
			*(p+i) -= 32;
		}
	}
}












