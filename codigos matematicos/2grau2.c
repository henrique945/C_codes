#include <stdio.h>
#include <math.h>

void recebe(float *p){
	int i;
	
	for(i=0; i<3; i++){
		//'printf("Digite o valor %c: ",'a'+1);
        scanf(" %f", p+i);    
    }
	
}

float calc_delta(float *p){
	float d;
	
	d = pow	(*(p+1),2) - 4 * *(p) * *(p+2);   //b²-4ac
	
	return d;
} 

void calc_raiz(float *p, float *r, float d){
	
	*r = (-*(p+1) + sqrt(d)) / 2 * *(p);
	*(r+1) = (-*(p+1) - sqrt(d)) / 2 * *(p);
} 

void most_raiz(float *r){
	int i;
	
	for(i=0; i<2; i++){
		printf("raiz %d: %.2f\n", i+1, *(r+i));
	}
}

int main(){
	float a[3],x[2],delta;
	
    printf("Digite a, b, c da equacao de 2 grau:\n");
    recebe(a);
    delta = calc_delta(a);
    
    if(delta < 0){
        printf("Nao existe raiz real");
    }
    else{
        calc_raiz(a,x, delta);
		most_raiz(x);   
    }
	return 0;   
}
