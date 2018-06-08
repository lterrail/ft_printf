/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:15:14 by lterrail          #+#    #+#             */
/*   Updated: 2018/06/01 19:39:34 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TEST1 0x11ffff
#define TEST2 2147483647
#define TEST3 -12345

#include "includes/ft_printf.h"
#include <stdio.h>
#include <locale.h>

int		main(void)
{
	int ret;
	ret = ft_printf("{%d}\n", 40);
	ret += 1;
	return (0);
}
