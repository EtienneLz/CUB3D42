#include "../includes/cube.h"

void    ft_error(int code)
{
    write(1, "Erreur \n", 8);
    if (code == 1)
    {
        close(g_data.fd);
        write(1, "Configuration invalide\n", 23);
        ft_free();
    }
    if (code == 2)
    {
        close(g_data.fd);
        write(1, "Ta mere\n", 25);
        ft_free();
    }
    if (code == 3)
    {
        close(g_data.fd);
        write(1, "Map invalide\n", 14);
        ft_free();
    }
}

void ft_free(void)
{
    if (g_textures_data.north_t)
        free(g_textures_data.north_t);
    if (g_textures_data.south_t)
        free(g_textures_data.south_t);
    if (g_textures_data.west_t)
        free(g_textures_data.west_t);
    if (g_textures_data.east_t)
        free(g_textures_data.east_t);
    if (g_textures_data.sprite_t)
        free(g_textures_data.sprite_t);
    if (g_data.map)
        free(g_data.map);
    ft_exit();
}

int ft_exit()
{
    exit(EXIT_SUCCESS);
}