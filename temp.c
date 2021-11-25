#include <stdio.h>
#include "./include/canvas_utils.h"
int main() {
int i =  10 ;
char * hola = "DONE!";
while ( i  <  30 ) {
printf("%d\n", (int) ( i  +  1 ));
i =  i  +  3 ;
if ( i  %  2  ==  0 ) {
return 0  ;}
}
printf("%s", hola);
return 0;

}