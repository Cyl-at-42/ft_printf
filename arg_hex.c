#include "ft_printf.h"

int	render_arg_hex(t_formatinfo *format_info, char *buffer, va_list arglist)
{
	static const char	*hexstr = "0123456789abcdef";
	unsigned int		argint;
	int					i;

	argint = va_arg(arglist, unsigned int);
	format_info->converted_precisionpadding = format_info->useprecision;
	format_info->paddingchr = selint(format_info->useprecision, ' ',
			format_info->paddingchr);
	if (!argint)
		return (arg_int_0(format_info));
	i = 7;
	while (i >= 0 && argint)
	{
		buffer[i--] = hexstr[argint & 0xf];
		argint >>= 4;
	}
	format_info->converted_str = buffer + i + 1;
	format_info->converted_hexprefix[0] = format_info->hexprefix;
	format_info->converted_hexprefix[1] = 'x';
	return (7 - i);
}

int	render_arg_caphex(t_formatinfo *format_info, char *buffer, va_list arglist)
{
	static const char	*hexstr = "0123456789ABCDEF";
	unsigned int		argint;
	int					i;

	argint = va_arg(arglist, unsigned int);
	format_info->converted_precisionpadding = format_info->useprecision;
	format_info->paddingchr = selint(format_info->useprecision, ' ',
			format_info->paddingchr);
	if (!argint)
		return (arg_int_0(format_info));
	i = 7;
	while (i >= 0 && argint)
	{
		buffer[i--] = hexstr[argint & 0xf];
		argint >>= 4;
	}
	format_info->converted_str = buffer + i + 1;
	format_info->converted_hexprefix[0] = format_info->hexprefix;
	format_info->converted_hexprefix[1] = 'X';
	return (7 - i);
}

int	render_arg_hexptr(t_formatinfo *format_info, char *buffer, va_list arglist)
{
	static const char	*hexstr = "0123456789abcdef";
	unsigned long		argul;
	int					i;

	argul = (unsigned long) va_arg(arglist, void *);
	if (!argul)
	{
		format_info->paddingchr = ' ';
		format_info->converted_str = "(nil)";
		return (5);
	}
	format_info->converted_precisionpadding = format_info->useprecision;
	format_info->paddingchr = selint(format_info->useprecision, ' ',
			format_info->paddingchr);
	i = 15;
	while (i >= 0 && argul)
	{
		buffer[i--] = hexstr[argul & 0xf];
		argul >>= 4;
	}
	format_info->converted_hexprefix[0] = '0';
	format_info->converted_hexprefix[1] = 'x';
	format_info->converted_str = buffer + i + 1;
	return (15 - i);
}
