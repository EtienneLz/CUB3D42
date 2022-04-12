/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:08:01 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/11 23:08:01 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	count_line(t_data *data, char *file_name)
{
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	while (ret != 0)
	{
		if (data->vars.size_line_max < ft_strlen(data->line))
			data->vars.size_line_max = ft_strlen(data->line);
		data->vars.size_map++;
		free(data->line);
		ret = get_next_line(data->fd, &data->line);
	}
	free(data->line);
	data->line = NULL;
	if (data->error)
		ft_error(data, 1);
	close(data->fd);
	data->map = malloc(sizeof(char *) * (data->vars.size_map + 2));
	if (!data->map)
		ft_error(data, 2);
	data->fd = open(file_name, O_RDONLY);
	if (data->fd == -1)
		ft_error(data, 1);
	while (i <= 5 + data->skip)
	{
		get_next_line(data->fd, &data->line);
		i++;
		free(data->line);
	}
}

void	parse_map(t_data *data)
{
	int				i;
	unsigned int	j;
	int				ret;

	i = 0;
	ret = 1;
	while (ret != 0)
	{
		ret = get_next_line(data->fd, &data->line);
		j = 0;
		data->map[i] = malloc(sizeof(char) * (data->vars.size_line_max + 1));
		if (!(data->map[i]))
			ft_error(data, 3);
		while (data->line[j])
		{
			if (data->line[j] == ' ' || data->line[j] == '1')
				data->map[i][j] = data->line[j];
			else if (data->line[j] == '2')
				data->map[i][j] = '2';
			else if (data->line[j] == '0')
				data->map[i][j] = '0';
			else if (data->line[j] == 'N' || data->line[j] == 'S'
				|| data->line[j] == 'W' || data->line[j] == 'E')
			{
				data->player++;
				data->cam_dir = data->line[j];
				data->map[i][j] = data->line[j];
			}
			else
				data->error = 1;
			j++;
		}
		while (j < data->vars.size_line_max)
			data->map[i][j++] = ' ';
		data->map[i][j] = '\0';
		free(data->line);
		data->line = NULL;
		i++;
	}
	data->map[i] = NULL;
	if (data->error || data->player != 1)
		ft_error(data, 2);
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
		j = 0;
		while (data->map[i][j])
		{
			tmp_map[i][j] = data->map[i][j];
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
			|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->check.s_pos_i = i;
				data->check.s_pos_j = j;
				data->check.s_direction = data->map[i][j];
				tmp_map[i][j] = '0';
			}
			j++;
		}
		while (j < (int)data->vars.size_line_max)
		{
			tmp_map[i][j] = ' ';
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
		free(frame);
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
		free(frame);
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
