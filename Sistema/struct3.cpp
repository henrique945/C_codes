#include <stdio.h>
#include <stdlib.h>
   
typedef struct aluno{     //defini��o
    char nome[50];
    int idade;
    int ra;
}Aluno;
   
void cadastro(Aluno *p){
    int i;
     
    for(i=0; i<3;i++){
        printf("Digite o nome: ");
        scanf(" %s", &(p->nome));
        printf("Digite a idade: ");
        scanf(" %d", &(p->idade));
        printf("Digite o ra: ");
        scanf(" %d", &(p->ra));
        p++;
    }
        
}
  
void imprime(Aluno a){
    printf("Nome: %s\nIdade: %d\n", a.nome, a.idade);
}
   
int main(){
    int i, idade;
    //struct aluno a1,a2,a3;
    Aluno a[3];
       
    cadastro(a);    
     
    //printf(" %s %d %d", a[0].nome, a[0].idade, a[0].ra);
       
    printf("Entre com uma idade especifica: \n");
    scanf(" %d", &idade);
       
    for( i = 0; i < 3; i++){
        if( a[i].idade < idade){
            imprime(a[i]);
        }
    }
      
}
