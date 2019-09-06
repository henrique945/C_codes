#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	int i,n,aux;
	float a, b, a_prox, b_prox, erro, m,m_prox=1;
	float ind[10],ele[10];
	
	printf("Digite o grau da equacao\n");
	scanf(" %d",&n);
	aux = n;
	for(i=0;i<=n;i++){
		printf("Digite o indice %d\n",aux);
		scanf(" %f",&ind[i]);
		ele[i] = aux;
		aux--;
	}
	
	printf("Digite o erro da equacao\n");
	scanf(" %f",&erro);
	
	printf("Digite o intervalo da equacao\n");
	scanf(" %f %f",&a,&b);
		
	i=0;
	while((m_prox > erro) || (-m_prox > erro)){	
		m=(a+b)/2;
		
		//equação
		a_prox = ind[0]*pow(a,ele[0]) + ind[1]*pow(a,ele[1]) + ind[2]*pow(a,ele[2]) + ind[3]*pow(a,ele[3]) + ind[4]*pow(a,ele[4]) + ind[5]*pow(a,ele[5]);
		b_prox = ind[0]*pow(b,ele[0]) + ind[1]*pow(b,ele[1]) + ind[2]*pow(b,ele[2]) + ind[3]*pow(b,ele[3]) + ind[4]*pow(b,ele[4]) + ind[5]*pow(b,ele[5]);
		m_prox = ind[0]*pow(m,ele[0]) + ind[1]*pow(m,ele[1]) + ind[2]*pow(m,ele[2]) + ind[3]*pow(m,ele[3]) + ind[4]*pow(m,ele[4]) + ind[5]*pow(m,ele[5]);
		
		printf("%d   a = %.3f  m = %.3f  b = %.3f     f(a) = %.3f  f(m) = %.3f  f(b) = %.3f\n",i,a,m,b,a_prox,m_prox,b_prox);
		
		if((a_prox < 0 && m_prox > 0) || (a_prox > 0 && m_prox < 0) ){
			a = a;
			b = m;
		}
		else if((m_prox < 0 && b_prox > 0)|| (m_prox > 0 && b_prox < 0) ){
			a=m;
			b=b;
		}
		i++;
	}
	
	return 0;
}
