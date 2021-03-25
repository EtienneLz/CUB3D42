#include "../includes/cube.h"

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (ft_strlen(s) <= start)
		len = 0;
	if (!(dest = malloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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