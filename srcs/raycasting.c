#include "../includes/cube.h"

static double    ray_shot_horizontal(double p_pos_x, double p_pos_y, double angle)
{
    double x_step;
    double first_step_x;
    double first_step_y;

    first_step_y = 1 - p_pos_y;

}

static double    ray_shot_vertical(double p_pos_x, double p_pos_y, double angle)
{
    double y_step;
}

static double    ray_shot(double angle)
{
    double      length_x_inter;
    double      length_y_inter;
    double      p_pos_x;
    double      p_pos_y;

    p_pos_x = (g_check_flags.pos_j - g_vars.size_case * (g_check_flags.pos_j / g_vars.size_case)) / g_vars.size_case;
    p_pos_y = ((g_data.res_x - g_check_flags.pos_i) - g_vars.size_case * ((g_data.res_x - g_check_flags.pos_i)/ g_vars.size_case)) / g_vars.size_case;
    length_x_inter = ray_shot_horizontal(p_pos_x, p_pos_y, angle);
    length_y_inter = ray_shot_vertical(p_pos_x, p_pos_y, angle);

    if (length_x_inter <= length_y_inter)
        return(length_x_inter);
    else
        return(length_y_inter);
}

static void    draw_column(int ray_length, int which_ray)
{
    int col_height;
    int draw_start;
    int draw_end;
    int i;

    i = 1;
    //printf("bloul");
    col_height = g_data.res_y / ray_length * 2;
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

    which_ray =  0;
    ray_angle = g_check_flags.pos_a - (30 * M_PI / 180);
    while (which_ray < 2  * g_ray_vars.column)
    {
        ray_length = ray_shot(ray_angle);
        draw_column(ray_length, which_ray);
        which_ray++;
        ray_angle += (60 * M_PI / 180) / g_data.res_x;
    }
}