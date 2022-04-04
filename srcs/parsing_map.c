#include "../includes/cube.h"

void    count_line()
{
	int ret;
	char *line;
	int i;

	i = 0;
	while ((ret = get_next_line(g_data.fd, &line) != 0))
	{
		if (g_vars.size_line_max < ft_strlen(line))
			g_vars.size_line_max = ft_strlen(line);
		g_vars.size_map++;
		free(line);
	}
	close(g_data.fd);
	if (!(g_data.map = malloc(sizeof(char*) * (g_vars.size_map + 1))))
		ft_error(2);
	if ((g_data.fd = open("config.cub", O_RDONLY)) == -1)
		ft_error(1);
	while (i <= 9)
	{
		get_next_line(g_data.fd, &line);
		i++;
		free(line);
	}
}

void	parse_map(void)
{
	int				i;
	unsigned int	j;
	int				ret;
	char			*line;

	i = 0;
	ret = 1;
	while (ret != 0)
	{
		ret = get_next_line(g_data.fd, &line);
		g_data.map[i] = NULL;
		j = 0;
		if (!(g_data.map[i] = malloc(sizeof(char) * (g_vars.size_line_max + 1))))
			ft_error(1);
		while (line[j])
		{
			if (line[j] == ' ' || line[j] == '1')
				g_data.map[i][j] = line[j];
			else if (line[j] == '2')
				g_data.map[i][j] = '2';
			else if (line[j] == '0')
				g_data.map[i][j] = '0';
			else if (line[j] == 'N' || line[j] == 'S' || line[j] == 'W' || line[j] == 'E')
				g_data.map[i][j] = line[j];
			else
				ft_error(1);
			j++;
		}
		while (j < g_vars.size_line_max)
			g_data.map[i][j++] = ' ';
		g_data.map[i][j] = '\0';
		free(line);
		i++;
	}
	g_data.map[i] = NULL;
}

static char	**copy_map()
{
	char	**tmp_map;
	int		i;
	int		j;

	i = 0;
	tmp_map = malloc(sizeof(char *) * (g_vars.size_map + 1));
	while (g_data.map[i] != NULL)
	{
		tmp_map[i] = NULL;
		tmp_map[i] = malloc(sizeof(char) * (g_vars.size_line_max + 1));
		j = 0;
		while (g_data.map[i][j])
		{
			tmp_map[i][j] = g_data.map[i][j];
			if (g_data.map[i][j] == 'N' || g_data.map[i][j] == 'S'
			|| g_data.map[i][j] == 'W' || g_data.map[i][j] == 'E')
			{
				g_check_flags.s_pos_i = i;
				g_check_flags.s_pos_j = j;
				g_check_flags.s_direction = g_data.map[i][j];
				tmp_map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	tmp_map[i] = NULL;
	return (tmp_map);
}

static void	ft_fill(char **frame, int i, int j)
{
	if (frame[i][j] == ' ')
	{
		free(frame);
		ft_error(3);
	}
	if (frame[i][j] == '0' || frame[i][j] == '2')
	{
		if (i == 0 || i == g_vars.size_map || j == 0 || j == (int)g_vars.size_line_max)
			ft_error(3);
		frame[i][j] = 'C';
		ft_fill(frame, i + 1, j);
		if (i != 0)
			ft_fill(frame, i - 1, j);
		ft_fill(frame, i, j + 1);
		if (j != 0)
			ft_fill(frame, i, j - 1);
	}
	else if (frame[i][j] != '1' && frame[i][j] != 'C')
	{
		free(frame);
		ft_error(3);
	}
}

void	check_map(void)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = copy_map();
	ft_fill(tmp, g_check_flags.s_pos_i, g_check_flags.s_pos_j);
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	if (g_check_flags.s_pos_i == 0 && g_check_flags.s_pos_j == 0)
		ft_error(3);
}
