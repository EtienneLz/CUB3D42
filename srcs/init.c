#include "../includes/cube.h"

/*static int             mouse_pos(int button, int x, int y)
{
    button = button;
    printf("%d, %d\n", x, y);
    return (0);
}*/



int             tamere_ft_exit()
{
    mlx_destroy_window(g_vars.mlx, g_vars.win);
    exit (0);
}

static void    vars_init(void)
{
    g_data.map = NULL;
    g_check_flags.start_pos = 0;
    g_vars.size_line_max = 0;
    g_data.res_x = 0;
    g_data.res_y = 0;
    g_textures_data.north_t = NULL;
    g_textures_data.south_t = NULL;
    g_textures_data.west_t = NULL;
    g_textures_data.east_t = NULL;
    g_textures_data.sprite_t = NULL;
    g_textures_data.r = 0;
    g_textures_data.g = 0;
    g_textures_data.b = 0;
    g_textures_data.floor_c = 0;
    g_textures_data.sky_c = 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (0);
    //printf("yo");
    vars_init();
    ft_file_read(argv[1]);

    //printf("yo");
    count_line();
    parse_map();
    close(g_data.fd);
    /*int i = 0;
    int j = 0;
    while (g_data.map[i])
    {
        while (g_data.map[i][j])
        {
            printf("%c", g_data.map[i][j]);
            j++;
        }
        printf("\n");
        j = 0;
        i++;
    }*/
    check_map();
    g_vars.mlx = mlx_init();
    
    input_loop();
    //vars.win = mlx_new_window(vars.mlx, 1280, 1024, "CYBERPUNK 2077");
    //mlx_key_hook(vars.win, key_hook, &vars);

    /*mlx_hook(g_vars.win, 33, 1L << 17, ft_exit, &g_vars);
    mlx_mouse_hook(g_vars.win, mouse_pos, &g_vars);
    mlx_hook(g_vars.win, 2, 1L<<0, key_hook, &g_vars);
    mlx_loop(g_vars.mlx);*/
    
    return (0);
}