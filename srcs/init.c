#include "../includes/cube.h"

int     create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16| g << 8 | b);
}

int     get_t(int trgb)
{
    return (trgb & (0xFF << 24));
}

int     get_r(int trgb)
{
    return (trgb & (0xFF << 16));
}

int     get_g(int trgb)
{
    return (trgb & (0xFF << 8));
}

int     get_b(int trgb)
{
    return (trgb & 0xFF);
}

static int             mouse_pos(int button, int x, int y)
{
    printf("%d, %d\n", x, y);
    return (0);
}

int             ft_exit()
{
    mlx_destroy_window(g_vars.mlx, g_vars.win);
    exit (0);
}

int             key_hook(int keycode)
{
    if (keycode == 65307)
        ft_exit(g_vars);
    else
        printf("%d\n", keycode);
    return (0);
}

int main(int argc, char *argv)
{
    if (argc != 2)
        return (0);
    file_read(argv[1]);

    g_vars.mlx = mlx_init();

    //vars.win = mlx_new_window(vars.mlx, 1280, 1024, "CYBERPUNK 2077");
    //mlx_key_hook(vars.win, key_hook, &vars);

    mlx_hook(g_vars.win, 33, 1L << 17, ft_exit, &g_vars);
    mlx_mouse_hook(g_vars.win, mouse_pos, &g_vars);
    mlx_hook(g_vars.win, 2, 1L<<0, key_hook, &g_vars);
    mlx_loop(g_vars.mlx);
    win_init(g_vars.mlx);
}