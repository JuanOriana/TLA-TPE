#include <stdio.h>
#include "./include/canvas_utils.h"
int main() {
char * hola = "DONE!";
double n =  3 ;
while ( n  <  30 ) {
printf("%lf\n",(double)(n));
n =  n  +  0.5 ;
if ((int) n  % (int) 4  ==  0 ) {
return 0  ;}
}
printf("%s", hola);
return 0;

}