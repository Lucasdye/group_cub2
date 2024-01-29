/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:46:02 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/29 14:23:17 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_color_definition(char *color_def)
{
	int	count_comas;
	int	count_numbers;

	count_comas = 0;
	count_numbers = 0;
	color_def++;
	while (*color_def != '\n')
	{
		if ((*color_def >= 48 && *color_def <= 57) || *color_def == ',')
		{
			if (*color_def == ',')
				count_comas++;
			else if ((*color_def >= 48 && *color_def <= 57))
				count_numbers++;
		}
		else
			return (FAILED);
		color_def++;
	}
	if (count_comas != 2 || count_numbers > 9)
		return (FAILED);
	return (SUCCESS);
}

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
	{
		if (check_color_definition(map + j + 1) == FAILED)
			return (-1);
		texture->color_f = ajout_new_color(map + j + 1);
	}
	else if (map[j] == 'C' && !texture->color_c)
	{
		if (check_color_definition(map + j + 1) == FAILED)
			return (-1);
		texture->color_c = ajout_new_color(map + j + 1);
	}
	else
		return (-1);
	return (0);
}
