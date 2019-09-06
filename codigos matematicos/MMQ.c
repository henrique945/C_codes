//Henrique Rodrigues Silva - RA: 190898
//Matheus Thomé lopes - RA: 173044

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

void calc(float mat[][100]);

int main(){
	float mat[100][100];
	char opt,op;
	
	printf("SISTEMAS LINEARES UTILIZANDO O METODO DE MINIMOS MULTIPLOS QUADRADOS\n");
	do{
		system("PAUSE");
		system("cls");
		calc(mat);		
		
		printf("Deseja continuar o programa: <S/N>\n");
		fflush(stdin);
		scanf("%c",&opt);
		
	}while(opt != 'n' && opt != 'N');
	
	return 0;
}

void calc(float mat[][100]){ //linhas
	float pivo,aux[10],x[10],y[10],u[10][10],a[10];
	int cont = 0,t,n,i,ii,j,tam;
	char opt;
	
	printf("Quanto numeros deseja:\n");
	scanf("%d",&n);
	printf("Digite X:\n");
	for(i=0;i<n;i++){
		scanf("%f",&x[i]);
	}
	printf("Digite Y:\n");
	for(i=0;i<n;i++){
		scanf("%f",&y[i]);
	}
	
	do{
		printf("Grau:\n");
		scanf("%d",&tam);
		for(i=0;i<tam+1;i++){
			for(j=0;j<tam+2;j++){
				mat[i][j] = 0;
			}
			a[i] = 0;
		}
		
		
		
		for(i=0;i<tam+1;i++){
			for(j=0;j<n;j++){
				u[i][j] = pow(x[j],i);
			}
		}
		
		printf("MATRIZ:\n");
		
		for(i=0;i<tam+1;i++){
			for(j=0;j<tam+2;j++){
				for(ii=0;ii<n;ii++){
					if(j == tam+1){ //y
						mat[i][j] += (u[i][ii] * y[ii]); 
					}
					else{ //x
						mat[i][j] += (u[i][ii] * u[j][ii]);
					}
				}
				printf("%f ",mat[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		
		printf("GAUSS\n");
		for(t=0;t<tam;t++){
			printf("etapa %d\n",t+1);
			for(i=0;i<tam+1;i++){
				for(ii=0;ii<tam+2;ii++){
					
					if((cont == 0) && (i>t)){
						pivo = mat[i-1][t];
						for(j=t+1;j<tam+1;j++){
							aux[j] = mat[j][t]/pivo;
							
						}
						cont++;
					}
					if(i>t){
						mat[i][ii] -= (aux[i] * mat[t][ii]);
					}
					printf("%.2f ",mat[i][ii]);
				}
				printf("\n");
			}
		cont = 0;
		printf("\n");
		}
		
		
		
		printf("Deseja continuar: <S/N>\n");
		fflush(stdin);
		scanf("%c",&opt);
	}while(opt != 'n' && opt != 'N');
	
	
	
	
}

	

/*
3
5
10
30
-35.03
10
30
100
-110.02
30
100
354
-370.06
*/











