#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	int i;
	float a, b, a_prox, b_prox, erro, m,m_prox=1;
	
	printf("Digite o erro da equacao x3-x-1\n");
	scanf(" %f",&erro);
	
	printf("Digite o intervalo da equacao X3-x-1\n");
	scanf(" %f %f",&a,&b);
		
	
	while((m_prox > erro) || (-m_prox > erro)){	
		m=(a+b)/2;
		
		//equação
		a_prox = powf(a,3)-a-1;
		b_prox = powf(b,3)-b-1;
		m_prox = powf(m,3)-m-1;
		
		printf("a = %.3f  m = %.3f  b = %.3f     f(a) = %.3f  f(m) = %.3f  f(b) = %.3f\n",a,m,b,a_prox,m_prox,b_prox);
		
		if((a_prox < 0 && m_prox > 0) || (a_prox > 0 && m_prox < 0) ){
			a = a;
			b = m;
		}
		else if((m_prox < 0 && b_prox > 0)|| (m_prox > 0 && b_prox < 0) ){
			a=m;
			b=b;
		}
	}
	
	return 0;
}
