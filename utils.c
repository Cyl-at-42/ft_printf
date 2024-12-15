#include "ft_printf_bonus.h"

char	*micro_atoi(int *int_ptr, char *str)
{
	unsigned int	nbr;
	int				digits;
	char			*str2;

	nbr = 0;
	str2 = str;
	while (*str >= '0' && *str <= '9')
		nbr = nbr * 10 + (*str++ - '0');
	digits = str - str2;
	if (digits > 10)
		nbr = 0xffffffff;
	else
		if (digits == 10 && nbr >= 2147483648)
			nbr = 0xffffffff;
	*int_ptr = nbr;
	return (str);
}

size_t	ft_strlen(char *s)
{
	char	*s2;

	s2 = (char *)s;
	while (*s2++)
		;
	return (--s2 - s);
}

int	selint(int condition, int trueval, int falseval)
{
	if (condition)
		return (trueval);
	return (falseval);
}

void	reset_lens(size_t *len1, size_t *len2)
{
	*len1 = 0;
	*len2 = 0;
}
