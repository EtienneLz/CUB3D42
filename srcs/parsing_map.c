/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:53:33 by mseligna          #+#    #+#             */
/*   Updated: 2022/04/12 15:53:33 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	copy_map_2(t_data *data, int i, char **tmp_map)
{
	int	j;

	j = 0;
	while (data->map[i][j])
	{
		if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
		|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
		{
			data->check.s_pos_i = i;
			data->check.s_pos_j = j;
			data->check.s_direction = data->map[i][j];
			tmp_map[i][j] = '0';
		}
		else
			tmp_map[i][j] = data->map[i][j];
		j++;
	}
	return (j);
}

static char	**copy_map(t_data *data)
{
	char	**tmp_map;
	int		i;
	int		j;

	i = 0;
	tmp_map = malloc(sizeof(char *) * (data->vars.size_map + 2));
	if (!tmp_map)
		ft_error(data, 3);
	while (data->map[i] != NULL)
	{
		tmp_map[i] = NULL;
		tmp_map[i] = malloc(sizeof(char) * (data->vars.size_line_max + 1));
		if (!(tmp_map[i]))
			ft_error(data, 3);
		j = copy_map_2(data, i, tmp_map);
		while (j < (int)data->vars.size_line_max)
		{
			tmp_map[i][j] = '1';
			j++;
		}
		tmp_map[i][j] = '\0';
		i++;
	}
	tmp_map[i] = NULL;
	return (tmp_map);
}

static void	ft_fill(t_data *data, char **frame, int i, int j)
{
	if (frame[i][j] == ' ')
	{
		free_tab(frame);
		ft_error(data, 2);
	}
	if (frame[i][j] == '0' || frame[i][j] == '2')
	{
		if (i == 0 || i == data->vars.size_map
			|| j == 0 || j == (int)data->vars.size_line_max)
			ft_error(data, 2);
		frame[i][j] = 'C';
		ft_fill(data, frame, i + 1, j);
		if (i != 0)
			ft_fill(data, frame, i - 1, j);
		ft_fill(data, frame, i, j + 1);
		if (j != 0)
			ft_fill(data, frame, i, j - 1);
	}
	else if (frame[i][j] != '1' && frame[i][j] != 'C')
	{
		free_tab(frame);
		ft_error(data, 2);
	}
}

void	check_map(t_data *data)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = copy_map(data);
	ft_fill(data, tmp, data->check.s_pos_i, data->check.s_pos_j);
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	if (data->check.s_pos_i == 0 && data->check.s_pos_j == 0)
		ft_error(data, 2);
}
