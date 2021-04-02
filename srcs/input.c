#include "../includes/cube.h"



static int     key_pressed(int keycode)
{
    if (keycode == 65307)
        ft_exit();
    if (keycode == FORWARD)
        move_player(-1, 1);
    if (keycode == BACK)
        move_player(1, 1);
    if (keycode == LEFT)
        move_player(-1, 2);
    if (keycode == RIGHT)
        move_player(1, 2);
    if (keycode == ROTATE_LEFT)
        rotate_player(-1);
    if (keycode == ROTATE_RIGHT)
        rotate_player(1);
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
    win_init(g_vars.mlx);
    g_check_flags.init_done = 1;
    g_vars.win = mlx_new_window(g_vars.mlx, 800, 600, "tHe BIndInG oF iSaAC : ANTiBIrtH");
    mlx_put_image_to_window(g_vars.mlx, g_vars.win, g_data.img, 0, 0);
    mlx_hook(g_vars.win, 33, 1L << 17, ft_exit, &g_vars);
    mlx_hook(g_vars.win, 2, 1L<<0, key_pressed, &g_vars);
    mlx_hook(g_vars.win, 3, 1L<<1, key_released, &g_vars);
    mlx_loop(g_vars.mlx);
}