#include "../includes/cube.h"

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
    g_check_flags.init_done = 0;
    g_check_flags.s_pos_i = 0;
    g_check_flags.s_pos_j = 0;
    g_check_flags.s_direction = 0;
}

static void    direction_init(void)
{
    if (g_check_flags.s_direction == 'N')
        g_check_flags.pos_a = M_PI / 2;
    if (g_check_flags.s_direction == 'S')
        g_check_flags.pos_a = 3 * M_PI / 2;
    if (g_check_flags.s_direction == 'E')
        g_check_flags.pos_a = 0;
    if (g_check_flags.s_direction == 'W')
        g_check_flags.pos_a = M_PI;
    g_ray_vars.column = g_data.res_x / 2;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (0);

    vars_init();
    ft_file_read(argv[1]);

    count_line();
    parse_map();
    close(g_data.fd);
    check_map();
    direction_init();
    g_vars.mlx = mlx_init();
    g_vars.size_case = 16;
    input_loop();
    
    return (0);
}