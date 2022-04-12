/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:08:28 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/12 11:13:34 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	skip_lines(t_data *data)
{
	if (get_next_line(data->fd, &data->line) < 1)
			data->error = 1;
	while (data->line[0] == '\0')
	{
		free(data->line);
		data->skip++;
		if (get_next_line(data->fd, &data->line) < 1)
			data->error = 1;
	}
}

int	skip_spaces(t_data *data, int n)
{
	while (data->line[n] && data->line[n] == ' ')
		n++;
	return (n);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	printf("in\n");
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0')
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	printf("OK\n");
	return (0);
void	check_empty(t_data *data)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	while (i < data->vars.size_map)
	{
		j = 0;
		check = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != ' ')
				check = 1;
			j++;
		}
		if (check == 0)
			ft_error(data, 2);
		i++;
	}
	if (check == 0)
		ft_error(data, 2);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char		*dest;

	dest = malloc(nmemb * size);
	if (!dest)
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
