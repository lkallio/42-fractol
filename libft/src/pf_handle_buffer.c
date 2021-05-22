/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:39:07 by lkallio           #+#    #+#             */
/*   Updated: 2021/05/21 14:46:59 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_buffer(t_pf *pf, char ins)
{
	if (pf->buf_idx == 1024)
	{
		if (pf->is_sprintf)
			memmove(pf->dst, pf->buf, 1024);
		else
			write(1, pf->buf, 1024);
		pf->n += 1024;
		pf->buf_idx = 0;
	}
	pf->buf[(pf->buf_idx)++] = ins;
}

void	feedbuf_str(t_pf *pf, char *str, int len)
{
	while (*str && len--)
		handle_buffer(pf, *str++);
}

void	feedbuf_nchar(t_pf *pf, char ins, int n)
{
	if (n < 0)
		return ;
	while (n--)
		handle_buffer(pf, ins);
}
