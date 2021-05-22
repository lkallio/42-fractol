/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:35:06 by lkallio           #+#    #+#             */
/*   Updated: 2021/05/22 13:39:07 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_sprintf(char *str, char const *format, ...)
{
	t_pf	pf;
	va_list	ap;

	va_start(ap, format);
	pf = (t_pf){.dt = {0, -1, -1, 0, 0, 0, 0}, .buf = {0},
		.buf_idx = 0, .n = 0, .format = format, .tempstr = 0,
		.is_sprintf = 1, .dst = str};
	parse_quoted(&pf, ap);
	va_end(ap);
	return (pf.n + pf.buf_idx);
}
