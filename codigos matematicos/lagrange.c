#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void aloca_float(float **p, int tam);

void show(float *x, float *fx, int tam);

int main(){
	int i,j,ponto;
	float *x=NULL,*fx=NULL,L,P=0,ex;

	printf("Quantidade de pontos?\n");   //só funciona para dois pontos
	scanf(" %d",&ponto);

	for(i=0;i<ponto;i++){
		aloca_float(&x,i+1);
		aloca_float(&fx,i+1);
		printf("X%d = ",i);
		scanf(" %f",(x+i));
		printf("f(x%d) = ",i);
		scanf(" %f",(fx+i));
	}

	show(x,fx,ponto);

	printf("Digite o X desejado: ");
	scanf(" %f",&ex);

	for(i=0;i<ponto;i++){
		if(i == 0){
			j=1;
		}
		else if(i == 1){
			j=0;
		}

		L = (ex - *(x+j))/(*(x+i) - *(x+j));
		L = (roundf(L*100))/100;

		P += L * *(fx+i);
		P = (roundf(P*100))/100;


	}
	printf("Valor encontrado: %.2f\n",P);

	//calcular L
	// L0 = (ex-x1)/(x0-x1)    //L1 = (ex-x0)/(x1-x0)





	
	return 0;
}

void aloca_float(float **p, int tam){
	if((*p=(float *)realloc(*p,tam*sizeof(float))) == NULL){
		printf("Erro\n");
		exit(1);
	}


}

void show(float *x, float *fx, int tam){
	int i;

	printf("X      ");
	for(i=0;i<tam;i++){
		printf("%.2f    ",*(x+i));
	}
	printf("\nF(x)   ");
	for(i=0;i<tam;i++){
		printf("%.2f    ",*(fx+i));
	}
}












