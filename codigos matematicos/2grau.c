#include <stdio.h>
#include <math.h>
 
int baskara(){
    float x1, x2;
    int i, delta;
    float a[3];
     
    for(i=0; i<3; i++){
        scanf(" %f", &a[i]);    
    }
    delta = powf(a[1],2) - 4*a[0]*a[2];
     
    if(delta < 0){
        printf("Nao existe raiz real");
    }
    else{
        x1=(-a[1]+sqrt(delta))/2*a[0];
        x2=(-a[1]-sqrt(delta))/2*a[0];
        printf("Raizes %.2f e %.2f", x1, x2);   
    }   
    return 0;
}
 
int main(){
    printf("Digite a, b, c da equacao de 2 grau:\n");
    baskara();  
}
