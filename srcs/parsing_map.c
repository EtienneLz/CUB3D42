#include "../includes/cube.h"

void    count_line(t_data *data)
{
	int ret;
	char *line;
	int i;

	i = 0;
	while ((ret = get_next_line(data->fd, &line) != 0))
	{
		if (data->vars.size_line_max < ft_strlen(line))
			data->vars.size_line_max = ft_strlen(line);
		data->vars.size_map++;
		free(line);
	}
	close(data->fd);
	if (!(data->map = malloc(sizeof(char*) * (data->vars.size_map + 1))))
		ft_error(data, 2);
	if ((data->fd = open("config.cub", O_RDONLY)) == -1)
		ft_error(data, 1);
	while (i <= 9)
	{
		get_next_line(data->fd, &line);
		i++;
		free(line);
	}
}

void	parse_map(t_data *data)
{
	int				i;
	unsigned int	j;
	int				ret;
	char			*line;

	i = 0;
	ret = 1;
	while (ret != 0)
	{
		ret = get_next_line(data->fd, &line);
		data->map[i] = NULL;
		j = 0;
		if (!(data->map[i] = malloc(sizeof(char) * (data->vars.size_line_max + 1))))
			ft_error(data, 1);
		while (line[j])
		{
			if (line[j] == ' ' || line[j] == '1')
				data->map[i][j] = line[j];
			else if (line[j] == '2')
				data->map[i][j] = '2';
			else if (line[j] == '0')
				data->map[i][j] = '0';
			else if (line[j] == 'N' || line[j] == 'S' || line[j] == 'W' || line[j] == 'E')
				data->map[i][j] = line[j];
			else
				ft_error(data, 1);
			j++;
		}
		while (j < data->vars.size_line_max)
			data->map[i][j++] = ' ';
		data->map[i][j] = '\0';
		free(line);
		i++;
	}
	data->map[i] = NULL;
}

static char	**copy_map(t_data *data)
{
	char	**tmp_map;
	int		i;
	int		j;

	i = 0;
	tmp_map = malloc(sizeof(char *) * (data->vars.size_map + 1));
	while (data->map[i] != NULL)
	{
		tmp_map[i] = NULL;
		tmp_map[i] = malloc(sizeof(char) * (data->vars.size_line_max + 1));
		j = 0;
		while (data->map[i][j])
		{
			tmp_map[i][j] = data->map[i][j];
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
			|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->check_flags.s_pos_i = i;
				data->check_flags.s_pos_j = j;
				data->check_flags.s_direction = data->map[i][j];
				tmp_map[i][j] = '0';
			}
			j++;
		}
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
		ft_error(data, 3);
	}
	if (frame[i][j] == '0' || frame[i][j] == '2')
	{
		if (i == 0 || i == data->vars.size_map || j == 0 || j == (int)data->vars.size_line_max)
			ft_error(data, 3);
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
		ft_error(data, 3);
	}
}

void	check_map(t_data *data)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = copy_map(data);
	ft_fill(data, tmp, data->check_flags.s_pos_i, data->check_flags.s_pos_j);
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	if (data->check_flags.s_pos_i == 0 && data->check_flags.s_pos_j == 0)
		ft_error(data, 3);
}
