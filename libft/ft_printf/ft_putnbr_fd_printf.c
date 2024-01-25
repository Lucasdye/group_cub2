/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:40:28 by sycourbi          #+#    #+#             */
/*   Updated: 2022/11/14 14:52:58 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static long int	ft_nbrlen(long int nb)
{
	long int	i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		i++;
		nb = nb * -1;
	}
	while (nb > 0)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

int	ft_putnbr_fd_printf(int n, int fd, int count)
{
	long int	nb;

	nb = (long)n;
	if (nb < 0 && nb != -2147483648)
	{
		count++;
		ft_putchar_fd('-', fd);
		nb = nb * -1;
	}
	if (nb == -2147483648)
		write(fd, "-2147483648", 11);
	if (nb >= 0 && nb <= 9)
		ft_putchar_fd(nb + '0', fd);
	if (nb > 9)
	{
		ft_putnbr_fd_printf(nb / 10, fd, count);
		ft_putchar_fd(nb % 10 + '0', fd);
	}
	return (count + ft_nbrlen(nb));
}
