#include "../includes/cube.h"

static char	*get_textures(t_data *data, char c1, char c2, int s)
{
	if (data->line[0] && data->line[1] && data->line[0] != c1 && data->line[1] != c2)
		ft_error(data, 1);
	return (ft_substr(data->line, s, ft_strlen(data->line) - s));
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
	if (data->line[0] != c && data->line[1] != ' ')
		ft_error(data, 1);
	while (k < 3)
	{
		while (data->line[i] >= '0' && data->line[i] <= '9')
		{
			tmp *= 10;
			tmp += data->line[i] - '0';
			i++;
			j++;
		}
		if (j > 3 || (data->line[i] != ',' && k < 2))
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

static void	ft_file_read_2(t_data *data)
{
	if (get_next_line(data->fd, &data->line) < 1)
		ft_error(data, 1);
	if (data->line[0])
		ft_error(data, 1);
	free(data->line);
	if (get_next_line(data->fd, &data->line) < 1)
		ft_error(data, 1);
	data->textures_data.floor_c = get_colors(data, 'F');
	free(data->line);
	if (get_next_line(data->fd, &data->line) < 1)
		ft_error(data, 1);
	data->textures_data.sky_c = get_colors(data, 'C');
	free(data->line);
}

static void	get_resolution(t_data *data)
{
	int	i;

	i = 2;
	if (data->line[0] != 'R')
		ft_error(data, 1);
	while (data->line[i] && (data->line[i] <= '9' && data->line[i] >= '0'))
	{
		data->res_x *= 10;
		data->res_x += data->line[i] - '0';
		i++;
	}
	i++;
	while (data->line[i] && (data->line[i] <= '9' && data->line[i] >= '0'))
	{
		data->res_y *= 10;
		data->res_y += data->line[i] - '0';
		i++;
	}
}

void	ft_file_read(t_data *data, char *file_name)
{
	data->fd = open(file_name, O_RDONLY);
	if (data->fd == -1)
		ft_error(data, 1);
	if (get_next_line(data->fd, &data->line) < 1)
		ft_error(data, 1);
	get_resolution(data);
	free(data->line);
	if (get_next_line(data->fd, &data->line) < 1)
		ft_error(data, 1);
	data->textures_data.textures[1] = get_textures(data, 'N', 'O', 3);
	free(data->line);
	if (get_next_line(data->fd, &data->line) < 1)
		ft_error(data, 1);
	data->textures_data.textures[3] = get_textures(data, 'S', 'O', 3);
	free(data->line);
	if (get_next_line(data->fd, &data->line) < 1)
		ft_error(data, 1);
	data->textures_data.textures[2] = get_textures(data, 'W', 'E', 3);
	free(data->line);
	if (get_next_line(data->fd, &data->line) < 1)
		ft_error(data, 1);
	data->textures_data.textures[0] = get_textures(data, 'E', 'A', 3);
	free(data->line);
	ft_file_read_2(data);
}
