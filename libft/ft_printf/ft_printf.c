/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:57:58 by sycourbi          #+#    #+#             */
/*   Updated: 2022/11/24 12:32:46 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putnbr_fd_printf(int n, int fd, int count);

static int	ft_chars(char *s, int fd, int count)
{
	if (s == NULL)
		count = ft_putstr_fd_printf("(null)", fd, count);
	else
		count = ft_putstr_fd_printf(s, fd, count);
	return (count);
}

static int	ft_sign(const char *format, va_list ap, int count)
{
	if (*format == 'i' || *format == 'd')
		count = ft_putnbr_fd_printf(va_arg(ap, int), 1, count);
	else if (*format == '%')
	{
		count++;
		ft_putchar_fd('%', 1);
	}
	else if (*format == 's')
		count = ft_chars(va_arg(ap, char *), 1, count);
	else if (*format == 'c')
	{
		count++;
		ft_putchar_fd(va_arg(ap, int), 1);
	}
	else if (*format == 'u')
		count = ft_putunsigint_fd(va_arg(ap, unsigned int), 1, count);
	else
		count = ft_hexa(format, ap, count);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{	
			count = ft_sign(format + 1, ap, count);
			format = format + 2;
		}
		else if (*format != '%' && *format != '\0')
		{
			write(1, format, 1);
			count++;
			format++;
		}
	}
	va_end(ap);
	return (count);
}
