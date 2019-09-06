#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	int i;
	float a, b, a_prox, b_prox, erro, m,m_prox=1;
	
	printf("Digite o erro da equacao 3x3-4\n");
	scanf(" %f",&erro);
	
	printf("Digite o intervalo da equacao 3X3-4\n");
	scanf(" %f %f",&a,&b);
		
	
	while((m_prox > erro) || (-m_prox > erro)){	
		m=(a+b)/2;
		
		//equação
		a_prox = 3*powf(a,3)-4;
		b_prox = 3*powf(b,3)-4;
		m_prox = 3*powf(m,3)-4;
		
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
