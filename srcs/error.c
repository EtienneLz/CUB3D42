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
	ft_exit();
}

void	ft_free(t_data *data)
{
	if (data->textures_data.textures[0])
		free(data->textures_data.textures[0]);
	if (data->textures_data.textures[1])
		free(data->textures_data.textures[1]);
	if (data->textures_data.textures[2])
		free(data->textures_data.textures[2]);
	if (data->textures_data.textures[3])
		free(data->textures_data.textures[3]);
	if (data->map)
		free(data->map);
	ft_exit();
}

int	ft_exit(void)
{
	exit(EXIT_SUCCESS);
}
