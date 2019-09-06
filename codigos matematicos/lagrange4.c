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
	float L,P,ex;
	char opt;

	do{
		P=0;
		printf("\nDigite o X desejado: ");
		fflush(stdin);
		scanf(" %f",&ex);
		
		if(ex < *x || ex > *(x+tam-1)){
			printf("Numero fora do intervalo\n");
		}
		else{
			for(i=0;i<tam;i++){
				L=1;
				for(j=0;j<tam;j++){
					if(i != j){
						L *= (ex - *(x+j))/(*(x+i) - *(x+j));
					}
				}
				L = (roundf(L*100))/100;
				printf("\nL%d = %.2f",i,L);			
		
				P += L * *(fx+i);
				P = (roundf(P*100))/100;
			}
			printf("\nValor encontrado: %.2f\n",P);
			
			printf("Deseja encontrar outro X? <s/n>\n");
			fflush(stdin);
			scanf("%c",&opt);
		}
		

	}while(opt != 'n' && opt != 'N');

}










