//Henrique Rodrigues Silva  RA:190898

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void aloca_float(float **p, int tam){
	if((*p=(float*)realloc(*p,tam*sizeof(float))) == NULL) printf("Erro\n");
}

float calc_k(float a, float b, float erro){
	float k;
	
	k = (log10(fabs(b-a)) - log10(erro))/log10(2);
	
	return k;
}

float calc(float *ind, float *ele, float a, int n){   //acha o valor de y para determinado x, f(x)=y
	float a_prox=0;
	int i;
	
	for(i=0;i<=n;i++){
		a_prox += (*(ind+i))*(pow(a,*(ele+i)));
	}
		
	return (roundf(a_prox * 1000)/1000);
}

int calcula(float *ind, float *ele, int n){
	float a, b, a_prox, b_prox, erro, m,m_prox=1,k;
	int i;
		
	printf("Digite o erro da equacao\n");
	scanf(" %f",&erro);
	
	printf("Digite o intervalo da equacao\n");
	scanf(" %f %f",&a,&b);
	
	k=calc_k(a,b,erro);
	
	i=0;
	
	while((m_prox > erro) || (-m_prox > erro)){	   //criterio de parada escolhido: |f(m)| < erro
		m=(a+b)/2;
		m= roundf(m*1000)/1000; //arredonda 3 casas decimais depois da virgula (float)
		
		a_prox = calc(ind,ele,a,n);
		b_prox = calc(ind,ele,b,n);
		m_prox = calc(ind,ele,m,n);
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
	printf("A raiz da funcao eh %.3f com erro %.3f\n",m,erro);
	printf("Quantidade de iteracoes %0.f (k = %.2f)\n",ceil(k),k);
		
}

int recebe(float *ind, float *ele,int n){ //recebe a quantidade a ser alocada, e recebe os parametros da equação
	int i,aux;
	
	aux=n;
	for(i=0;i<=n;i++){
		printf("Digite o indice %d\n",aux);
		scanf("%f",ind+i);
		*(ele+i) = aux;
		aux--;
	}
	return n;
}

int main(){
	int i,n,aux;
	float *ind=NULL,*ele=NULL;
	
	printf("Digite o grau da equacao\n");
	scanf(" %d",&n);
	
	aloca_float(&ind,n+1);
	aloca_float(&ele,n+1);
	
	recebe(ind,ele,n);
	calcula(ind,ele,n);

	return 0;
}
