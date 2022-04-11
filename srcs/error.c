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
	write(1, "Erreur \n", 8);
	if (code == 0)
	{
		write(1, "Configuration invalide\n", 23);
		ft_free(data);
	}
	if (code == 1)
	{
		close(data->fd);
		write(1, "Configuration invalide\n", 23);
		ft_free(data);
	}
	if (code == 2)
	{
		close(data->fd);
		write(1, "Ta mere\n", 9);
		ft_free(data);
	}
	if (code == 3)
	{
		close(data->fd);
		write(1, "Map invalide\n", 14);
		ft_free(data);
	}
}

int	ft_free(t_data *data)
{
	int	i;

	i = 0;
	if (data->line != NULL)
		free(data->line);
	if (data->textures_data.textures[0] != NULL)
		free(data->textures_data.textures[0]);
	if (data->textures_data.textures[1] != NULL)
		free(data->textures_data.textures[1]);
	if (data->textures_data.textures[2] != NULL)
		free(data->textures_data.textures[2]);
	if (data->textures_data.textures[3] != NULL)
		free(data->textures_data.textures[3]);
	if (data->map)
	{
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	if (data->depth_buffer)
		free(data->depth_buffer);
	if (data->textures_data.image[0].img != NULL)
		mlx_destroy_image(data->vars.mlx, data->textures_data.image[0].img);
	if (data->textures_data.image[1].img != NULL)
		mlx_destroy_image(data->vars.mlx, data->textures_data.image[1].img);
	if (data->textures_data.image[2].img != NULL)
		mlx_destroy_image(data->vars.mlx, data->textures_data.image[2].img);
	if (data->textures_data.image[3].img != NULL)
		mlx_destroy_image(data->vars.mlx, data->textures_data.image[3].img);
	if (data->img != 0)
		mlx_destroy_image(data->vars.mlx, data->img);
	if (data->check_flags.init_done)
		mlx_destroy_window(data->vars.mlx, data->vars.win);
	mlx_destroy_display(data->vars.mlx);
	mlx_loop_end(&data->vars);
	free(data->vars.mlx);
	exit(EXIT_SUCCESS);
}
