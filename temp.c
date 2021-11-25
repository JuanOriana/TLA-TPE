#include <stdio.h>
#include "./include/canvas_utils.h"
int main() {
char * hola = "hola";
canvas_t cv = {.canvas_mat=malloc(20*10), .width=20, .height=10, .color=CV_WHITE};
int i =  0 ;
cv_fill_area(cv,'/', 2 , 2 , 5 , 5 );
while ( 3  +  2  /  2 ) {
cv_set_char_in_coords(cv,'*', i , i );
i =  i  +  1 ;
}
cv_set_color(&cv, 4 );
canvas_plot(cv);
free(cv.canvas_mat);
return 0;

}