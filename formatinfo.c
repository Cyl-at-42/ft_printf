#include "ft_printf.h"

int	write_padding(int repeat, char chr)
{
	int	i;

	i = repeat;
	while (i--)
		write(1, &chr, 1);
	return (repeat);
}

void	formatinfo_initdefaults(t_formatinfo *format_info, char *format)
{
	format_info->formatstr_start = format;
	format_info->min_field_width = 0;
	format_info->precision = 1;
	format_info->converted_precisionpadding = 0;
	format_info->hexprefix = 0;
	format_info->paddingchr = ' ';
	format_info->plussign = 0;
	format_info->leftalign = 0;
	format_info->useprecision = 0;
	format_info->converted_sign = 0;
	format_info->converted_hexprefix[0] = 0;
}

void	formatinfo_calculate_paddings(t_formatinfo *format_info,
	int converted_len)
{
	int	padding_total;
	int	padding_precision;

	padding_total = format_info->min_field_width - converted_len;
	if (format_info->converted_sign)
		padding_total--;
	if (format_info->converted_hexprefix[0])
		padding_total -= 2;
	format_info->padding_zero = 0;
	format_info->padding_spc = 0;
	padding_precision = 0;
	if (format_info->converted_precisionpadding)
	{
		padding_precision = format_info->precision - converted_len;
		if (padding_precision < 0)
			padding_precision = 0;
	}
	format_info->padding_spc = padding_total - padding_precision;
	format_info->padding_zero = padding_precision;
	if (!format_info->leftalign && format_info->paddingchr == '0')
	{
		format_info->padding_spc = 0;
		format_info->padding_zero = padding_total;
	}
}

int	formatinfo_render_value(t_formatinfo *format_info, va_list arglist)
{
	static int	(*raf[10])(t_formatinfo*, char*, va_list) = {
		render_arg_invalid, render_arg_percent, render_arg_chr, render_arg_int,
		render_arg_int, render_arg_hexptr, render_arg_string, render_arg_uint,
		render_arg_hex, render_arg_caphex};
	char		converted_value_buffer[20];
	int			len;
	int			converted_len;

	converted_len = raf[format_info->typecode](format_info,
			converted_value_buffer, arglist);
	formatinfo_calculate_paddings(format_info, converted_len);
	len = 0;
	if (format_info->padding_spc > 0 && !format_info->leftalign)
		len += write_padding(format_info->padding_spc, ' ');
	if (format_info->converted_sign)
		len += write(1, &format_info->converted_sign, 1);
	if (format_info->converted_hexprefix[0])
		len += write(1, &format_info->converted_hexprefix[0], 2);
	if (format_info->padding_zero > 0)
		len += write_padding(format_info->padding_zero, '0');
	if (converted_len)
		len += write(1, format_info->converted_str, converted_len);
	if (format_info->padding_spc > 0 && format_info->leftalign)
		len += write_padding(format_info->padding_spc, ' ');
	return (len);
}
