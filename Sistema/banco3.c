#include <stdio.h>
#include <stdlib.h>
 
typedef struct cliente{
    char nome[30];
    int conta;
    float saldo;
}cliente;

int validation(cliente *p){
	int conta,i;
	
	printf("Digite o numero da conta:\n");
	scanf(" %d",&conta);
	
	for(i=0;i<10;i++){
		if(conta == (p+i)->conta) return i; //se encontrou retorna a posicao
		//se usamos (p+i) não perdemos a referencia do ponteiro	
	}
	return -1; //se nao encontrou, -1 é uma posicao invalido
}
 
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
 
void dep_ret(cliente *p){
    int aux,i; 
    float valor,posivel;
    
	i=validation(p);   
    if(i != -1){ //se tiver encontrado a conta é verdadeiro
    	printf("Nome: %s\n",(p+i)->nome); //p+i -> assim a gente altera exatamente a estrutura que queremos
        printf("Saldo: %.2f\n",(p+i)->saldo);
        printf("Valor do deposito/retirada:\n");
        scanf(" %f",&valor);
        posivel = ((p+i)->saldo) + valor;
        if(posivel >= 0){    
            (p+i)->saldo += valor;
            printf("Nova saldo: %.2f\n",(p+i)->saldo);
        }
        else printf("Saldo indisponivel\n");
	}
	else printf("Numero da conta invalido ou nao cadastrado\n");
}

void list_cliente(cliente *p, int max){
	int i;
	
	for(i=0;i<max;i++){
		printf("Nome: %s			Conta: %d	Saldo:%.2f\n",(p+i)->nome,(p+i)->conta,(p+i)->saldo);
	}
}

void emprestimo(cliente *p){
	int i;
	float salario,emprest;
	char opt;
	
	i=validation(p);
	if(i != -1){
		printf("Nome: %s			Saldo:%.2f\n",(p+i)->nome,(p+i)->saldo);
		printf("Salario:\n");
		scanf(" %f", &salario);
		
		emprest = salario*0.2;
		printf("Emprestimo de %.2f, valor a ser pago %.2f\n",emprest,(emprest+emprest*0.05));
		printf("Confirmar emprestimo: S-Sim  N-Nao\n");
		scanf(" %c",&opt);
		if(opt == 'S' || opt == 's'){
			(p+i)->saldo += emprest;
			printf("Novo saldo: %.2f\n", (p+i)->saldo);	
		}	
	}
}

void doc(cliente *p){
	int i,j;
	float valor;
	
	i=validation(p);
	j=validation(p);
	if(i != -1){
		if(j != -1){
			printf("Transferencia de:\n");
			printf("Nome: %s			Conta: %d	Saldo:%.2f\n",(p+i)->nome,(p+i)->conta,(p+i)->saldo);
			printf("Para:\n");
			printf("Nome: %s			Conta: %d	Saldo:%.2f\n",(p+j)->nome,(p+j)->conta,(p+j)->saldo);
			printf("Valor da transferencia:\n");
			scanf(" %f", &valor);
			if(valor > 0){
				if((p+i)->saldo >= valor){
					(p+i)->saldo -= valor;
					(p+j)->saldo += valor;
					printf("Nome: %s			Conta: %d	Saldo:%.2f\n",(p+i)->nome,(p+i)->conta,(p+i)->saldo);
					printf("Nome: %s			Conta: %d	Saldo:%.2f\n",(p+j)->nome,(p+j)->conta,(p+j)->saldo);
				}
				else printf("Saldo indisponivel\n");	
			}
			else printf("Valor invalido\n");
		}
	}
	
}
 
int main(){
    int aux=0,i=0;
    cliente client[10], *p;
    p=client;
 
    while(aux!=6){
        printf("SISTEMA BANCARIO\n1-Cadastro\n2-Deposito/Retirada\n3-Lista de Cliente\n4-Emprestimo\n5-Transferencia\n6-Sair\n");
        scanf(" %d", &aux);
         
        if(aux == 1){
            cadastro(p+i);
            i++;
        }
        else if(aux == 2) dep_ret(p);
        else if(aux == 3) list_cliente(p,i);
		else if(aux == 4) emprestimo(p);
		else if(aux == 5) doc(p);
        else if(aux != 6) printf("Digite o numero valido\n");      
    }
}
