#include "ft_printf.h"

char	*formatinfo_parse_flags(t_formatinfo *out_format_info, char *format)
{
	while ((*format == '+') || (*format == ' ') || (*format == '0')
		|| (*format == '#') || (*format == '-'))
	{
		if (*format == '+')
			out_format_info->plussign = '+';
		if (*format == ' ')
			out_format_info->plussign = ' ';
		if (*format == '0')
			out_format_info->paddingchr = '0';
		if (*format == '#')
			out_format_info->hexprefix = '0';
		if (*format == '-')
			out_format_info->leftalign = '-';
		format++;
	}
	if (out_format_info->leftalign)
		out_format_info->paddingchr = ' ';
	return (format);
}

char	*formatinfo_parse_width(t_formatinfo *format_info, char *format_str)
{
	if (*format_str >= '0' && *format_str <= '9')
		format_str = micro_atoi(&format_info->min_field_width, format_str);
	return (format_str);
}

char	*formatinfo_parse_precision(t_formatinfo *format_info, char *format_str)
{
	if (*format_str == '.')
	{
		format_str++;
		if (*format_str >= '0' && *format_str <= '9')
			format_str = micro_atoi(&format_info->precision, format_str);
		else
			format_info->precision = 0;
		format_info->useprecision = '.';
	}
	return (format_str);
}

char	*formatinfo_parse_type(t_formatinfo *format_info, char *format)
{
	static const char	*typeschrs = "%cdipsuxX";
	int					type;

	type = 0;
	while (typeschrs[type])
	{
		if (*format == typeschrs[type])
			break ;
		type++;
	}
	if (!typeschrs[type])
		type = 0;
	else
		type++;
	format_info->typecode = type;
	if (*format)
		format++;
	return (format);
}

char	*formatinfo_parse_formatstr(t_formatinfo *format_info, char *format_str)
{
	formatinfo_initdefaults(format_info, format_str);
	format_str = formatinfo_parse_flags(format_info, format_str);
	format_str = formatinfo_parse_width(format_info, format_str);
	format_str = formatinfo_parse_precision(format_info, format_str);
	format_str = formatinfo_parse_type(format_info, format_str);
	format_info->formatstr_end = format_str;
	return (format_str);
}
