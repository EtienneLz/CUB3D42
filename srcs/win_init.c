#include "../includes/cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*static void	draw_square(int i, int j)
{
	int     p;
	int     q;

	p = 0;
	while (p <= data->vars.size_case)
	{
		q = 0;
		while (q <= data->vars.size_case)
		{
			if (data->map[i][j] == '1')
				my_mlx_pixel_put(&data->data, data->vars.size_case * j + q, data->vars.size_case * i + p, 0x00999999);
			else if (data->map[i][j] == '0')
				my_mlx_pixel_put(&data->data, data->vars.size_case * j + q, data->vars.size_case * i + p, 0x00FFFFFF);
			else if (data->map[i][j] == ' ')
				my_mlx_pixel_put(&data->data, data->vars.size_case * j + q, data->vars.size_case * i + p, 0x00000000);
			else
				my_mlx_pixel_put(&data->data, data->vars.size_case * j + q, data->vars.size_case * i + p, 0x00FFFFFF);
			q++;
		}
		p++;
	}
}*/

void	draw_player(t_data *data, double d_i, double d_j)
{
	//int p;
	//int q;
	int	j;
	int	i;

	if (data->check_flags.init_done == 0)
	{
		j = (data->vars.size_case * data->check_flags.s_pos_j + data->vars.size_case / 2 - 4);
		i = (data->vars.size_case * data->check_flags.s_pos_i + data->vars.size_case / 2 - 4);
		data->check_flags.pos_i = i + 4;
		data->check_flags.pos_j = j + 4;
	}
	else
	{
		j = d_j - 4;
		i = d_i - 4;
		data->check_flags.pos_i = d_i;
		data->check_flags.pos_j = d_j;
	}
	printf("%f, %f bloup\n", d_i, d_j);
	/*p = 0;
	while (p <= 9)
	{
		q = 0;
		while (q <= 9)
		{
			my_mlx_pixel_put(&data->data, j + q, i + p, 0x00FF0000);
			q++;
		}
		p++;
	}*/
}

void	win_init(t_data *data)
{
	/*int i;
	int j;

	i = 0;*/
	data->img = mlx_new_image(data->vars.mlx, data->res_x, data->res_y);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	/*while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			draw_square(i, j);
			j++;
		}
		i++;
	}*/
	if (data->check_flags.init_done == 0)
	{
		data->check_flags.pos_i = data->vars.size_case * data->check_flags.s_pos_i + data->vars.size_case / 2 - 4;
		data->check_flags.pos_j = data->vars.size_case * data->check_flags.s_pos_j + data->vars.size_case / 2 - 4;
		//draw_player(data->check_flags.pos_i, data->check_flags.pos_j);
	}
}
