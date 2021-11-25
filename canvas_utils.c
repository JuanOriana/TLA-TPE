
#include "./include/canvas_utils.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

static void horizontal_bound(int width);
static void set_cmd_color(cv_color color);

void canvas_plot(canvas_t canvas)
{
    if (canvas.canvas_mat == NULL)
        return;

    set_cmd_color(canvas.color);
    horizontal_bound(canvas.width);
    for (int i = 0; i < canvas.height; i++)
    {
        printf("|");
        for (int j = 0; j < canvas.width; j++)
        {
            if (canvas.canvas_mat[i * canvas.width + j])
                printf("%c", canvas.canvas_mat[i * canvas.width + j]);
            else
                printf(" ");
        }
        printf("|\n");
    }
    horizontal_bound(canvas.width);
    set_cmd_color(CV_WHITE);
}

void cv_set_char_in_coords(canvas_t canvas, char c, int x, int y)
{
    if (canvas.canvas_mat == NULL || x < 0 || x >= canvas.width || y < 0 || y > canvas.height)
    {
        return;
    }
    canvas.canvas_mat[y * canvas.width + x] = c;
}

void cv_horizontal_line(canvas_t canvas, int left_bound, int right_bound, int y)
{
    if (canvas.canvas_mat == NULL)
    {
        return;
    }
    if (y < 0 || y >= canvas.height || right_bound < left_bound)
    {
        return;
    }
    int start = MAX(0, left_bound);
    int end = MIN(right_bound, canvas.width - 1);
    for (int i = start; i <= end; i++)
    {
        canvas.canvas_mat[y * canvas.width + i] = '-';
    }
}

// low -> mas cerca de la parte superior, high -> mas cerca de la inferior
void cv_vertical_line(canvas_t canvas, int low_bound, int high_bound, int x)
{
    if (canvas.canvas_mat == NULL)
    {
        return;
    }
    if (x < 0 || x >= canvas.width || high_bound < low_bound)
    {
        return;
    }
    int start = MAX(0, low_bound);
    int end = MIN(high_bound, canvas.height - 1);
    for (int i = start; i <= end; i++)
    {
        canvas.canvas_mat[i * canvas.width + x] = '|';
    }
}

void cv_set_color(canvas_t *canvas, int color)
{

    if (color >= CV_WHITE && color <= CV_BLUE)
        canvas->color = color;
}

static void horizontal_bound(int width)
{
    for (int i = 0; i < width + 2; i++)
    {
        putchar('-');
    }
    putchar('\n');
}

static void set_cmd_color(cv_color color)
{
    switch (color)
    {
    case CV_BLUE:
        printf("\033[0;34m");
        break;
    case CV_GREEN:
        printf("\033[0;32m");
        break;
    case CV_RED:
        printf("\033[0;31m");
        break;
    case CV_YELLOW:
        printf("\033[0;33m");
        break;
    case CV_WHITE:
    default:
        printf("\033[0m");
        break;
    }
}

void cv_fill_area(canvas_t canvas, char c, int x1, int y1, int x2, int y2)
{
    if (canvas.canvas_mat == NULL || x1 > x2 || y1 > y2)
    {
        return;
    }
    int startX = MAX(0, x1);
    int endX = MIN(canvas.width, x2);
    int startY = MAX(0, y1);
    int endY = MIN(canvas.height, y2);

    for (int j = startX; j <= endX; j++)
    {
        for (int i = startY; i <= endY; i++)
        {
            canvas.canvas_mat[i * canvas.width + j] = c;
        }
    }
}