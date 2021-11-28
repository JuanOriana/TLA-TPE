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

// Plotear canvas
void canvas_plot(canvas_t canvas);
// Pone char en (x,y)
void cv_set_char_in_coords(canvas_t canvas, char c, int x, int y);
// Pone linea horizontal
void cv_horizontal_line(canvas_t canvas, int left_bound, int right_bound, int y);
// Pone linea vertical
void cv_vertical_line(canvas_t canvas, int low_bound, int high_bound, int x);
// Cambia color al ploteo
void cv_set_color(canvas_t *canvas, int color);
// Llena area del canvas con char
void cv_fill_area(canvas_t canvas, char c, int x1, int y1, int x2, int y2);

#endif