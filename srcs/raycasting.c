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

static int	get_tex_color(t_image tex, double u, double v)
{
	char			*ptr;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	ptr = tex.addr + (int)(v * tex.height) *tex.line_length
		+ (int)(u * tex.width)*(tex.bbp >> 3);
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

static void	draw_init(t_data *data, t_image *text)
{
	data->vars.j = 0;
	data->vars.start = data->res_y / 2 - data->tex.line_height / 2;
	data->vars.end = data->res_y / 2 + data->tex.line_height / 2;
	if (data->tex.orientation == 'N')
		*text = data->tex.image[1];
	else if (data->tex.orientation == 'S')
		*text = data->tex.image[3];
	else if (data->tex.orientation == 'E')
		*text = data->tex.image[0];
	else if (data->tex.orientation == 'W')
		*text = data->tex.image[2];
}

static void	put_loop(t_data *data, t_image texture, int i)
{
	data->vars.color = get_tex_color(texture, data->tex.wall_x,
			((data->vars.j - data->vars.start) * 1.0)
			/ (data->vars.end - data->vars.start));
	my_mlx_pixel_put(data, i, data->vars.j++, data->vars.color);
}

static void	draw_line_textured(t_data *data, int i)
{
	t_image	texture;

	draw_init(data, &texture);
	if (data->vars.start > 0)
		while (data->vars.j < data->vars.start)
			my_mlx_pixel_put(data, i, data->vars.j++, data->tex.sky_c);
	if (data->vars.end >= data->res_y)
		while (data->vars.j < data->res_y)
			put_loop(data, texture, i);
	else
		while (data->vars.j < data->vars.end)
			put_loop(data, texture, i);
	while (data->vars.j < data->res_y)
		my_mlx_pixel_put(data, i, data->vars.j++, data->tex.floor_c);
}

static void	init_vars(t_data *data, double ray[2])
{
	data->ray_vars.delta_dist[0] = fabs(1.0 / ray[0]);
	data->ray_vars.delta_dist[1] = fabs(1.0 / ray[1]);
	data->ray_vars.map_pos[0] = floor(data->check.pos_i);
	data->ray_vars.map_pos[1] = floor(data->check.pos_j);
	if (ray[0] < 0)
		data->ray_vars.step[0] = -1;
	else
		data->ray_vars.step[0] = 1;
	if (ray[1] < 0)
		data->ray_vars.step[1] = -1;
	else
		data->ray_vars.step[1] = 1;
	if (ray[0] < 0)
		data->ray_vars.side_dist[0] = (data->check.pos_i
				- data->ray_vars.map_pos[0]) * data->ray_vars.delta_dist[0];
	else
		data->ray_vars.side_dist[0] = (data->ray_vars.map_pos[0] + 1.0
				- data->check.pos_i) * data->ray_vars.delta_dist[0];
	if (ray[1] < 0)
		data->ray_vars.side_dist[1] = (data->check.pos_j
				- data->ray_vars.map_pos[1]) * data->ray_vars.delta_dist[1];
	else
		data->ray_vars.side_dist[1] = (data->ray_vars.map_pos[1] + 1.0
				- data->check.pos_j) * data->ray_vars.delta_dist[1];
}

static int	check_hit(t_data *data, double ray[2])
{
	if (data->ray_vars.side_dist[0] < data->ray_vars.side_dist[1])
	{
		data->ray_vars.side_dist[0] += data->ray_vars.delta_dist[0];
		data->ray_vars.map_pos[0] += data->ray_vars.step[0];
		if (ray[0] > 0)
			data->tex.orientation = 'N';
		else
			data->tex.orientation = 'S';
	}
	else
	{
		data->ray_vars.side_dist[1] += data->ray_vars.delta_dist[1];
		data->ray_vars.map_pos[1] += data->ray_vars.step[1];
		if (ray[1] > 0)
			data->tex.orientation = 'E';
		else
			data->tex.orientation = 'W';
	}
	return (data->map[data->ray_vars.map_pos[0]]
		[data->ray_vars.map_pos[1]] == '1');
}

void	run_dda(t_data *data, int i, double ray[2])
{
	int	hit;

	init_vars(data, ray);
	hit = 0;
	while (!hit)
		hit = check_hit(data, ray);
	if (data->tex.orientation == 'N' || data->tex.orientation == 'S')
		data->tex.wall_dist = (data->ray_vars.map_pos[0] - data->check.pos_i
				+ (1 - data->ray_vars.step[0]) / 2) / ray[0];
	else
		data->tex.wall_dist = (data->ray_vars.map_pos[1] - data->check.pos_j
				+ (1 - data->ray_vars.step[1]) / 2) / ray[1];
	data->depth_buffer[i] = data->tex.wall_dist;
	if (data->tex.orientation == 'N' || data->tex.orientation == 'S')
		data->tex.wall_x = data->check.pos_j
			+ data->tex.wall_dist * ray[1];
	else
		data->tex.wall_x = data->check.pos_i
			+ data->tex.wall_dist * ray[0];
	data->tex.wall_x -= floor(data->tex.wall_x);
	if (data->tex.wall_dist > 0)
		data->tex.line_height = data->res_x / data->tex.wall_dist;
	else
		data->tex.line_height = 2147483647;
	draw_line_textured(data, i);
}
