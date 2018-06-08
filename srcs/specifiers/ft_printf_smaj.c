/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_smaj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 02:44:43 by lterrail          #+#    #+#             */
/*   Updated: 2018/05/31 15:52:23 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_wstrlen(t_printf *pf, int *str)
{
	int i;

	i = 0;
	while (*str)
	{
		if ((*str >= 0xD800 && *str <= 0xDB7F) ||
		(*str >= 0xDC00 && *str <= 0xDFFF))
			return (pf->printed = -1);
		if (*str <= 0x7F && (pf->precision == 0 || (i + 1 <= pf->precision)))
			i++;
		else if (*str <= 0x7FF && (pf->precision == 0 ||
		(i + 2 <= pf->precision)))
			i += 2;
		else if (*str <= 0xFFFF && (pf->precision == 0 ||
		(i + 3 <= pf->precision)))
			i += 3;
		else if (*str <= 0x10FFFF && (pf->precision == 0 ||
		(i + 4 <= pf->precision)))
			i += 4;
		str++;
	}
	return (i);
}

static void	ft_pputnwstr(int *str, int len)
{
	int	i;

	i = 0;
	while (*str && i < len)
	{
		if (*str <= 0x7F)
			i++;
		else if (*str <= 0x7FF)
			i += 2;
		else if (*str <= 0xFFFF)
			i += 3;
		else if (*str <= 0x10FFFF)
			i += 4;
		if (i <= len)
			ft_pputwchar(*str++);
	}
}

int			ft_printf_smaj(t_printf *pf)
{
	int				len;
	int				*str;

	str = va_arg(pf->ap, int *);
	if (str == NULL)
		str = L"(null)";
	if ((len = ft_wstrlen(pf, str)) == -1)
		return (EXIT_ERROR);
	pf->printed += len;
	if (pf->moins == 0 && pf->width > 0)
		ft_pputnchar(pf, ' ', pf->width - len);
	if (pf->moins == 0 && pf->zero > 0)
		ft_pputnchar(pf, '0', pf->zero - len);
	ft_pputnwstr(str, len);
	if (pf->moins > 0 && pf->width > 0)
		ft_pputnchar(pf, ' ', pf->width - len);
	if (pf->moins > 0 && pf->zero > 0)
		ft_pputnchar(pf, '0', pf->zero - len);
	return (EXIT_SUCCESS);
}
