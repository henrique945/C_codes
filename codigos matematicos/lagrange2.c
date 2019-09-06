#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void aloca_float(float **p, int tam);
void show(float *x, float *fx, int tam);
void calc(float *x, float *fx, int tam);

int main(){
	int i,ponto;
	float *x=NULL,*fx=NULL;

	printf("Quantidade de pontos?\n");   //só funciona para dois ou tres pontos
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
	calc(x,fx,ponto);



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

void calc(float *x, float *fx, int tam){
	int i,k,j;
	float L,P=0,ex;

	printf("Digite o X desejado: ");
	scanf(" %f",&ex);

	for(i=0;i<tam;i++){
		if(tam == 2){
			if(i == 0){
				j=1;
				k=ex;
			}
			else if(i == 1){
				j=0;
				k=ex;
			}
			L = (ex - *(x+j))/(*(x+i) - *(x+j));			
		}
		else if(tam == 3){
			if(i == 0){
				j=1;
				k=2;
			}
			else if(i == 1){
				j=0;
				k=2;
			}
			else if(i == 2){
				j=0;
				k=1;
			}
			L = (ex - *(x+j))/(*(x+i) - *(x+j));
			L *= (ex - *(x+k))/(*(x+i) - *(x+k));
		}



		L = (roundf(L*100))/100;

		P += L * *(fx+i);
		P = (roundf(P*100))/100;


	}
	printf("Valor encontrado: %.2f\n",P);

}










