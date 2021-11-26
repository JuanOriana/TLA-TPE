#include <stdio.h>
#include "./include/canvas_utils.h"
int main() {
double n1 = (double) 0.9 ;
int n2 = (int) 3 ;
printf("%s", "Bienvenido al evaluador matematico!\n\n");
printf("%s", "Se trabaja con el double n1 = ");
printf("%lf",(double)(n1));
printf("%s", "\nY con el int n2 = ");
printf("%d",(int)(n2));
printf("%s", "\n\nn1 + n2: ");
printf("%f", n1  +  n2 );
printf("%s", "\nn1 - n2: ");
printf("%f", n1  -  n2 );
printf("%s", "\nn1 * n2: ");
printf("%f", n1  *  n2 );
printf("%s", "\nn1 / n2: ");
printf("%f", n1  /  n2 );
printf("%s", "\nn2 % 3: ");
printf("%d",(int) n2  % (int) 3 );
printf("%s", "\nn1 && n2: ");
printf("%d", n1  &&  n2 );
printf("%s", "\n((n1+n2)/n2*n1)*n1: ");
printf("%f", (  (  n1  +  n2  )  /  n2  *  n1  )  *  n1 );
int n = (int) -  1 ;
printf("%s", "\n\nAhora comienza el test de precision. Ingresa un numero del 1 al 100. Se dividira 1 en N partes iguales y \
las sumaremos de a una a una variable double. Finalmente se compara con el valor \
integral para ver la precision.\n\n");
printf("%s", "Ingresa tu numero: ");
scanf("%d", &n);if ( n  <=  0  ||  n  >  100 ) {
printf("%s", "El numero tiene que ir del 1 al 100!\n");
return -  1  ;}
double fract = (double) 1.0  /  n ;
double sum = (double) 0 ;
printf("%s", "Se usara una fraccion de: ");
printf("%lf",(double)(fract));
while ( n ) {
sum = (double) sum  +  fract ;
n = (int) n  -  1 ;
}
printf("%s", "\n\nEl valor resultante de la suma es:");
printf("%lf",(double)(sum));
printf("%s", "\nEl resultado de hacer la suma == 1 es: ");
if ( sum  ==  1 ) {
printf("%s", "VERADERO\n\n");

} else {
printf("%s", "FALSO\n\n");
}
return 0;

}