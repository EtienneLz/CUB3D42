/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:56:43 by elouchez          #+#    #+#             */
/*   Updated: 2022/04/04 17:57:05 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static size_t	len_numb(unsigned long long n, int base)
{
	size_t	i;

	i = 0;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

char	*base_convert(unsigned long long n, char *base_figures, int l)
{
	char	*res;
	int		i;
	size_t	size;

	size = len_numb(n, l);
	res = (char *)malloc(sizeof(char) * (size + 1));
	i = 1;
	while (n != 0)
	{
		res[size - i++] = base_figures[n % l];
		n /= l;
	}
	res[size] = '\0';
	return (res);
}

unsigned int	hexa_color(int r, int g, int b)
{
	return(b + (g * 256) + (r * 256 * 256));
}

unsigned int	get_r(unsigned int rgb)
{
	return (rgb / (256 * 256));
}
