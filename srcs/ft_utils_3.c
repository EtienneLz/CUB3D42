/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:03:49 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/11 23:32:10 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	texture_init_2(t_data *data)
{
	data->text_d.image[0].addr
		= mlx_get_data_addr(data->text_d.image[0].img,
			&data->text_d.image[0].bbp,
			&data->text_d.image[0].line_length,
			&data->text_d.image[0].endian);
	data->text_d.image[1].addr
		= mlx_get_data_addr(data->text_d.image[1].img,
			&data->text_d.image[1].bbp,
			&data->text_d.image[1].line_length,
			&data->text_d.image[1].endian);
	data->text_d.image[2].addr
		= mlx_get_data_addr(data->text_d.image[2].img,
			&data->text_d.image[2].bbp,
			&data->text_d.image[2].line_length,
			&data->text_d.image[2].endian);
	data->text_d.image[3].addr
		= mlx_get_data_addr(data->text_d.image[3].img,
			&data->text_d.image[3].bbp,
			&data->text_d.image[3].line_length,
			&data->text_d.image[3].endian);
}

void	texture_init(t_data *data)
{
	data->text_d.image[0].img = mlx_xpm_file_to_image(data->vars.mlx,
			data->text_d.textures[0],
			&(data->text_d.image[0].width),
			&(data->text_d.image[0].height));
	if (data->text_d.image[0].img == NULL)
		ft_error(data, 0);
	data->text_d.image[1].img = mlx_xpm_file_to_image(data->vars.mlx,
			data->text_d.textures[1],
			&(data->text_d.image[1].width),
			&(data->text_d.image[1].height));
	if (data->text_d.image[1].img == NULL)
		ft_error(data, 0);
	data->text_d.image[2].img = mlx_xpm_file_to_image(data->vars.mlx,
			data->text_d.textures[2],
			&(data->text_d.image[2].width),
			&(data->text_d.image[2].height));
	if (data->text_d.image[2].img == NULL)
		ft_error(data, 0);
	data->text_d.image[3].img = mlx_xpm_file_to_image(data->vars.mlx,
			data->text_d.textures[3],
			&(data->text_d.image[3].width),
			&(data->text_d.image[3].height));
	if (data->text_d.image[3].img == NULL)
		ft_error(data, 0);
	texture_init_2(data);
}
