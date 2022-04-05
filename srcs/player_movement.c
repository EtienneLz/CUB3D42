/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:00:47 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/05 16:39:22 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	check_collision(t_data *data, int direction, int axis)
{
	int	which_i;
	int	which_j;

	which_i = data->check_flags.pos_i / data->vars.size_case;
	which_j = data->check_flags.pos_j / data->vars.size_case;
	if (axis == 1)
	{
		which_i = (data->check_flags.pos_i + sin(data->check_flags.pos_a))
			/ data->vars.size_case;
		which_j = data->check_flags.pos_j + cos(data->check_flags.pos_a)
			/ data->vars.size_case;
		printf("%d, %d\n", which_i, which_j);
		if (data->map[which_i][which_j] == '1')
			return (0);
	}
	if (axis == 2)
	{
		which_i = data->check_flags.pos_i / data->vars.size_case;
		which_j = (data->check_flags.pos_j + direction) / data->vars.size_case;
		printf("%d, %d\n", which_i, which_j);
		if (data->map[which_i][which_j] == '1')
			return (0);
	}
	return (1);
}

/*static void draw_line(void)
{
	int i;
	int tmp_x;
	int tmp_y;

	i = 0;
	while (i <= 20)
	{
		tmp_x = (data->check_flags.pos_j + (cos(data->check_flags.pos_a) * i));
		tmp_y = (data->check_flags.pos_i + (sin(data->check_flags.pos_a) * i));
		my_mlx_pixel_put(&data->data, tmp_x, tmp_y, 0x00FF0000);
		i++;
	}
}*/

void	move_player(t_data *data, int direction, int axis)
{
	if (direction == 0)
		return ;
	if (check_collision(data, direction, axis))
	{
		win_init(data);
		printf("%f, %f\n", data->check_flags.pos_i, data->check_flags.pos_j);
		if (axis == 1)
		{
			if (direction > 0)
				draw_player(data, (data->check_flags.pos_i - (sin(data->check_flags.pos_a))), (data->check_flags.pos_j - (cos(data->check_flags.pos_a))));
			if (direction < 0)
				draw_player(data, (data->check_flags.pos_i + (sin(data->check_flags.pos_a))), (data->check_flags.pos_j + (cos(data->check_flags.pos_a))));
		}
		if (axis == 2)
		{
			if (direction > 0)
				draw_player(data, (data->check_flags.pos_i + (sin(data->check_flags.pos_a + M_PI / 2))), (data->check_flags.pos_j + (cos(data->check_flags.pos_a + M_PI / 2))));
			if (direction < 0)
				draw_player(data, (data->check_flags.pos_i + (sin(data->check_flags.pos_a - M_PI / 2))), (data->check_flags.pos_j + (cos(data->check_flags.pos_a - M_PI / 2))));
		}
		raycasting(data);
		mlx_put_image_to_window(data->vars.mlx,
			data->vars.win, data->img, 0, 0);
	}
}

void	rotate_player(t_data *data, int direction)
{
	win_init(data);
	data->check_flags.pos_a += 2 * (M_PI / 180) * direction;
	raycasting(data);
	mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->img, 0, 0);
}
