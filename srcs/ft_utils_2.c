/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:08:28 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/11 18:41:50 by elouchez         ###   ########.fr       */
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
