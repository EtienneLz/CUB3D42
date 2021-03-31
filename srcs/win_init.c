#include "../includes/cube.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    win_init()
{
    void    *mlx_win;
    int     i;
    int     size_case;
    int     p;
    int     q;

    size_case = 800 / g_vars.size_line_max;
    i = 0;
    int j;

    mlx_win = mlx_new_window(g_vars.mlx, 800, 600, "tHe BIndInG oF iSaAC : ANTiBIrtH");
    g_data.img = mlx_new_image(g_vars.mlx, 800, 600);
    g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel, &g_data.line_length, &g_data.endian);

    while (g_data.map[i])
    {
        j = 0;
        while (g_data.map[i][j])
        {
            p = 0;
            while (p <= size_case)
            {
                q = 0;
                while (q <= size_case)
                {
                    if (g_data.map[i][j] == '1')
                        my_mlx_pixel_put(&g_data, size_case * j + q, size_case * i + p, 0x00999999);
                    else if (g_data.map[i][j] == '0')
                        my_mlx_pixel_put(&g_data, size_case * j + q, size_case * i + p, 0x00FFFFFF);
                    else
                        my_mlx_pixel_put(&g_data, size_case * j + q, size_case * i + p, 0x00FF2D00);
                    q++;
                }
                p++;
            }
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(g_vars.mlx, mlx_win, g_data.img, 0, 0);

    mlx_loop(g_vars.mlx);
}