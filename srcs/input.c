#include "../includes/cube.h"



static int     key_pressed(int keycode)
{
    if (keycode == 65307)
        ft_exit();
    if (keycode == FORWARD)
        move_player(-2, 1);
    if (keycode == BACK)
        move_player(2, 1);
    if (keycode == LEFT)
        move_player(-2, 2);
    if (keycode == RIGHT)
        move_player(2, 2);
    if (keycode == ROTATE_LEFT)
        rotate_player(-2);
    if (keycode == ROTATE_RIGHT)
        rotate_player(2);
    if (keycode == 555)
        raycasting();
    return (0);
}

static int     key_released(int keycode)
{
    if (keycode == FORWARD)
        move_player(0, 0);
    if (keycode == BACK)
        move_player(0, 0);
    if (keycode == LEFT)
        move_player(0, 0);
    if (keycode == RIGHT)
        move_player(0, 0);
    return (0);
}


void            input_loop(void)
{  
    win_init();
    g_check_flags.init_done = 1;
    g_vars.win = mlx_new_window(g_vars.mlx, g_data.res_x, g_data.res_y, "tHe BIndInG oF iSaAC : ANTiBIrtH");
    mlx_put_image_to_window(g_vars.mlx, g_vars.win, g_data.img, 0, 0);
    mlx_hook(g_vars.win, 33, 1L << 17, ft_exit, &g_vars);
    mlx_hook(g_vars.win, 2, 1L<<0, key_pressed, &g_vars);
    mlx_hook(g_vars.win, 3, 1L<<1, key_released, &g_vars);
    mlx_loop(g_vars.mlx);
}