#include <stdio.h>
#include <stdlib.h>
 
typedef struct aluno{     //definição
    char nome[50];
    int idade;
    int ra;
}Aluno;
 
Aluno cadastro(){
    Aluno aux;
    printf("Digite o nome: ");
    scanf(" %s", &aux.nome);
    printf("Digite a idade: ");
    scanf(" %d", &aux.idade);
    printf("Digite o ra: ");
    scanf(" %d", &aux.ra);
         
    return aux;     
}

void imprime(Aluno a){
	printf("Nome: %s\nIdade: %d\n", a.nome, a.idade);
}
 
int main(){
    int i, idade;
    //struct aluno a1,a2,a3;
    Aluno a[3];
     
    for(i=0; i<3;i++){
        a[i] = cadastro();
    }
     
    //printf(" %s %d %d", a[0].nome, a[0].idade, a[0].ra);
     
    printf("Entre com uma idade especifica: \n");
    scanf(" %d", &idade);
     
    for( i = 0; i < 3; i++){
        if( a[i].idade < idade){
            imprime(a[i]);
        }
    }
    
}
