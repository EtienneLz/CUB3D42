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

static char	*get_tex(t_data *data, int s)
{
	return (ft_substr(data->line, s, ft_strlen(data->line) - s));
}

static void	get_colors_2(t_data *data, unsigned int tmp, int k)
{
	if (tmp > 255)
		data->error = 1;
	if (k == 0)
		data->tex.r = tmp;
	if (k == 1)
		data->tex.g = tmp;
	if (k == 2)
		data->tex.b = tmp;
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
	return (hexa_color(data->tex.r,
			data->tex.g, data->tex.b));
}

void	ft_file_read(t_data *data)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		skip_lines(data);
		if (!(ft_strncmp("NO", data->line, 2)) && data->tex.t[1] == NULL)
			data->tex.t[1] = get_tex(data, skip_spaces(data, 2));
		else if (!(ft_strncmp("SO", data->line, 2)) && data->tex.t[3] == NULL)
			data->tex.t[3] = get_tex(data, skip_spaces(data, 2));
		else if (!(ft_strncmp("WE", data->line, 2)) && data->tex.t[2] == NULL)
			data->tex.t[2] = get_tex(data, skip_spaces(data, 2));
		else if (!(ft_strncmp("EA", data->line, 2)) && data->tex.t[0] == NULL)
			data->tex.t[0] = get_tex(data, skip_spaces(data, 2));
		else if (!(ft_strncmp("F", data->line, 1)) && data->tex.floor_c == 0)
			data->tex.floor_c = get_colors(data, 'F');
		else if (!(ft_strncmp("C", data->line, 1)) && data->tex.sky_c == 0)
			data->tex.sky_c = get_colors(data, 'C');
		else if (i < 5)
			data->error = 1;
		i++;
		if (data->line != NULL && i < 7)
			free(data->line);
	}
}
