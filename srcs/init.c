#include "../includes/cube.h"

static int             mouse_pos(int button, int x, int y)
{
    printf("%d, %d\n", x, y);
    return (0);
}

int             tamere_ft_exit()
{
    mlx_destroy_window(g_vars.mlx, g_vars.win);
    exit (0);
}

int             key_hook(int keycode)
{
    if (keycode == 65307)
        tamere_ft_exit();
    else
        printf("%d\n", keycode);
    return (0);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (0);
    ft_file_read(argv[1]);

    g_vars.mlx = mlx_init();

    //vars.win = mlx_new_window(vars.mlx, 1280, 1024, "CYBERPUNK 2077");
    //mlx_key_hook(vars.win, key_hook, &vars);

    /*mlx_hook(g_vars.win, 33, 1L << 17, ft_exit, &g_vars);
    mlx_mouse_hook(g_vars.win, mouse_pos, &g_vars);
    mlx_hook(g_vars.win, 2, 1L<<0, key_hook, &g_vars);
    mlx_loop(g_vars.mlx);
    win_init(g_vars.mlx);*/
    return (0);
}