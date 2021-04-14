#include "../includes/cube.h"

static int    ray_shot(double angle)
{
    int     which_i;
    int     which_j;
    int     ray_length;

    ray_length = 1;
    which_i = g_check_flags.pos_i / g_vars.size_case;
    which_j = g_check_flags.pos_j / g_vars.size_case;
    while (g_data.map[which_i][which_j] != '1')
    {
        ray_length++;
        which_i = (g_check_flags.pos_i + sin(angle) * ray_length) / g_vars.size_case;
        which_j = (g_check_flags.pos_j + cos(angle) * ray_length) / g_vars.size_case;
    }
    return (ray_length);
}

static void    draw_column(int ray_length, int which_ray)
{
    int col_height;
    int draw_start;
    int draw_end;
    int i;

    i = 0;
    printf("bloul");
    col_height = g_data.res_y / ray_length;
    if ((draw_start = -col_height / 2 + g_data.res_y / 2) < 0)
        draw_start = 0;
    if ((draw_end = col_height / 2 + g_data.res_y / 2) >= g_data.res_y)
        draw_end = g_data.res_y - 1;
    while (i < g_data.res_y)
    {
        if (i < draw_start || i > draw_end)
            my_mlx_pixel_put(&g_data, which_ray, i, 0x00000000);
        if (i >= draw_start && i <= draw_end)
            my_mlx_pixel_put(&g_data, which_ray, i, 0x0000FF00);
        i++;
    }
}

void    raycasting(void)
{
    int which_ray;
    int ray_length;
    double ray_angle;

    which_ray = -g_ray_vars.column;
    ray_angle = g_check_flags.pos_a - (30 * M_PI / 180);
    while (which_ray < g_ray_vars.column)
    {
        ray_length = ray_shot(ray_angle);
        draw_column(ray_length, which_ray);
        which_ray++;
        ray_angle += (60 * M_PI / 180) / g_data.res_x;
    }
}