#include <stdio.h>
#include <stdlib.h>

typedef struct cliente{
	char nome[30];
	int conta;
	float saldo;
}cliente;

void cadastro(cliente *p){
	static int conta = 1000;
	
	printf("Digite o nome:\n");
	fflush(stdin);
	gets(p->nome);
	printf("Conta: %d\n\n",conta);
	p->conta = conta;
	p->saldo=0;
	conta++;
}

void dep_ret(cliente *q){
	int aux,i,achou=0;
	float valor,posivel;
	
	//funcao de validação	
	printf("Digite o numero da conta:\n");
	scanf(" %d",&aux);
	for(i=0;i<10;i++){
		if(aux == q->conta){
			printf("Nome: %s\n",q->nome);
			printf("Saldo: %.2f\n",q->saldo);
			printf("Valor do deposito/retirada:\n");
			scanf(" %f",&valor);
			posivel = (q->saldo) + valor;
			achou = 1;
			if(posivel >= 0){	
				q->saldo += valor;
				printf("Nova saldo: %.2f\n",q->saldo);
			}
			else printf("Saldo indisponivel\n");
		}
		q++;
	}
	if(achou == 0) printf("Numero da conta invalido ou nao cadastrado\n");	
}

int main(){
	int aux=0,i=0;
	cliente client[10], *p, *q;
	p=client;
	q=client;
	//p+i;

	while(aux!=3){
        printf("SISTEMA BANCARIO\n1-Cadastro\n2-Deposito/Retirada\n3-Sair\n");
        scanf(" %d", &aux);
        
        if(aux == 1){
        	cadastro(p);
        	p++;
		}
		else if(aux == 2) dep_ret(q);
        else if(aux != 3) printf("Digite o numero valido\n");  
        
	}
}
