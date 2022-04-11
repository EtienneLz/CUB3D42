/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:42:09 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/11 18:42:09 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static char	*get_textures(t_data *data, char c1, char c2, int s)
{
	if (data->line[0] && data->line[1]
		&& (data->line[0] != c1 || data->line[1] != c2))
		data->error = 1;
	return (ft_substr(data->line, s, ft_strlen(data->line) - s));
}

static void	get_colors_2(t_data *data, unsigned int tmp, int k)
{
	if (tmp > 255)
		data->error = 1;
	if (k == 0)
		data->text_d.r = tmp;
	if (k == 1)
		data->text_d.g = tmp;
	if (k == 2)
		data->text_d.b = tmp;
}

static unsigned int	get_colors(t_data *data, char c)
{
	int	tmp;
	int	i;
	int	j;
	int	k;

	i = 2;
	j = 0;
	k = 0;
	tmp = 0;
	if (data->line[0] && data->line[1]
		&& (data->line[0] != c || data->line[1] != ' '))
		data->error = 1;
	while (data->line[i])
	{
		if (k == 3)
			break ;
		while (data->line[i] >= '0' && data->line[i] <= '9')
		{
			tmp *= 10;
			tmp += data->line[i] - '0';
			i++;
			j++;
		}
		if (((j > 3 || j == 0) || (data->line[i] != ',' && k < 2))
			|| (k == 2 && data->line[i] != '\0'))
			data->error = 1;
		get_colors_2(data, tmp, k);
		j = 0;
		tmp = 0;
		if (data->line[i] == ',')
			i++;
		k++;
	}
	if (k < 3)
		data->error = 1;
	return (hexa_color(data->text_d.r,
			data->text_d.g, data->text_d.b));
}

static void	ft_file_read_2(t_data *data)
{
	skip_lines(data);
	data->text_d.floor_c = get_colors(data, 'F');
	free(data->line);
	skip_lines(data);
	data->text_d.sky_c = get_colors(data, 'C');
	free(data->line);
}

void	ft_file_read(t_data *data, char *file_name)
{
	data->fd = open(file_name, O_RDONLY);
	if (data->fd == -1)
		ft_error(data, 1);
	skip_lines(data);
	data->text_d.textures[1] = get_textures(data, 'N', 'O', 3);
	free(data->line);
	skip_lines(data);
	data->text_d.textures[3] = get_textures(data, 'S', 'O', 3);
	free(data->line);
	skip_lines(data);
	data->text_d.textures[2] = get_textures(data, 'W', 'E', 3);
	free(data->line);
	skip_lines(data);
	data->text_d.textures[0] = get_textures(data, 'E', 'A', 3);
	free(data->line);
	ft_file_read_2(data);
}
