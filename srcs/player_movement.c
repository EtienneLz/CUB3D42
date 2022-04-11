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

static void	move_player_3(t_data *data, double d_i, double d_j)
{
	if (data->map[(int)(data->check.pos_i + d_i)]
		[(int)(data->check.pos_j + d_j)] != '1')
	{
		data->check.pos_i += d_i;
		data->check.pos_j += d_j;
	}
}

static void	move_player_2(t_data *data, double *d_i, double *d_j, int direction)
{
	if (direction > 0)
	{
		*d_i = data->cam_plane[0] * SPEED;
		*d_j = data->cam_plane[1] * SPEED;
	}
	if (direction < 0)
	{
		*d_i = data->cam_plane[0] * -SPEED;
		*d_j = data->cam_plane[1] * -SPEED;
	}
}

void	move_player(t_data *data, int direction, int axis)
{
	double	d_i;
	double	d_j;

	if (direction == 0)
		return ;
	if (axis == 1)
	{
		if (direction > 0)
		{
			d_i = data->dir[0] * -SPEED;
			d_j = data->dir[1] * -SPEED;
		}
		if (direction < 0)
		{
			d_i = data->dir[0] * SPEED;
			d_j = data->dir[1] * SPEED;
		}
	}
	if (axis == 2)
		move_player_2(data, &d_i, &d_j, direction);
	move_player_3(data, d_i, d_j);
}

void	rotate_player(t_data *data, int direction)
{
	double	tmp;
	double	pos_a;

	pos_a = (M_PI / 100) * direction;
	tmp = data->dir[0];
	data->dir[0] = tmp * cos(pos_a) - data->dir[1] * sin(pos_a);
	data->dir[1] = tmp * sin(pos_a) + data->dir[1] * cos(pos_a);
	tmp = data->cam_plane[0];
	data->cam_plane[0] = tmp * cos(pos_a) - data->cam_plane[1] * sin(pos_a);
	data->cam_plane[1] = tmp * sin(pos_a) + data->cam_plane[1] * cos(pos_a);
}
