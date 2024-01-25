/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:38:38 by sycourbi          #+#    #+#             */
/*   Updated: 2023/03/01 15:38:42 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strlen_gnl(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strrchr_gnl(char *s, int c)
{
	int	len;

	len = ft_strlen_gnl(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return (1);
		else
			len--;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!s3)
		return (NULL);
	while (s1 && s1[++j])
		s3[++i] = s1[j];
	j = -1;
	while (s2 && s2[++j])
		s3[++i] = s2[j];
	s3[++i] = '\0';
	if (s1)
		free(s1);
	return (s3);
}
