/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:51:55 by sycourbi          #+#    #+#             */
/*   Updated: 2022/12/08 12:54:57 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static long int	ft_nbrlen(unsigned long nb)
{
	long int	i;

	i = 0;
	if (nb < 1)
		return (1);
	while (nb != 0)
	{
		i++;
		nb = nb / 16;
	}
	return (i);
}

static int	ft_putnbr_hexa(unsigned long nbr, char *base, int count)
{
	if (nbr < 16)
	{
		ft_putchar_fd(base[nbr], 1);
	}
	if (nbr >= 16)
	{
		ft_putnbr_hexa(nbr / 16, base, count);
		ft_putchar_fd(base[nbr % 16], 1);
	}
	return (count + ft_nbrlen(nbr));
}

static int	ft_putvoid_hexa(unsigned long nbr, char *base, int count)
{
	if (!nbr)
	{
		count = ft_putstr_fd_printf("(nil)", 1, count);
		return (count);
	}
	if (nbr)
		count = ft_putstr_fd_printf("0x", 1, count);
	count = ft_putnbr_hexa(nbr, base, count);
	return (count);
}

int	ft_hexa(const char *format, va_list ap, int count)
{
	char	*basemin;
	char	*basemaj;

	basemin = "0123456789abcdef";
	basemaj = "0123456789ABCDEF";
	if (*format == 'x')
		count = ft_putnbr_hexa((unsigned int) va_arg(ap, int), basemin, count);
	if (*format == 'X')
		count = ft_putnbr_hexa((unsigned int) va_arg(ap, int), basemaj, count);
	if (*format == 'p')
		count = ft_putvoid_hexa(va_arg(ap, unsigned long),
				basemin, count);
	return (count);
}
