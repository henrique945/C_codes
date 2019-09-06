#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{     //definição
	char nome[50];
	int idade;
	int ra;
}Aluno;

int main(){
	int i, idade;
	//struct aluno a1,a2,a3;
	Aluno a[3];
	
	for(i = 0; i <3; i++){
		printf("Digite o nome: ");
		scanf(" %s", &a[i].nome);
		printf("Digite a idade: ");
		scanf(" %d", &a[i].idade);
		printf("Digite o ra: ");
		scanf(" %d", &a[i].ra);	
		}
	
	printf("Entre com uma idade especifica: \n");
	scanf(" %d", &idade);
	
	for( i = 0; i < 3; i++){
		if( a[i].idade < idade){
			printf("Nome: %s\nIdade: %d\n", a[i].nome, a[i].idade);
		}
	}
}

//3 alunos, digita uma idade;  imprimir os nomes e idades dos alunos com idade menor que a digitada

