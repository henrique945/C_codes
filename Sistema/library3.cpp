#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
typedef struct livro{
    char nome[30];
    char autor[20];
    float code;
    int emprestado; 
}livro;
 
typedef struct lib{
    int materia;
    livro book;
}lib;
 
void aloca(lib **p, int tam){
	if((*p= (lib*) realloc(*p,tam*sizeof(lib))) == NULL) printf("ERRO");
}
 
void cadastro(lib *p){
	fflush(stdin);
    printf("Nome\n");
    gets(p->book.nome);
    fflush(stdin);
    printf("Autor\n");
    gets(p->book.autor);
    printf("Materia:\n1-Historia 2-Matematica 3-Biologia 4-Ficcao 5-Bibliografia\n");
    scanf(" %d", &p->materia);
    fflush(stdin);
    printf("Codigo:\n");
    scanf(" %f", &p->book.code);
    printf("Emprestado 0-Nao 1-Sim\n");
    scanf(" %d", &p->book.emprestado);
    fflush(stdin);
}

void materia(lib *q){
	if(q->materia == 1) printf("Materia: Historia\n");
	else if(q->materia == 2) printf("Materia: Matematica\n");	
	else if(q->materia == 3) printf("Materia: Biologia\n");
	else if(q->materia == 4) printf("Materia: Ficcao\n");
	else if(q->materia == 5) printf("Materia: Bibliografia\n");
}
void procurar(lib *p, int tam){
	int aux, i,existe=0;
	char nome[30];
	
	printf("Procurar por 1-nome ou 2-autor\n");
    scanf(" %d", &aux);
             
	if(aux==1){
        printf("Digite o nome\n");
        fflush(stdin);
        gets(nome);
        
        for(i=0;i<tam;i++){
        	if(strcmp((p+i)->book.nome,nome) == 0){
        		printf("\nNome: %s\n", (p+i)->book.nome);
        		printf("Autor: %s\n", (p+i)->book.autor);
        		printf("\n%.2f\n", (p+i)->book.code);
				materia(p+i);
				if((p+i)->book.emprestado == 0) printf("Disponivel\n\n");
        		else if((p+i)->book.emprestado == 1) printf("Indisponivel\n\n"); 
        		existe++;
			}
		}
		if(existe == 0) printf("Nome nao encontrado\n");
    }
         
    else if(aux==2){
        printf("Digite o autor\n");
        fflush(stdin);
        gets(nome);
         
        for(i=0;i<tam;i++){
            if(strcmp((p+i)->book.autor,nome) == 0){
                printf("\nNome: %s\n", (p+i)->book.nome);
        		printf("Autor: %s\n", (p+i)->book.autor);
        		printf("\n%.2f\n", (p+i)->book.code);
				materia(p+i);
				if((p+i)->book.emprestado == 0) printf("Disponivel\n\n");
        		else if((p+i)->book.emprestado == 1) printf("Indisponivel\n\n");
                existe++;
            }
        }
        if(existe == 0) printf("Autor nao encontrado\n");     
    }  
}

void erase(lib *p,int tam){
	int i;
	float code;
	
	printf("Qual livro deseja apagar?(codigo)\n");
	scanf(" %f", &code);
	
	for(i=0;i<tam;i++){
    	if(((p+i)->book.code) == code){
    		(p+i)->book.nome[0] = '\0';
       		(p+i)->book.autor[0] = '\0';
        	(p+i)->materia = 0;
       		(p+i)->book.emprestado = 2;
       	    (p+i)->book.code = 0;
		}
	}	
}
 
int main(){
    int aux=1,cont=0;
    lib *p=NULL;
     
    while(aux!=0){
        printf("BEM VINDO A SUA BIBLIOTECA\n1-Cadastro de livros\n2-Procurar livro\n3-Apagar registro\n0-Sair\n");
        scanf(" %d", &aux);
         
        if(aux==1){
            aloca(&p,cont+1); 
            cadastro(p+cont);
            cont++;
        }
        else if(aux==2) procurar(p,cont);
        else if(aux==3) erase(p,cont);        
    }       
}
