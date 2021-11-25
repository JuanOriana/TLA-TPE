
#include "./include/canvas_utils.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

static void horizontal_bound(int width);

void canvas_plot(canvas_t canvas)
{
    if (canvas.canvas_mat == NULL)
        return;
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
}

void set_char_in_coords(canvas_t canvas, char c, int x, int y)
{
    if (!(canvas.canvas_mat == NULL))
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

static void horizontal_bound(int width)
{
    for (int i = 0; i < width + 2; i++)
    {
        putchar('-');
    }
    putchar('\n');
}