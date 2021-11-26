#include <stdio.h>
#include "./include/canvas_utils.h"
int main() {
char * order = "todo en orden";
double one = (double) 0.1 ;
canvas_t cv = {.canvas_mat=malloc(10*10), .width=10, .height=10, .color=CV_WHITE};
cv_set_char_in_coords(cv,'*', one , 3 );
canvas_plot(cv);
free(cv.canvas_mat);
return 0;

}