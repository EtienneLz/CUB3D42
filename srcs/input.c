/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:58:54 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/05 16:37:53 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	key_pressed(t_data *data, int keycode)
{
	if (keycode == 65307)
		ft_exit();
	if (keycode == FORWARD)
		move_player(data, -2, 1);
	if (keycode == BACK)
		move_player(data, 2, 1);
	if (keycode == LEFT)
		move_player(data, -2, 2);
	if (keycode == RIGHT)
		move_player(data, 2, 2);
	if (keycode == ROTATE_LEFT)
		rotate_player(data, -2);
	if (keycode == ROTATE_RIGHT)
		rotate_player(data, 2);
	if (keycode == 555)
		raycasting(data);
	return (0);
}

static int	key_released(t_data *data, int keycode)
{
	if (keycode == FORWARD)
		move_player(data, 0, 0);
	if (keycode == BACK)
		move_player(data, 0, 0);
	if (keycode == LEFT)
		move_player(data, 0, 0);
	if (keycode == RIGHT)
		move_player(data, 0, 0);
	return (0);
}

void	input_loop(t_data *data)
{
	win_init(data);
	data->check_flags.init_done = 1;
	data->vars.win = mlx_new_window(data->vars.mlx, data->res_x, data->res_y, "tHe BIndInG oF iSaAC : ANTiBIrtH");
	mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->img, 0, 0);
	mlx_hook(data->vars.win, 33, 1L << 17, ft_exit, &data->vars);
	mlx_hook(data->vars.win, 2, 1L<<0, key_pressed, &data->vars);
	mlx_hook(data->vars.win, 3, 1L<<1, key_released, &data->vars);
	mlx_loop(data->vars.mlx);
}
