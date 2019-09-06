//Henrique Rodrigues Silva - RA: 190898
//Matheus Thomé Lopes - RA: 173044

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

void aloca(float **p, int tam);
void recebe_dados(float *vet, int tam);
float trapezio(float *vet, int tam, float a, float b, int n);

int main(){
	float *vet = NULL,a,b,area,aux;
	int i,grau,n;
	char opt='S',op;
	
	printf("REGRA DOS TRAPEZIOS\n");
	do{
		system("PAUSE");
		system("cls");
		printf("Grau da equacao:\n");
		scanf("%d",&grau);
		grau++;
		aloca(&vet,grau);
		recebe_dados(vet,grau);
		printf("Digite o intervalo a:\n");
		scanf("%f",&a);
		printf("Digite o intervalo b:\n");
		scanf("%f",&b);
		
		if(a > b){
			aux = b;
			b = a;
			a = aux;
		}
		
		do{
			printf("Digite o numero de divisoes:\n");
			scanf("%d",&n);
			
			area = trapezio(vet, grau, a,b,n);
			printf("\nITR = %.4f\n",area);
			
			printf("Deseja continuar com a mesma equacao: <S/N>\n");
			fflush(stdin);
			scanf("%c",&op);
		}while(op != 'n' && opt != 'N');
		
		printf("Deseja continuar o programa: <S/N>\n");
		fflush(stdin);
		scanf("%c",&opt);
	}while(opt != 'N' && opt != 'n');
	
	return 0;
}

void aloca(float **p, int tam){
	if((*p=(float*)realloc(*p,tam*sizeof(float))) == NULL){
		printf("Erro de alocacao\n");
		exit(1);
	}
}

void recebe_dados(float *vet, int tam){
	int i;
	
	for(i=0;i<tam;i++){
		printf("Digite o grau %d: ",i);
		scanf("%f",(vet+i));
	}
	
}

float trapezio(float *vet, int tam, float a, float b, int n){
	float h,fvet[50],fx,area,t = 0; //altura
	int i,j,k=0;
	
	h = (b-a)/n;
	printf("\nAltura: %.2f\n",h);
	printf("a = %.2f \t b = %.2f\n\n",a,b);
	if(n == 1){
		fvet[0] = 0.0;
		fvet[1] = 0.0;
		for(j=0;j<tam;j++){
			if(*(vet+j) != 0){
				fvet[0] += (*(vet+j)) * powf(a,j);
				fvet[1] += (*(vet+j)) * powf(b,j);
			}
		}
		
		printf("\nValores de f(x):\n");
		printf("f(%.2f) = %.2f\n",a,fvet[0]);	
		printf("f(%.2f) = %.2f\n",b,fvet[1]);	
		
		area = (h/2) * (fvet[0] + fvet[1]);
		return area;
	}
	else{
		fx = a;
		for(i=0;i<n+1;i++){
			fvet[i] = 0.0;
			for(j=0;j<tam;j++){
				if(*(vet+j) != 0){
					fvet[i] += (*(vet+j)) * powf(fx,j);
				}
			}
			//printf("%.2f ",fvet[i]);	
			fx += h;
		}
		printf("\nValores de f(x):\n");
		
		fx = a;
		for(i=0;i<n+1;i++){
			if(i == 0 || i == n){
				t += fvet[i];
			}
			else{
				t += 2 * fvet[i];
			}
			printf("f(%.2f) = %.2f\n",fx,t);
			fx += h;
		}
		
		area = (h/2) * t;
		return area;
	}
}











