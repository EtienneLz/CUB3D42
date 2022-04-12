/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:58:26 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/05 16:22:42 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	vars_init_2(t_data *data)
{
	data->text_d.image[0].img = NULL;
	data->text_d.image[1].img = NULL;
	data->text_d.image[2].img = NULL;
	data->text_d.image[3].img = NULL;
	data->text_d.textures[0] = NULL;
	data->text_d.textures[1] = NULL;
	data->text_d.textures[2] = NULL;
	data->text_d.textures[3] = NULL;
	data->img = NULL;
	data->depth_buffer = NULL;
	data->vars.win = NULL;
	data->line = NULL;
	data->error = 0;
	data->skip = 0;
	data->res_x = 1000;
	data->res_y = 1000;
	data->player = 0;
}

static void	vars_init(t_data *data, char *argv)
{
	if (argv[ft_strlen(argv) - 1] != 'b'
		&& argv[ft_strlen(argv) - 2] != 'u'
		&& argv[ft_strlen(argv) - 3] != 'c'
		&& argv[ft_strlen(argv) - 4] != '.')
	{
		write (1, "Wrong type of file, must be .cub\n", 34);
		exit (0);
	}
	data->map = NULL;
	data->check.start_pos = 0;
	data->vars.size_line_max = 0;
	data->vars.size_map = 0;
	data->res_x = 0;
	data->res_y = 0;
	data->text_d.r = 0;
	data->text_d.g = 0;
	data->text_d.b = 0;
	data->text_d.floor_c = 0;
	data->text_d.sky_c = 0;
	data->check.init_done = 0;
	data->check.s_pos_i = 0;
	data->check.s_pos_j = 0;
	data->check.s_direction = 0;
	vars_init_2(data);
}

static void	direction_init(t_data *data)
{
	if (data->check.s_direction == 'N')
		data->check.pos_a = M_PI / 2;
	if (data->check.s_direction == 'S')
		data->check.pos_a = 3 * M_PI / 2;
	if (data->check.s_direction == 'E')
		data->check.pos_a = 0;
	if (data->check.s_direction == 'W')
		data->check.pos_a = M_PI;
}

void	raycasting(t_data *data)
{
	int		i;
	double	camera_x;
	double	ray[2];

	i = 0;
	while (i < data->res_x)
	{
		camera_x = 1.5 * i / data->res_x - 1;
		ray[0] = data->dir[0] + data->cam_plane[0] * camera_x;
		ray[1] = data->dir[1] + data->cam_plane[1] * camera_x;
		run_dda(data, i, ray);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		write (1, "Wrong number of arguments\n", 27);
		return (0);
	}
	vars_init(&data, argv[1]);
	data.vars.mlx = mlx_init();
	ft_file_read(&data, argv[1]);
	count_line(&data, argv[1]);
	parse_map(&data);
	close(data.fd);
	check_empty(&data);
	check_map(&data);
	direction_init(&data);
	texture_init(&data);
	cam_init(&data);
	input_loop(&data);
	return (0);
}
