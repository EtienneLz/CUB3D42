/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:00:47 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/04 18:01:31 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	check_collision(int direction, int axis)
{
	int	which_i;
	int	which_j;

	which_i = g_check_flags.pos_i / g_vars.size_case;
	which_j = g_check_flags.pos_j / g_vars.size_case;
	//printf("%d, %d\n", which_i, which_j);
	if (axis == 1)
	{
		which_i = (g_check_flags.pos_i + sin(g_check_flags.pos_a)) / g_vars.size_case;
		which_j = g_check_flags.pos_j + cos(g_check_flags.pos_a) / g_vars.size_case;
		printf("%d, %d\n", which_i, which_j);
		if (g_data.map[which_i][which_j] == '1')
			return (0);
	}
	if (axis == 2)
	{
		which_i = g_check_flags.pos_i / g_vars.size_case;
		which_j = (g_check_flags.pos_j + direction) / g_vars.size_case;
		printf("%d, %d\n", which_i, which_j);
		if (g_data.map[which_i][which_j] == '1')
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
		tmp_x = (g_check_flags.pos_j + (cos(g_check_flags.pos_a) * i));
		tmp_y = (g_check_flags.pos_i + (sin(g_check_flags.pos_a) * i));
		my_mlx_pixel_put(&g_data, tmp_x, tmp_y, 0x00FF0000);
		i++;
	}
}*/

void	move_player(int direction, int axis)
{
	if (direction == 0)
		return ;
	if (check_collision(direction, axis))
	{
		win_init();
		printf("%f, %f\n", g_check_flags.pos_i, g_check_flags.pos_j);
		if (axis == 1)
		{
			if (direction > 0)
				draw_player((g_check_flags.pos_i - (sin(g_check_flags.pos_a))), (g_check_flags.pos_j - (cos(g_check_flags.pos_a))));
			if (direction < 0)
				draw_player((g_check_flags.pos_i + (sin(g_check_flags.pos_a))), (g_check_flags.pos_j + (cos(g_check_flags.pos_a))));
		}
		if (axis == 2)
		{
			if (direction > 0)
				draw_player((g_check_flags.pos_i + (sin(g_check_flags.pos_a + M_PI / 2))), (g_check_flags.pos_j + (cos(g_check_flags.pos_a + M_PI / 2))));
			if (direction < 0)
				draw_player((g_check_flags.pos_i + (sin(g_check_flags.pos_a - M_PI / 2))), (g_check_flags.pos_j + (cos(g_check_flags.pos_a - M_PI / 2))));
		}
		//draw_line();
		raycasting();
		mlx_put_image_to_window(g_vars.mlx, g_vars.win, g_data.img, 0, 0);
	}
}

void	rotate_player(int direction)
{
	win_init();
	g_check_flags.pos_a += 2 * (M_PI / 180) * direction;
	//printf("%lf\n", g_check_flags.pos_a);
	//draw_line();
	//draw_player(g_check_flags.pos_i, g_check_flags.pos_j);
	raycasting();
	mlx_put_image_to_window(g_vars.mlx, g_vars.win, g_data.img, 0, 0);
}