#include "../includes/cube.h"

static char	*get_textures(t_data *data, char *line, char c1, char c2, int s)
{
	if (line[0] != c1 && line[1] != c2)
		ft_error(data, 1);
	return (ft_substr(line, s, ft_strlen(line) - s));
}

static void	get_colors_2(t_data *data, unsigned int tmp, int k)
{
	if (tmp > 255)
		ft_error(data, 1);
	if (k == 0)
		data->textures_data.r = tmp;
	if (k == 1)
		data->textures_data.g = tmp;
	if (k == 2)
		data->textures_data.b = tmp;
}

static unsigned int	get_colors(t_data *data, char *line, char c)
{
	int	tmp;
	int	i;
	int	j;
	int	k;

	i = 2;
	j = 0;
	k = 0;
	tmp = 0;
	if (line[0] != c && line[1] != ' ')
		ft_error(data, 1);
	while (k < 3)
	{
		while (line[i] >= '0' && line[i] <= '9')
		{
			tmp *= 10;
			tmp += line[i] - '0';
			i++;
			j++;
		}
		if (j > 3 || (line[i] != ',' && k < 2))
			ft_error(data, 2);
		get_colors_2(data, tmp, k);
		j = 0;
		tmp = 0;
		i++;
		k++;
	}
	return (hexa_color(data->textures_data.r,
			data->textures_data.g, data->textures_data.b));
}

static void	ft_file_read_2(t_data *data, char *line)
{
	if (get_next_line(data->fd, &line) < 1)
		ft_error(data, 1);
	if (line[0] != '\0')
		ft_error(data, 1);
	if (get_next_line(data->fd, &line) < 1)
		ft_error(data, 1);
	data->textures_data.sprite_t = get_textures(data, line, 'S', ' ', 2);
	if (get_next_line(data->fd, &line) < 1)
		ft_error(data, 1);
	data->textures_data.floor_c = get_colors(data, line, 'F');
	if (get_next_line(data->fd, &line) < 1)
		ft_error(data, 1);
	data->textures_data.sky_c = get_colors(data, line, 'C');
}

static void	get_resolution(t_data *data, char *line)
{
	int	i;

	i = 2;
	if (line[0] != 'R')
		ft_error(data, 1);
	while (line[i] && (line[i] <= '9' && line[i] >= '0'))
	{
		data->res_x *= 10;
		data->res_x += line[i] - '0';
		i++;
	}
	i++;
	while (line[i] && (line[i] <= '9' && line[i] >= '0'))
	{
		data->res_y *= 10;
		data->res_y += line[i] - '0';
		i++;
	}
}

void	ft_file_read(t_data *data, char *file_name)
{
	char	*line;

	data->fd = open(file_name, O_RDONLY);
	if (data->fd == -1)
		ft_error(data, 1);
	if (get_next_line(data->fd, &line) < 1)
		ft_error(data, 1);
	get_resolution(data, line);
	free (line);
	if (get_next_line(data->fd, &line) < 1)
		ft_error(data, 1);
	data->textures_data.north_t = get_textures(data, line, 'N', 'O', 3);
	free (line);
	if (get_next_line(data->fd, &line) < 1)
		ft_error(data, 1);
	data->textures_data.south_t = get_textures(data, line, 'S', 'O', 3);
	free (line);
	if (get_next_line(data->fd, &line) < 1)
		ft_error(data, 1);
	data->textures_data.west_t = get_textures(data, line, 'W', 'E', 3);
	free (line);
	if (get_next_line(data->fd, &line) < 1)
		ft_error(data, 1);
	data->textures_data.east_t = get_textures(data, line, 'E', 'A', 3);
	free (line);
	ft_file_read_2(data, line);
}
