#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int preenche_mat(float mat[][100]);
void calc(float mat[][100], int tam);
void show(float mat[][100], int tam);

int main(){
	float mat[100][100];
	char opt;
	int tam;
	
	printf("SISTEMAS LINEARES UTILIZANDO A ELIMINACAO DE GAUSS\n");
	do{
		system("PAUSE");
		system("cls");
		tam = preenche_mat(mat);
		calc(mat,tam);		
		show(mat,tam);
		
		printf("Deseja continuar: <S/N>\n");
		fflush(stdin);
		scanf("%c",&opt);
		
	}while(opt != 'n' && opt != 'N');
	
	
	
	return 0;
}

int preenche_mat(float mat[][100]){
	int i,j,n;
	
	printf("Quantas variaveis:\n");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		for(j=0;j<n+1;j++){
			scanf("%f",&mat[i][j]);
		}
	}
	
	return n;	
}

void calc(float mat[][100], int tam){ //linhas
	float aux;	
	int i,ii,j,line=1,col=0;
	
	for(i=1;i<tam;i++){
		for(ii=line;ii<=tam;ii++){
			
			aux = mat[i][col]/mat[i-1][col];
			printf("\naux = %f\n",aux);
			for(j=0;j<tam+1;j++){
				mat[i][j] = mat[i-1][j]*aux - mat[i][j];
			}
		}
		col++;
		line++;
	}
	show(mat,tam);
	
}

void show(float mat[][100], int tam){
	int i,j;
	
	for(i=0;i<tam;i++){
		for(j=0;j<tam+1;j++){
			printf("%.2f ",mat[i][j]);
		}
		printf("\n");
	}
	
	
}













