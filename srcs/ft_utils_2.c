/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:08:28 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/12 10:16:57 by mseligna         ###   ########.fr       */
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
}
