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
 
void cadastro(lib *p){
    int i;  
     
    printf("Indice do livro\n");
    scanf(" %d", &i);
    i--;
     
    p = p + i;
    fflush(stdin);
    printf("Nome\n");
    gets(p->book.nome);
    fflush(stdin);
    printf("Autor\n");
    gets(p->book.autor);
    printf("Materia:\n1-Historia 2-Matematica 3-Biologia\n");
    scanf(" %d", &p->materia);
    fflush(stdin);
    printf("Codigo:\n");
    scanf(" %f", &p->book.code);
    printf("Emprestado 0-Nao 1-Sim\n");
    scanf(" %d", &p->book.emprestado);
    fflush(stdin);
    p = p - i;				//porque utlizar esta operação ao inves de p++; Pq vai e volta, mesmo fora de sequencia?
         
}
 
int main(){
    int aux=1, aux2, i, j, existe=0;
    char name_aux[30];
    lib li[50];
     
    while(aux!=0){
        printf("BEM VINDO A SUA BIBLIOTECA\n1-Cadastro de livros\n2-Procurar livro\n3-Apagar registro\n0-Sair\n");
        scanf(" %d", &aux);
         
        if(aux==1){
             
            cadastro(li);
        }
        else if(aux==2){
            printf("Procurar por 0-indice ou 1-nome\n");
            scanf(" %d", &aux2);
             
            if(aux2==0){
                printf("Digite o indice\n");
                scanf(" %d", &i);
                i--;
                 
                printf("\nNome: %s\n", li[i].book.nome);
                printf("Autor: %s\n", li[i].book.autor);
                if(li[i].materia == 1) printf("Materia: Historia");
                else if(li[i].materia == 2) printf("Materia: Matematica");
                else if(li[i].materia == 3) printf("Materia: Biologia");
                 
                printf("\n%.2f\n", li[i].book.code);    
                 
                if(li[i].book.emprestado == 0) printf("Disponivel\n\n");
                else if(li[i].book.emprestado == 1) printf("Indisponivel\n\n");
            }
             
            else if(aux2==1){
                printf("Digite o nome\n");
                fflush(stdin);
                gets(name_aux);
                 
                for(j=0;j<5;j++){
                    if(strcmp(name_aux,li[j].book.nome) == 0){
                        printf("\nNome: %s\n", li[j].book.nome);
                        printf("Autor: %s\n", li[j].book.autor);
                        if(li[j].materia == 1) printf("Materia: Historia");
                        else if(li[j].materia == 2) printf("Materia: Matematica");
                        else if(li[j].materia == 3) printf("Materia: Biologia");
                         
                        printf("\n%.2f\n", li[j].book.code);    
                         
                        if(li[j].book.emprestado == 0) printf("Disponivel\n\n");
                        else if(li[j].book.emprestado == 1) printf("Indisponivel\n\n");
                        existe++;
                    }
                 
                }
                if(existe == 0) printf("Nome nao encontrado\n");
                 
                 
            }   
        }
        else if(aux==3){
            printf("Qual livro deseja apagar?\n");
            scanf(" %d", &i);
            i--;
            li[i].book.nome[0] = '\0';
            li[i].book.autor[0] = '\0';
            li[i].materia = 0;
            li[i].book.emprestado = 2;
            li[i].book.code = 0;
        }
    }       
}
