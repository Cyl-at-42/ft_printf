#include "ft_printf.h"

int	arg_int_specific(t_formatinfo *out_format_info, int argint)
{
	if (argint == -2147483648)
	{
		out_format_info->converted_str = "2147483648";
		out_format_info->converted_sign = '-';
		return (10);
	}
	return (0);
}

int	arg_int_0(t_formatinfo *format_info)
{
	format_info->converted_str = "0";
	format_info->converted_sign = format_info->plussign;
	if (format_info->useprecision && format_info->precision == 0)
		return (0);
	return (1);
}

int	render_arg_int(t_formatinfo *fi, char *buffer, va_list arglist)
{
	int	argint;
	int	i;
	int	isneg;

	argint = va_arg(arglist, int);
	fi->converted_precisionpadding = fi->useprecision;
	fi->paddingchr = selint(fi->useprecision, ' ', fi->paddingchr);
	if (!argint)
		return (arg_int_0(fi));
	i = arg_int_specific(fi, argint);
	if (i)
		return (i);
	isneg = (argint < 0);
	if (isneg)
		argint *= -1;
	i = 9;
	while (argint)
	{
		buffer[i--] = '0' + argint % 10;
		argint /= 10;
	}
	fi->converted_sign = selint(isneg, fi->converted_sign = '-', fi->plussign);
	fi->converted_str = buffer + i + 1;
	return (9 - i);
}

int	render_arg_uint(t_formatinfo *format_info, char *buffer, va_list arglist)
{
	unsigned int	argint;
	int				i;

	format_info->converted_precisionpadding = format_info->useprecision;
	format_info->paddingchr = selint(format_info->useprecision, ' ',
			format_info->paddingchr);
	argint = va_arg(arglist, unsigned int);
	if (!argint)
		return (arg_int_0(format_info));
	i = 9;
	while (argint)
	{
		buffer[i--] = '0' + argint % 10;
		argint /= 10;
	}
	buffer[10] = 0;
	format_info->converted_str = buffer + i + 1;
	return (9 - i);
}
