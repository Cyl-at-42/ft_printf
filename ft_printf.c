#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list			arglist;
	char			*unformattedstart_ptr;
	size_t			unformatted_len;
	size_t			result_len;
	t_formatinfo	fi;

	va_start(arglist, format);
	unformattedstart_ptr = (char *) format;
	reset_lens(&unformatted_len, &result_len);
	while (*format)
	{
		while (*format && *format != '%')
			format++;
		unformatted_len = format - unformattedstart_ptr;
		result_len += unformatted_len;
		write(1, unformattedstart_ptr, unformatted_len);
		if (*format == '%')
		{
			format = formatinfo_parse_formatstr(&fi, (char *)++format);
			result_len += formatinfo_render_value(&fi, arglist);
		}
		unformattedstart_ptr = (char *)format;
	}
	va_end(arglist);
	return (result_len);
}
