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
	data->res_x = 0;
	data->res_y = 0;
	data->textures_data.north_t = NULL;
	data->textures_data.south_t = NULL;
	data->textures_data.west_t = NULL;
	data->textures_data.east_t = NULL;
	data->textures_data.sprite_t = NULL;
	data->textures_data.r = 0;
	data->textures_data.g = 0;
	data->textures_data.b = 0;
	data->textures_data.floor_c = 0;
	data->textures_data.sky_c = 0;
	data->check_flags.init_done = 0;
	data->check_flags.s_pos_i = 0;
	data->check_flags.s_pos_j = 0;
	data->check_flags.s_direction = 0;
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
	data->ray_vars.column = data->res_x / 2;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (0);
	vars_init(&data);
	ft_file_read(&data, argv[1]);
	count_line(&data);
	parse_map(&data);
	close(data.fd);
	check_map(&data);
	direction_init(&data);
	data.vars.mlx = mlx_init();
	data.vars.size_case = 16;
	input_loop(&data);
	return (0);
}
