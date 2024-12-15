#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_formatinfo
{
	char	*formatstr_start;
	char	*formatstr_end;
	char	*converted_str;
	int		min_field_width;
	int		precision;
	int		typecode;
	int		converted_precisionpadding;
	char	plussign;
	char	paddingchr;
	char	leftalign;
	char	hexprefix;
	char	useprecision;
	char	converted_sign;
	char	converted_hexprefix[2];
	int		padding_zero;
	int		padding_spc;
}	t_formatinfo;

size_t	ft_strlen(char *s);
int		selint(int condition, int trueval, int falseval);
char	*micro_atoi(int *int_ptr, char *str);
void	reset_lens(size_t *len1, size_t *len2);
void	formatinfo_initdefaults(t_formatinfo *format_info, char *format);
void	formatinfo_calculate_paddings(t_formatinfo *format_info,
			int converted_len);
int		formatinfo_render_value(t_formatinfo *format_info, va_list arglist);
char	*formatinfo_parse_formatstr(t_formatinfo *format_info,
			char *format_str);
int		arg_int_0(t_formatinfo *format_info);
int		render_arg_int(t_formatinfo *format_info, char *buffer,
			va_list arglist);
int		render_arg_uint(t_formatinfo *format_info, char *buffer,
			va_list arglist);
int		render_arg_hex(t_formatinfo *format_info, char *buffer,
			va_list arglist);
int		render_arg_caphex(t_formatinfo *format_info, char *buffer,
			va_list arglist);
int		render_arg_hexptr(t_formatinfo *format_info, char *buffer,
			va_list arglist);
int		render_arg_invalid(t_formatinfo *format_info, char *buffer,
			va_list arglist);
int		render_arg_string(t_formatinfo *format_info, char *buffer,
			va_list arglist);
int		render_arg_percent(t_formatinfo *format_info, char *buffer,
			va_list arglist);
int		render_arg_chr(t_formatinfo *out_format_info, char *buffer,
			va_list arglist);
int		ft_printf(const char *format, ...);

#endif
