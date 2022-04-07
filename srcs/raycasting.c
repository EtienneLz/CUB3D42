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

	m_angle = fmod(angle, (2 * M_PI));
	if (m_angle < 0.5 * M_PI || m_angle > 1.5 * M_PI)
		return (0);
	if (m_angle < 0 && m_angle > M_PI)
		return (1);
	if (m_angle > 0.5 * M_PI || m_angle < 1.5 * M_PI)
		return (2);
	else
		return (3);
}

double	distanceBetweenPoints(double x1, double y1, double x2, double y2) 
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

static void	ray_shot_horizontal(t_data *data, double p_pos_x, double p_pos_y, double angle)
{
	double	inter_x;
	double	inter_y;
	double	step_x;
	double	step_y;
	double	next_hor_x;
	double	next_hor_y;
	double	next_ver_x;
	double	next_ver_y;

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
	next_hor_x = inter_x;
	next_hor_y = inter_y;
	if (ray_facing(angle) == 1)
		inter_y -= 1;
	while (next_hor_x >= 0 && next_hor_x <= data->res_x && next_hor_y >= 0 && next_hor_y <= data->res_y)
	{
		if (data->map[(int)inter_x][(int)inter_y] == '1')
		{
			data->ray_vars.wall_hit_hor = 1;
			data->ray_vars.hor_wall_hitX = (int)next_hor_x;
			data->ray_vars.hor_wall_hitY = (int)next_hor_y;
			break ;
		}
		else
		{
			next_hor_x += step_x;
			next_hor_y += step_y;
		}
	}
	inter_y = floor(p_pos_x / data->vars.size_case) * data->vars.size_case;
	if (ray_facing(angle) == 3)
		inter_x += data->vars.size_case;
	inter_y = p_pos_y + (inter_x - p_pos_x) * tan(angle);
	step_x = data->vars.size_case;
	if (ray_facing(angle) == 0)
		step_x *= -1;
	step_y = data->vars.size_case * tan(angle);
	if (ray_facing(angle) == 1 && step_y > 0)
		step_y *= -1;
	if (ray_facing(angle) == 2 && step_y < 0)
		step_y *= -1;
	next_ver_x = inter_x;
	next_ver_y = inter_y;
	if (ray_facing(angle) == 0)
		next_ver_x -= 1;
	while (next_ver_x >= 0 && next_ver_x <= data->res_x && next_ver_y >= 0 && next_ver_y <= data->res_y)
	{
		if (data->map[(int)next_ver_x][(int)next_ver_y] == '1')
		{
			data->ray_vars.wall_hit_ver = 1;
			data->ray_vars.ver_wall_hitX = (int)next_ver_x;
			data->ray_vars.ver_wall_hitY = (int)next_ver_y;
			break ;
		}
		else
		{
			next_ver_x += step_x;
			next_ver_y += step_y;
		}
	}
	data->ray_vars.Xdistance = LDBL_MAX;
	data->ray_vars.Ydistance = LDBL_MAX;
	if (data->ray_vars.wall_hit_hor)
		data->ray_vars.Xdistance = distanceBetweenPoints(p_pos_x, p_pos_y, data->ray_vars.hor_wall_hitX, data->ray_vars.hor_wall_hitY);
	if (data->ray_vars.wall_hit_ver)
		data->ray_vars.Ydistance = distanceBetweenPoints(p_pos_x, p_pos_y, data->ray_vars.ver_wall_hitX, data->ray_vars.ver_wall_hitY);
}

static double	ray_shot(t_data *data, double angle)
{
	double	p_pos_x;
	double	p_pos_y;

	p_pos_x = (data->check_flags.pos_j - data->vars.size_case * (data->check_flags.pos_j / data->vars.size_case)) / data->vars.size_case;
	p_pos_y = ((data->res_x - data->check_flags.pos_i) - data->vars.size_case * ((data->res_x - data->check_flags.pos_i) / data->vars.size_case)) / data->vars.size_case;
	ray_shot_horizontal(data, p_pos_x, p_pos_y, angle);
	if (data->ray_vars.Xdistance <= data->ray_vars.Ydistance)
		return (data->ray_vars.Xdistance);
	else
		return (data->ray_vars.Ydistance);
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
		data->ray_vars.wall_hit_hor = 0;
		data->ray_vars.wall_hit_ver = 0;
		data->ray_vars.hor_wall_hitX = 0;
		data->ray_vars.hor_wall_hitY = 0;
		data->ray_vars.ver_wall_hitX = 0;
		data->ray_vars.ver_wall_hitY = 0;
		ray_length = ray_shot(data, ray_angle);
		draw_column(data, ray_length, which_ray);
		which_ray++;
		ray_angle += (60 * M_PI / 180) / data->res_x;
	}
}
