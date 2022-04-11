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

static int		get_tex_color(t_image tex, double u, double v)
{
	char			*ptr;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	ptr = tex.addr + (int)(v * tex.height) * tex.line_length
		+ (int)(u * tex.width) * (tex.bbp >> 3);
	if (tex.endian)
		r = (unsigned char)(*ptr);
	else
		r = (unsigned char)(*(ptr + 2));
	g = (unsigned char)(*(ptr + 1));
	if (tex.endian)
		b = (unsigned char)(*(ptr + 2));
	else
		b = (unsigned char)(*ptr);
	return ((r << 16) + (g << 8) + b);
}

static void	draw_line_textured(t_data *data, int i)
{
	int		j;
	int		start;
	int		end;
	t_image	texture;
	int		color;

	start = data->res_y / 2 - data->textures_data.line_height / 2;
	end = data->res_y / 2 + data->textures_data.line_height / 2;
	if (data->textures_data.orientation == 'N')
		texture = data->textures_data.image[1];
	else if (data->textures_data.orientation == 'S')
		texture = data->textures_data.image[3];
	else if (data->textures_data.orientation == 'E')
		texture = data->textures_data.image[0];
	else if (data->textures_data.orientation == 'W')
		texture = data->textures_data.image[2];
	j = 0;
	if (start > 0)
		while (j < start)
			my_mlx_pixel_put(data, i, j++, data->textures_data.floor_c);
	while (j < (end >= data->res_y ? data->res_y - 1 : end))
	{
		color = get_tex_color(texture, data->textures_data.wall_x,
			((j - start) * 1.0) / (end - start));
		my_mlx_pixel_put(data, i, j++, color);
	}
	while (j < data->res_y)
		my_mlx_pixel_put(data, i, j++, data->textures_data.sky_c);
}

static void	init_vars(t_data *data, double ray[2])
{
	data->ray_vars.delta_dist[0] = fabs(1.0 / ray[0]);
	data->ray_vars.delta_dist[1] = fabs(1.0 / ray[1]);
	data->ray_vars.map_pos[0] = floor(data->check_flags.pos_i);
	data->ray_vars.map_pos[1] = floor(data->check_flags.pos_j);
	if (ray[0] < 0)
		data->ray_vars.step[0] = -1;
	else
		data->ray_vars.step[0] = 1;
	if (ray[1] < 0)
		data->ray_vars.step[1] = -1;
	else
		data->ray_vars.step[1] = 1;
	if (ray[0] < 0)
		data->ray_vars.side_dist[0] = (data->check_flags.pos_i - data->ray_vars.map_pos[0]) * data->ray_vars.delta_dist[0];
	else
		data->ray_vars.side_dist[0] = (data->ray_vars.map_pos[0] + 1.0 - data->check_flags.pos_i) * data->ray_vars.delta_dist[0];
	if (ray[1] < 0)
		data->ray_vars.side_dist[1] = (data->check_flags.pos_j - data->ray_vars.map_pos[1]) * data->ray_vars.delta_dist[1];
	else
		data->ray_vars.side_dist[1] = (data->ray_vars.map_pos[1] + 1.0 - data->check_flags.pos_j) * data->ray_vars.delta_dist[1];
}

static int	check_hit(t_data *data, double ray[2])
{
	if (data->ray_vars.side_dist[0] < data->ray_vars.side_dist[1])
	{
		data->ray_vars.side_dist[0] += data->ray_vars.delta_dist[0];
		data->ray_vars.map_pos[0] += data->ray_vars.step[0];
		if (ray[0] > 0)
			data->textures_data.orientation = 'N';
		else
			data->textures_data.orientation = 'S';
	}
	else
	{
		data->ray_vars.side_dist[1] += data->ray_vars.delta_dist[1];
		data->ray_vars.map_pos[1] += data->ray_vars.step[1];
		if (ray[1] > 0)
			data->textures_data.orientation = 'E';
		else
			data->textures_data.orientation = 'W';
	}
	return (data->map[data->ray_vars.map_pos[0]][data->ray_vars.map_pos[1]] == '1');
}

static void	run_dda(t_data *data, int i, double ray[2])
{
	int	hit;

	init_vars(data, ray);
	hit = 0;
	while (!hit)
		hit = check_hit(data, ray);
	if (data->textures_data.orientation == 'N' || data->textures_data.orientation == 'S')
		data->textures_data.wall_dist = (data->ray_vars.map_pos[0] - data->check_flags.pos_i + (1 - data->ray_vars.step[0]) / 2) / ray[0];
	else
		data->textures_data.wall_dist = (data->ray_vars.map_pos[1] - data->check_flags.pos_j + (1 - data->ray_vars.step[1]) / 2) / ray[1];
	data->depth_buffer[i] = data->textures_data.wall_dist;
	if (data->textures_data.orientation == 'N' || data->textures_data.orientation == 'S')
		data->textures_data.wall_x = data->check_flags.pos_j + data->textures_data.wall_dist * ray[1];
	else
		data->textures_data.wall_x = data->check_flags.pos_i + data->textures_data.wall_dist * ray[0];
	data->textures_data.wall_x -= floor(data->textures_data.wall_x);
	if (data->textures_data.wall_dist > 0)
		data->textures_data.line_height = data->res_x / data->textures_data.wall_dist;
	else
		data->textures_data.line_height = 2147483647;
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
		camera_x = 1.5 * i / data->res_x - 1;
		ray[0] = data->dir[0] + data->cam_plane[0] * camera_x;
		ray[1] = data->dir[1] + data->cam_plane[1] * camera_x;
		run_dda(data, i, ray);
		i++;
	}
}
