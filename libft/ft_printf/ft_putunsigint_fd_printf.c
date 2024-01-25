/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigint_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:43:29 by sycourbi          #+#    #+#             */
/*   Updated: 2022/11/30 11:47:36 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static unsigned int	ft_nbrlen(unsigned int nb)
{
	unsigned int	i;

	i = 0;
	if (nb < 1)
		return (1);
	while (nb > 0)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

int	ft_putunsigint_fd(unsigned int u, int fd, int count)
{
	if (u <= 9)
		ft_putchar_fd(u + '0', fd);
	if (u > 9)
	{
		ft_putunsigint_fd(u / 10, fd, count);
		ft_putchar_fd(u % 10 + '0', fd);
	}
	return (count + ft_nbrlen(u));
}
