/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:55:54 by sycourbi          #+#    #+#             */
/*   Updated: 2023/03/28 17:31:02 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"

# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_putstr_fd_printf(char *s, int fd, int count);
int	ft_putnbr_fd_printf(int n, int fd, int count);
int	ft_putunsigint_fd(unsigned int u, int fd, int count);
int	ft_hexa(const char *format, va_list ap, int count);

#endif
