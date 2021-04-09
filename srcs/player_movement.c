#include "../includes/cube.h"

static  int    check_collision(int direction, int axis)
{
    int     which_i;
    int     which_j;

    which_i = g_check_flags.pos_i / g_vars.size_case;
    which_j = g_check_flags.pos_j / g_vars.size_case;
    //printf("%d, %d\n", which_i, which_j);
    if (axis == 1)
    {
        which_i = (g_check_flags.pos_i + direction) / g_vars.size_case;
        which_j = g_check_flags.pos_j / g_vars.size_case;
        printf("%d, %d\n", which_i, which_j);
        if (g_data.map[which_i][which_j] == '1')
            return (0);
    }
    if (axis == 2)
    {
        which_i = g_check_flags.pos_i / g_vars.size_case;
        which_j = (g_check_flags.pos_j + direction) / g_vars.size_case;
        printf("%d, %d\n", which_i, which_j);
        if (g_data.map[which_i][which_j] == '1')
            return (0);
    }
    return (1);
}

void            move_player(int direction, int axis)
{
    if (direction == 0)
            return ;
    
    if (check_collision(direction, axis))
    {
        win_init();
        if (axis == 1)
        {
            if (direction > 0)
                draw_player(g_check_flags.s_pos_i, g_check_flags.s_pos_j, direction, 0);
            if (direction < 0)
                draw_player(g_check_flags.s_pos_i, g_check_flags.s_pos_j, direction, 0);
        }
        if (axis == 2)
        {
            if (direction > 0)
                draw_player(g_check_flags.s_pos_i, g_check_flags.s_pos_j, 0, direction);
            if (direction < 0)
                draw_player(g_check_flags.s_pos_i, g_check_flags.s_pos_j, 0, direction);
        }         
        mlx_put_image_to_window(g_vars.mlx, g_vars.win, g_data.img, 0, 0);
    }
}

void        rotate_player(int direction)
{
    int i;

    i = 0;
    win_init();
    g_check_flags.pos_a += 2 * (M_PI / 180) * direction;
    while (i <= 20)
    {
        mlx_pixel_put(g_vars.mlx, g_vars.win, (int)(g_check_flags.pos_j + (cos(g_check_flags.pos_a) * i)), (int)(g_check_flags.pos_i + (sin(g_check_flags.pos_a) * i)), 0x00FF0000);
        i++;
    }
    //draw_player(g_check_flags.s_pos_i, g_check_flags.s_pos_j, 0, 0);
    mlx_put_image_to_window(g_vars.mlx, g_vars.win, g_data.img, 0, 0);
    printf("%d, %d\n", g_check_flags.pos_i, g_check_flags.pos_j);
    printf("%f\n", g_check_flags.pos_a);
    printf("%d\n", (int)(g_check_flags.pos_j + (cos(g_check_flags.pos_a) * 10)));
}