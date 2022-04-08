/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:56:43 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/04 17:57:05 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static size_t	len_numb(unsigned long long n, int base)
{
	size_t	i;

	i = 0;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

char	*base_convert(unsigned long long n, char *base_figures, int l)
{
	char	*res;
	int		i;
	size_t	size;

	size = len_numb(n, l);
	res = (char *)malloc(sizeof(char) * (size + 1));
	i = 1;
	while (n != 0)
	{
		res[size - i++] = base_figures[n % l];
		n /= l;
	}
	res[size] = '\0';
	return (res);
}

unsigned int	hexa_color(int r, int g, int b)
{
	return(b + (g * 256) + (r * 256 * 256));
}

unsigned int	get_r(unsigned int rgb)
{
	return (rgb / (256 * 256));
}

unsigned int	mlx_get_pixel(t_image text, int x, int y)
{
	return (*(unsigned int *)(text.addr
		+ (x * text.bbp / 8 + y * text.line_length)));
}

static void	texture_init_2(t_data *data)
{
	data->textures_data.image[0].addr = mlx_get_data_addr(data->textures_data.image[0].img, &data->textures_data.image[0].bbp,
			&data->textures_data.image[0].line_length, &data->textures_data.image[0].endian);
	data->textures_data.image[1].addr = mlx_get_data_addr(data->textures_data.image[1].img, &data->textures_data.image[1].bbp,
			&data->textures_data.image[1].line_length, &data->textures_data.image[1].endian);
	data->textures_data.image[2].addr = mlx_get_data_addr(data->textures_data.image[2].img, &data->textures_data.image[2].bbp,
			&data->textures_data.image[2].line_length, &data->textures_data.image[2].endian);
	data->textures_data.image[3].addr = mlx_get_data_addr(data->textures_data.image[3].img, &data->textures_data.image[3].bbp,
			&data->textures_data.image[3].line_length, &data->textures_data.image[3].endian);
}

void	texture_init(t_data *data)
{
	data->textures_data.image[0].img = mlx_xpm_file_to_image(data->vars.mlx,
			data->textures_data.textures[0], &(data->textures_data.image[0].width),
			&(data->textures_data.image[0].height));
	if (data->textures_data.image[0].img == NULL)
		ft_error(data, 0);
	data->textures_data.image[1].img = mlx_xpm_file_to_image(data->vars.mlx,
			data->textures_data.textures[1], &(data->textures_data.image[1].width),
			&(data->textures_data.image[1].height));
	if (data->textures_data.image[1].img == NULL)
		ft_error(data, 0);
	data->textures_data.image[2].img = mlx_xpm_file_to_image(data->vars.mlx,
			data->textures_data.textures[2], &(data->textures_data.image[2].width),
			&(data->textures_data.image[2].height));
	if (data->textures_data.image[2].img == NULL)
		ft_error(data, 0);
	data->textures_data.image[3].img = mlx_xpm_file_to_image(data->vars.mlx,
			data->textures_data.textures[3], &(data->textures_data.image[3].width),
			&(data->textures_data.image[3].height));
	if (data->textures_data.image[3].img == NULL)
		ft_error(data, 0);
	texture_init_2(data);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char		*dest;

	if (!(dest = malloc(nmemb * size)))
		return (0);
	ft_memset(dest, 0, size * nmemb);
	return (dest);
}

void	*ft_memset(void *dest, int c, size_t n)
{
	unsigned char	*ensac;
	size_t			i;

	i = 0;
	ensac = dest;
	while (i < n)
	{
		ensac[i] = c;
		i++;
	}
	return (dest);
}