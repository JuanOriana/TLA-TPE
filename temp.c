#include <stdio.h>
#include "./include/canvas_utils.h"
int main() {
canvas_t cv = {.canvas_mat=malloc(10*10), .width=10, .height=10, .color=CV_WHITE};
cv_set_color(&cv, 4 );
int n =  0 ;
while ( n  <  10 ) {
set_char_in_coords(cv,'*', n , n );
n =  n  +  1 ;
}
canvas_plot(cv);return 0;

}