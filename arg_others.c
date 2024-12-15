#include "ft_printf.h"

int	render_arg_invalid(t_formatinfo *format_info, char *buffer, va_list arglist)
{
	size_t	len;

	(void) arglist;
	buffer[0] = 0;
	format_info->converted_str = format_info->formatstr_start - 1;
	len = format_info->formatstr_end - format_info->formatstr_start + 1;
	return (len);
}

int	render_arg_string(t_formatinfo *format_info, char *buffer, va_list arglist)
{
	char	*argstr;
	size_t	argstr_len;

	argstr = va_arg(arglist, char *);
	buffer[0] = 0;
	format_info->paddingchr = selint(format_info->useprecision, ' ',
			format_info->paddingchr);
	if (!argstr)
	{
		if (format_info->useprecision && format_info->precision <= 5)
			return (0);
		format_info->paddingchr = ' ';
		format_info->converted_str = "(null)";
		return (6);
	}
	argstr_len = ft_strlen(argstr);
	format_info->converted_str = argstr;
	if (format_info->useprecision)
	{
		if ((int) argstr_len > format_info->precision)
			return (format_info->precision);
	}
	return (argstr_len);
}

int	render_arg_percent(t_formatinfo *format_info, char *buffer, va_list arglist)
{
	(void) arglist;
	buffer[0] = '%';
	format_info->min_field_width = 0;
	format_info->converted_str = buffer;
	return (1);
}

int	render_arg_chr(t_formatinfo *out_format_info, char *buffer, va_list arglist)
{
	buffer[0] = (char)va_arg(arglist, int);
	out_format_info->converted_str = buffer;
	return (1);
}
