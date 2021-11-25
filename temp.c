#include <stdio.h>
#include "./include/canvas_utils.h"
int main() {
canvas_t cv = {.canvas_mat=malloc(10*10), .width=10, .height=10, .color=CV_WHITE};
canvas_t cv2 = {.canvas_mat=malloc(10*10), .width=10, .height=10, .color=CV_WHITE};
canvas_t cv3 = {.canvas_mat=malloc(10*10), .width=10, .height=10, .color=CV_WHITE};
canvas_t cv4 = {.canvas_mat=malloc(10*10), .width=10, .height=10, .color=CV_WHITE};
canvas_t cv5 = {.canvas_mat=malloc(10*10), .width=10, .height=10, .color=CV_WHITE};
cv_set_color(&cv, 4 );
int n =  0 ;
while ( n  <  10 ) {
set_char_in_coords(cv,'*', n , n );
n =  n  +  1 ;
}
canvas_plot(cv);free(cv5.canvas_mat);
free(cv4.canvas_mat);
free(cv3.canvas_mat);
free(cv2.canvas_mat);
free(cv.canvas_mat);
return 0;

}