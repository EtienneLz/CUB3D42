/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:19:18 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/05 16:44:04 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	ray_facing(double angle)
{
	double	m_angle;

	m_angle = angle % M_PI;
	if (m_angle < 0.5 * M_PI || m_angle > 1.5 * M_PI)
		return (0);
	if (m_angle < 0 && m_angle > M_PI)
		return (1);
	if (m_angle > 0.5 * M_PI || m_angle < 1.5 * M_PI)
		return (2);
	else
		return (3);
}

static double	ray_shot_horizontal(t_data *data, double p_pos_x, double p_pos_y, double angle)
{
	double	inter_x;
	double	inter_y;
	double	step_x;
	double	step_y;

	inter_y = floor(p_pos_y / data->vars.size_case) * data->vars.size_case;
	if (ray_facing(angle) == 3)
		inter_y += data->vars.size_case;
	inter_x = p_pos_x + (inter_y - p_pos_y) / tan(angle);
	step_y = data->vars.size_case;
	if (ray_facing(angle) == 1)
		step_y *= -1;
	step_x = data->vars.size_case / tan(angle);
	if (ray_facing(angle) == 2 && step_x > 0)
		step_x *= -1;
	if (ray_facing(angle) == 0 && step_x < 0)
		step_x *= -1;
}

static double	ray_shot_vertical(t_data *data, double p_pos_x, double p_pos_y, double angle)
{
	double	y_step;
}

static double	ray_shot(t_data *data, double angle)
{
	double	length_x_inter;
	double	length_y_inter;
	double	p_pos_x;
	double	p_pos_y;

	p_pos_x = (data->check_flags.pos_j - data->vars.size_case * (data->check_flags.pos_j / data->vars.size_case)) / data->vars.size_case;
	p_pos_y = ((data->res_x - data->check_flags.pos_i) - data->vars.size_case * ((data->res_x - data->check_flags.pos_i) / data->vars.size_case)) / data->vars.size_case;
	length_x_inter = ray_shot_horizontal(data, p_pos_x, p_pos_y, angle);
	length_y_inter = ray_shot_vertical(data, p_pos_x, p_pos_y, angle);
	if (length_x_inter <= length_y_inter)
		return (length_x_inter);
	else
		return (length_y_inter);
}

static void	draw_column(t_data *data, int ray_length, int which_ray)
{
	int	col_height;
	int	draw_start;
	int	draw_end;
	int	i;

	i = 1;
	col_height = data->res_y / ray_length * 2;
	draw_start = -col_height / 2 + data->res_y / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = col_height / 2 + data->res_y / 2;
	if (draw_end >= data->res_y)
		draw_end = data->res_y - 1;
	while (i < data->res_y)
	{
		if (i < draw_start || i > draw_end)
			my_mlx_pixel_put(data, which_ray, i, 0x00000000);
		if (i >= draw_start && i <= draw_end)
			my_mlx_pixel_put(data, which_ray, i, 0x0000FF00);
		i++;
	}
}

void	raycasting(t_data *data)
{
	int		which_ray;
	int		ray_length;
	double	ray_angle;

	which_ray = 0;
	ray_angle = data->check_flags.pos_a - (30 * M_PI / 180);
	while (which_ray < 2 * data->ray_vars.column)
	{
		ray_length = ray_shot(data, ray_angle);
		draw_column(data, ray_length, which_ray);
		which_ray++;
		ray_angle += (60 * M_PI / 180) / data->res_x;
	}
}
