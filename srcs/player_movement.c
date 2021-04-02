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
    g_check_flags.pos_a += direction;
    if (g_check_flags.pos_a == 360 && direction > 0)
        g_check_flags.pos_a = 0;
    if (g_check_flags.pos_a == -1 && direction < 0)
        g_check_flags.pos_a = 359;
    g_check_flags.fov_s = g_check_flags.pos_a - 30;
    g_check_flags.fov_e = g_check_flags.pos_a + 30;
    printf("%d\n", g_check_flags.pos_a);
}