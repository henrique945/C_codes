//Henrique Rodrigues Silva  RA:190898

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct pot{
	float *ind;
	float *ele;
}pot;

void aloca(pot **p){
	if((*p=(pot *)realloc(*p,1*sizeof(pot))) == NULL) printf("Erro\n");
}

void aloca_float(float **p, int tam){
	if((*p=(float*)realloc(*p,tam*sizeof(float))) == NULL) printf("Erro\n");
}

float calc(pot *p, float a, int n){   //acha o valor de y para determinado x, f(x)=y
	float a_prox=0;
	int i;
	
	for(i=0;i<=n;i++){
		a_prox += (*(p->ind+i))*(pow(a,*(p->ele+i)));
	}
		
	return (roundf(a_prox * 1000)/1000);
}

int calcula(pot *p, int n){
	float a, b, a_prox, b_prox, erro, m,m_prox=1;
	int i;
	
	printf("Digite o erro da equacao\n");
	scanf(" %f",&erro);
	
	printf("Digite o intervalo da equacao\n");
	scanf(" %f %f",&a,&b);
	
	i=0;
	while((m_prox > erro) || (-m_prox > erro)){	   //criterio de parada escolhido: |f(m)| < erro
		m=(a+b)/2;
		m= roundf(m*1000)/1000; //arredonda 3 casas decimais depois da virgula (float)
		
		a_prox = calc(p,a,n);
		b_prox = calc(p,b,n);
		m_prox = calc(p,m,n);
		printf("%d   a = %.3f  m = %.3f  b = %.3f     f(a) = %.3f  f(m) = %.3f  f(b) = %.3f\n",i,a,m,b,a_prox,m_prox,b_prox);
		
		//roundf(val * 1000) / 1000   para arredondar um float na 3 casa decimal
		
		if((a_prox < 0 && m_prox > 0) || (a_prox > 0 && m_prox < 0) ){
			a = a;
			b = m;
		}
		else if((m_prox < 0 && b_prox > 0)|| (m_prox > 0 && b_prox < 0) ){
			a=m;
			b=b;
		}
		else if(a_prox*m_prox > 0 || b_prox*m_prox > 0){
			printf("No intervalo nao ha raiz!\n");
			return 0;
		}
		i++;
	}
	printf("O valor de k = %d",i-1);	
}

int recebe(pot *p){ //recebe a quantidade a ser alocada, e recebe os parametros da equação
	int n,i,aux;
	
	printf("Digite o grau da equacao\n");
	scanf(" %d",&n);
	
	p->ind=NULL;
	p->ele=NULL;
	aloca_float(&(p->ind),n+1);
	aloca_float(&(p->ele),n+1);
	
	aux=n;
	for(i=0;i<=n;i++){
		printf("Digite o indice %d\n",aux);
		scanf("%f",(p->ind+i));
		//printf("%f",*(p->ind+i));
		*(p->ele+i) = aux;
		aux--;
	}
	return n;
}

int main(){
	int i,n,aux;
	pot *p=NULL;
	
	aloca(&p);
	n=recebe(p);
	calcula(p,n);

	return 0;
}
