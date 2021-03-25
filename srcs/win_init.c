#include "../includes/cube.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    win_init(void *mlx)
{
    void    *mlx_win;
    int     x;
    int     y;
    int     r;
    int     L;
    int     l;

    x = 0;
    y = 0;
    L = 1024;
    l = 800;
    r = l / 5;  

   // mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, L, l, "tHe BIndInG oF iSaAC : ANTiBIrtH");
    g_data.img = mlx_new_image(mlx, L, l);
    g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel, &g_data.line_length, &g_data.endian);

    while (x < L)
    {
        while (y < l)
        {
            if (((x - L / 2) * (x - L / 2) + (y - l / 2) * (y - l / 2)) < r * r)
                my_mlx_pixel_put(&g_data, x, y, 0x00FF0000);
            else
            my_mlx_pixel_put(&g_data, x, y, 0x00FFFFFF);
            y++;
        }
        y = 0;
        x++;
    }

    mlx_put_image_to_window(mlx, mlx_win, g_data.img, 0, 0);

    mlx_loop(mlx);
}