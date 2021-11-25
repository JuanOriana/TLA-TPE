#include <stdio.h>
#include "./include/canvas_utils.h"
int main() {
int n1 =  1 ;
int n2 =  1 ;
canvas_t cv = {.canvas_mat=malloc(30*10), .width=30, .height=10};
int i =  0 ;
set_char_in_coords(cv,'x', 10 , 3 );set_char_in_coords(cv,'x', 20 , 3 );while ( i  <  30 ) {
cv_horizontal_line(cv, 0 , 30 , i );cv_vertical_line(cv, 0 , 18 , i );i =  i  +  3 ;
}
canvas_plot(cv);return 0;

}