/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:51:48 by lkallio           #+#    #+#             */
/*   Updated: 2021/05/21 15:06:57 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

typedef struct s_dt
{
	int		param;
	int		width;
	int		prec;
	int		length;
	int		type;
	int		num_len;
	int		temp;
}					t_dt;

typedef struct s_pf
{
	t_dt			dt;
	char			buf[1024];
	char			*dst;
	int				buf_idx;
	int				n;
	const char		*format;
	char			*tempstr;
	unsigned is_sprintf : 1;
}					t_pf;

int					handle_double(t_pf *pf, va_list ap);
void				feedbuf_nchar(t_pf *pf, char ins, int n);
void				feedbuf_str(t_pf *pf, char *str, int len);
void				handle_buffer(t_pf *pf, char ins);
int					write_int(uintmax_t in, t_pf *pf, int base, int i);
int					ft_nstrchr(const char *pool, char c);
int					handle_str(t_pf *pf, va_list ap);
int					handle_uint(t_pf *pf, va_list ap);
int					handle_int(t_pf *pf, va_list ap);
int					handle_ptr(t_pf *pf, va_list ap);
int					ft_printf(char const *format, ...);
int					handle_n(t_pf *pf, va_list ap);
int					ft_nstrchr(const char *pool, char c);
int					pf_atoi(t_pf *pf, int *i, int ret);
int					handle_c(t_pf *pf, va_list ap);
int					handle_percent(t_pf *pf);
int					handle_longints(t_pf *pf, va_list ap);
int					ft_sprintf(char *str, char const *format, ...);
int					parse_quoted(t_pf *pf, va_list ap);
int					pf_width(t_pf *pf, int *i, va_list ap);

#endif
