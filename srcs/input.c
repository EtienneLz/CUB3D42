#include "../includes/cube.h"

static int     key_pressed(int keycode)
{
    if (keycode == 65307)
        tamere_ft_exit();
    else
        printf("%d\n", keycode);
    return (0);
}


void            input_loop(void)
{
    win_init(g_vars.mlx);
    mlx_hook(g_vars.win, 33, 1L << 17, ft_exit, &g_vars);
    mlx_hook(g_vars.win, 2, 1L<<0, key_pressed, &g_vars);
    mlx_loop(g_vars.mlx);
}