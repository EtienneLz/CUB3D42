/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:56:21 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/05 16:27:09 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	ft_error(t_data *data, int code)
{
	write(2, "Error\n", 6);
	if (code == 0)
		write(2, "Invalid configuration D\n", 24);
	else
	{
		close(data->fd);
		if (code == 1)
			write(2, "Invalid configuration\n", 22);
		if (code == 2)
			write(2, "Invalid map\n", 13);
		if (code == 3)
			write(2, "Memory allocation failed\n", 25);
	}
	ft_free(data);
}

static void	ft_free_2(t_data *data)
{
	if (data->depth_buffer)
		free(data->depth_buffer);
	if (data->tex.image[0].img != NULL)
		mlx_destroy_image(data->vars.mlx, data->tex.image[0].img);
	if (data->tex.image[1].img != NULL)
		mlx_destroy_image(data->vars.mlx, data->tex.image[1].img);
	if (data->tex.image[2].img != NULL)
		mlx_destroy_image(data->vars.mlx, data->tex.image[2].img);
	if (data->tex.image[3].img != NULL)
		mlx_destroy_image(data->vars.mlx, data->tex.image[3].img);
	if (data->img != 0)
		mlx_destroy_image(data->vars.mlx, data->img);
	if (data->check.init_done)
		mlx_destroy_window(data->vars.mlx, data->vars.win);
	mlx_destroy_display(data->vars.mlx);
	mlx_loop_end(&data->vars);
	free(data->vars.mlx);
}

int	ft_free(t_data *data)
{
	int	i;

	i = 0;
	if (data->line != NULL)
		free(data->line);
	if (data->tex.t[0] != NULL)
		free(data->tex.t[0]);
	if (data->tex.t[1] != NULL)
		free(data->tex.t[1]);
	if (data->tex.t[2] != NULL)
		free(data->tex.t[2]);
	if (data->tex.t[3] != NULL)
		free(data->tex.t[3]);
	if (data->map != NULL)
	{
		while (data->map[i] != NULL)
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	ft_free_2(data);
	exit(EXIT_SUCCESS);
}
