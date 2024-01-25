/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <sycourbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:46:02 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/18 11:55:20 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//fonction copy split en tableau de int
int	*ajout_new_color(char *map)
{
	char	**split;
	int		*res;
	int		size;

	size = 0;
	split = ft_split(map, ',');
	if (!split)
		return (NULL);
	while (split[size])
		size++;
	if (size != 3)
		return (free_tab((void **)split), NULL);
	res = malloc(sizeof(int) * 3);
	if (!res)
		return (free_tab((void **)split), NULL);
	res[0] = ft_atoi(split[0]);
	res[1] = ft_atoi(split[1]);
	res[2] = ft_atoi(split[2]);
	free_tab((void **)split);
	return (res);
}

int	ajout_color(char *map, int j, t_text *texture)
{
	if (map[j] == 'F' && !texture->color_f)
		texture->color_f = ajout_new_color(map + j + 1);
	else if (map[j] == 'C' && !texture->color_c)
		texture->color_c = ajout_new_color(map + j + 1);
	else
		return (-1);
	return (0);
}
