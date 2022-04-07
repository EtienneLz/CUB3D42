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
		return (0); //E
	if (m_angle < 0 && m_angle > M_PI)
		return (1); //N
	if (m_angle > 0.5 * M_PI || m_angle < 1.5 * M_PI)
		return (2); //W
	else
		return (3); //S
}

static void	draw_line_textured(t_data *data, int i)
{
	int		j;
	int		start;
	int		end;
	t_img	texture;
	int		color;

	start = data->res_y / 2 - data->textures_data.line_height / 2;
	end = data->res_y / 2 + data.line_height / 2;
	texture = world->textures[data.side];
	j = 0;
	while (j < (start < 0 ? 0 : start))
		set_screen_pixel(world->screen, i, j++, world->color_ceiling);
	while (j < (end >= world->scr_height ? world->scr_height - 1 : end))
	{
		color = get_tex_color(texture, data.wall_x,
			((j - start) * 1.0) / (end - start));
		set_screen_pixel(world->screen, i, j++, color);
	}
	while (j < world->scr_height)
		set_screen_pixel(world->screen, i, j++, world->color_floor);
}

static void	init_vars(t_data *data, double ray[2])
{
	data->ray_vars.delta_dist[0] = fabs(1.0 / ray[0]);
	data->ray_vars.delta_dist[1] = fabs(1.0 / ray[1]);
	data->ray_vars.map_pos[0] = floor(data->check_flags.pos_i);
	data->ray_vars.map_pos[1] = floor(data->check_flags.pos_j);
	data->ray_vars.step[0] = (ray[0] < 0) ? -1 : 1;
	data->ray_vars.step[1] = (ray[1] < 0) ? -1 : 1;
	data->ray_vars.side_dist[0] = (ray[0] < 0)
		? (data->check_flags.pos_i - data->ray_vars.map_pos[0]) * data->ray_vars.delta_dist[0]
		: (data->ray_vars.map_pos[0] + 1.0 - data->check_flags.pos_i) * data->ray_vars.delta_dist[0];
	data->ray_vars.side_dist[1] = (ray[1] < 0)
		? (data->check_flags.pos_j - data->ray_vars.map_pos[1]) * data->ray_vars.delta_dist[1]
		: (data->ray_vars.map_pos[1] + 1.0 - data->check_flags.pos_j) * data->ray_vars.delta_dist[1];
}

t_bool	check_hit(t_data *data, double ray[2])
{
	if (data->ray_vars.side_dist[0] < data->ray_vars.side_dist[1])
	{
		data->ray_vars.side_dist[0] += data->ray_vars.delta_dist[0];
		data->ray_vars.map_pos[0] += data->ray_vars.step[0];
		data->textures_data.side = ray[0] > 0 ? N : S;
	}
	else
	{
		data->ray_vars.side_dist[1] += data->ray_vars.delta_dist[1];
		data->ray_vars.map_pos[1] += data->ray_vars.step[1];
		data->textures_data.side = ray[1] > 0 ? E : W;
	}
	return (data->map[vars->map_pos[0]][vars->map_pos[1]] == 1);
}

static void	run_dda(t_data *data, int i, double ray[2])
{
	t_bool		hit;

	init_vars(data, ray);
	hit = FALSE;
	while (!hit)
		hit = check_hit(data, ray);
	data->textures_data.wall_dist = (ray_facing(data->check_flags.pos_a) == 1 || ray_facing(data->check_flags.pos_a) == 3)
		? (vars.map_pos[0] - world->pos[0] + (1 - vars.step[0]) / 2) / ray[0]
		: (vars.map_pos[1] - world->pos[1] + (1 - vars.step[1]) / 2) / ray[1];
	world->depth_buffer[i] = data->textures_data.wall_dist;
	data.wall_x = (ray_facing(data->check_flags.pos_a) == 1 || ray_facing(data->check_flags.pos_a) == 3)
		? data->check_flags.pos_y + data->textures_data.wall_dist * ray[1]
		: data->check_flags.pos_x + data->textures_data.wall_dist * ray[0];
	data->textures_data.wall_x -= floor(data->textures_data.wall_x);
	data->textures_data.line_height = (data->textures_data.wall_dist > 0)
		? data->res_x / data->textures_data.wall_dist
		: 2147483647;
	draw_line_textured(data, i);
}

void	raycasting(t_data *data)
{
	int		i;
	double	camera_x;
	double	ray[2];

	i = 0;
	while (i < data->res_x)
	{
		camera_x = 2.0 * i / data->res_x - 1;
		ray[0] = world->dir[0] + world->cam_plane[0] * camera_x;
		ray[1] = world->dir[1] + world->cam_plane[1] * camera_x;
		run_dda(data, i, ray);
		i++;
	}
}
