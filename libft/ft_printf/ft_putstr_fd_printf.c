/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:23:43 by sycourbi          #+#    #+#             */
/*   Updated: 2022/11/22 15:08:09 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putstr_fd_printf(char *s, int fd, int count)
{
	if (!s)
		return (0);
	while (*s)
	{
		count++;
		write(fd, s, 1);
		s++;
	}
	return (count);
}
