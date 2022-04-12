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

static char	*get_textures(t_data *data, int s)
{
	//if (data->line[0] && data->line[1]
	//	&& (data->line[0] != c1 || data->line[1] != c2))
	//	data->error = 1;
	return (ft_substr(data->line, s, ft_strlen(data->line) - s));
}

static void	get_colors_2(t_data *data, unsigned int tmp, int k)
{
	if (tmp > 255)
		data->error = 1;
	if (k == 0)
		data->textures_data.r = tmp;
	if (k == 1)
		data->textures_data.g = tmp;
	if (k == 2)
		data->textures_data.b = tmp;
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
		if (data->line[i] == ' ')
			i = skip_spaces(data, i);
		while (data->line[i] >= '0' && data->line[i] <= '9')
		{
			tmp *= 10;
			tmp += data->line[i] - '0';
			i++;
			j++;
		}
		if (data->line[i] == ' ')
			i = skip_spaces(data, i);
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
	return (hexa_color(data->textures_data.r,
			data->textures_data.g, data->textures_data.b));
}

/*static void	ft_file_read_2(t_data *data)
{
	skip_lines(data);
	data->textures_data.floor_c = get_colors(data, 'F');
	free(data->line);
	skip_lines(data);
	data->textures_data.sky_c = get_colors(data, 'C');
	free(data->line);
}*/

void	ft_file_read(t_data *data, char *file_name)
{
	int	i;

	i = 0;
	data->fd = open(file_name, O_RDONLY);
	if (data->fd == -1)
		ft_error(data, 1);
	while (i <= 7)
	{
		printf("i = %d\n", i);
		//get_next_line(data->fd, &data->line);
		skip_lines(data);
		if (!(ft_strncmp("NO", data->line, 2)))
			data->textures_data.textures[1] = get_textures(data, skip_spaces(data, 2));
		else if (!(ft_strncmp("SO", data->line, 2)))
			data->textures_data.textures[3] = get_textures(data, skip_spaces(data, 2));
		else if (!(ft_strncmp("WE", data->line, 2)))
			data->textures_data.textures[2] = get_textures(data, skip_spaces(data, 2));
		else if (!(ft_strncmp("EA", data->line, 2)))
			data->textures_data.textures[0] = get_textures(data, skip_spaces(data, 2));
		else if (!(ft_strncmp("F", data->line, 1)))
			data->textures_data.floor_c = get_colors(data, 'F');
		else if (!(ft_strncmp("C", data->line, 1)))
			data->textures_data.sky_c = get_colors(data, 'C');
		i++;
		printf("error %d\n", data->error);
		if (data->line != NULL)
			free(data->line);
	}
}
