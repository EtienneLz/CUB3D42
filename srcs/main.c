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

static void	vars_init(t_data *data)
{
	data->map = NULL;
	data->check_flags.start_pos = 0;
	data->vars.size_line_max = 0;
	data->vars.size_map = 0;
	data->res_x = 0;
	data->res_y = 0;
	data->textures_data.r = 0;
	data->textures_data.g = 0;
	data->textures_data.b = 0;
	data->textures_data.floor_c = 0;
	data->textures_data.sky_c = 0;
	data->check_flags.init_done = 0;
	data->check_flags.s_pos_i = 0;
	data->check_flags.s_pos_j = 0;
	data->check_flags.s_direction = 0;
	data->textures_data.image[0].img = NULL;
	data->textures_data.image[1].img = NULL;
	data->textures_data.image[2].img = NULL;
	data->textures_data.image[3].img = NULL;
	data->textures_data.textures[0] = NULL;
	data->textures_data.textures[1] = NULL;
	data->textures_data.textures[2] = NULL;
	data->textures_data.textures[3] = NULL;
	data->img = NULL;
	data->depth_buffer = NULL;
	data->vars.win = NULL;
	data->line = NULL;
	data->error = 0;
}

static void	direction_init(t_data *data)
{
	if (data->check_flags.s_direction == 'N')
		data->check_flags.pos_a = M_PI / 2;
	if (data->check_flags.s_direction == 'S')
		data->check_flags.pos_a = 3 * M_PI / 2;
	if (data->check_flags.s_direction == 'E')
		data->check_flags.pos_a = 0;
	if (data->check_flags.s_direction == 'W')
		data->check_flags.pos_a = M_PI;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		write (1, "Wrong number of arguments\n", 27);
		return (0);
	}
	if (argv[1][ft_strlen(argv[1]) - 1] != 'b' && argv[1][ft_strlen(argv[1]) - 2] != 'u' && argv[1][ft_strlen(argv[1]) - 3] != 'c' && argv[1][ft_strlen(argv[1]) - 4] != '.')
	{
		write (1, "Wrong type of file, must be .cub\n", 34);
		return (0);
	}
	vars_init(&data);
	data.vars.mlx = mlx_init();
	ft_file_read(&data, argv[1]);
	count_line(&data);
	parse_map(&data);
	close(data.fd);
	check_map(&data);
	direction_init(&data);
	texture_init(&data);
	cam_init(&data);
	input_loop(&data);
	return (0);
}
