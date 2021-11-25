#ifndef _CANVAS_UTILS_H
#define _CANVAS_UTILS_H
#include <stdlib.h>
#include <stdio.h>

typedef enum cv_color
{
    CV_WHITE,
    CV_RED,
    CV_YELLOW,
    CV_GREEN,
    CV_BLUE
} cv_color;

typedef struct canvas_t
{
    char *canvas_mat;
    int width;
    int height;
    cv_color color;
} canvas_t;

void canvas_plot(canvas_t canvas);
void set_char_in_coords(canvas_t canvas, char c, int x, int y);
void cv_horizontal_line(canvas_t canvas, int left_bound, int right_bound, int y);
void cv_vertical_line(canvas_t canvas, int low_bound, int high_bound, int x);
void cv_set_color(canvas_t *canvas, int color);

#endif