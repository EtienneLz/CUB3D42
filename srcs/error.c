#include "../includes/cube.h"

void    ft_error(int code)
{
    if (code == 1)
    {
        close(g_data.fd);
        write(1, "Erreur de fichier config\n", 25);
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
        write(1, "Erreur de map\n", 14);
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
    ft_exit();
}

void ft_exit()
{
    return ;
}