#include <stdio.h>
#include "./include/canvas_utils.h"
int main() {
int start =  1 ;
int max;
int impossible =  0 ;
int done =  0 ;
printf("%s", "Escribe hasta que primo quieres probar: ");
scanf("%d", &max);printf("%s", "\n");
while ( start  <=  max ) {
impossible =  0 ;
done =  0 ;
printf("%d",(int)(start));
printf("%s", " ");
if ( start  ==  2  ||  start  ==  3 ) {
done =  1 ;
}
if ( done  ==  0 ) {
if ( !  (  start  <=  1  ||  start  %  2  ==  0  ||  start  %  3  ==  0  ) ) {
int j =  5 ;
while ( j  *  j  <  start ) {
if ( start  %  j  ==  0  ||  start  %  (  j  +  2  )  ==  0 ) {
impossible =  1 ;
}
j =  j  +  6 ;
}

} else {
impossible =  1 ;
}
}
if ( done  ==  1  ||  impossible  ==  1 ) {
printf("%s", "no ");
}
printf("%s", "es primo\n");
start =  start  +  1 ;
}
return 0;

}