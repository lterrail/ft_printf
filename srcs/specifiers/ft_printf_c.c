/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 17:49:03 by lterrail          #+#    #+#             */
/*   Updated: 2018/05/31 16:26:21 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_c(t_printf *pf)
{
	char	c[2];

	c[0] = (char)va_arg(pf->ap, int);
	c[1] = '\0';
	if (pf->zero > 0)
	{
		pf->zero = pf->zero - 1;
		ft_pputnchar(pf, '0', pf->zero);
	}
	if (pf->moins == 0 && pf->width > 0)
		ft_pputnchar(pf, ' ', pf->width - 1);
	pf->printed += write(1, &c[0], 1);
	if (pf->moins > 0 && pf->width > 0)
		ft_pputnchar(pf, ' ', pf->width - 1);
	return (EXIT_SUCCESS);
}

static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

void		ft_pputwchar(unsigned int wc)
{
	if (wc <= 127)
		ft_putchar(wc);
	else if (wc <= 2047)
	{
		ft_putchar((wc >> 6) + 0xC0);
		ft_putchar((wc & 0x3F) + 0x80);
	}
	else if (wc <= 65535)
	{
		ft_putchar((wc >> 12) + 0xE0);
		ft_putchar(((wc >> 6) & 0x3F) + 0x80);
		ft_putchar((wc & 0x3F) + 0x80);
	}
	else if (wc <= 1114111)
	{
		ft_putchar((wc >> 18) + 0xF0);
		ft_putchar(((wc >> 12) & 0x3F) + 0x80);
		ft_putchar(((wc >> 6) & 0x3F) + 0x80);
		ft_putchar((wc & 0x3F) + 0x80);
	}
}

static int	ft_wchrlen(t_printf *pf, unsigned int chr, int len)
{
	if ((chr >= 0xD800 && chr <= 0xDB7F) || (chr >= 0xDC00 && chr <= 0xDFFF))
	{
		pf->printed = -1;
		return (EXIT_ERROR);
	}
	if (chr <= 0x7F)
		len = 1;
	else if (chr <= 0x7FF)
		len = 2;
	else if (chr <= 0xFFFF)
		len = 3;
	else if (chr <= 0x10FFFF)
		len = 4;
	else
	{
		pf->printed = -1;
		return (EXIT_ERROR);
	}
	return (len);
}

int			ft_printf_cmaj(t_printf *pf)
{
	unsigned int	chr;
	int				len;

	len = 0;
	chr = va_arg(pf->ap, unsigned int);
	if ((len = ft_wchrlen(pf, chr, len)) == -1)
		return (pf->printed = -1);
	pf->printed += len;
	if ((size_t)len > MB_CUR_MAX)
	{
		pf->printed = -1;
		return (EXIT_ERROR);
	}
	if (pf->moins == 0 && pf->width > 0)
		ft_pputnchar(pf, ' ', pf->width - len);
	ft_pputwchar(chr);
	if (pf->moins > 0 && pf->width > 0)
		ft_pputnchar(pf, ' ', pf->width - len);
	return (EXIT_SUCCESS);
}
