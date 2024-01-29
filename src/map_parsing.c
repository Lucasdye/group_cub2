/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:43:57 by lbouguet          #+#    #+#             */
/*   Updated: 2024/01/29 14:20:34 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	only_one_player(char **map)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (map[j])
	{
		while (map[j][i])
		{
			if (is_player(map[j][i]) == 1)
			{
				if (flag == 1)
					return (FAILED);
				else
					flag = 1;
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (SUCCESS);
}

int	trash_detector(char **copy_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (copy_map[j])
	{
		while (copy_map[j][i])
		{
			if (copy_map[j][i] != '0' && copy_map[j][i] != '1')
			{
				if (copy_map[j][i] != 'N' && copy_map[j][i] != 'S')
				{
					if (copy_map[j][i] != 'W' && copy_map[j][i] != 'E'
							&& copy_map[j][i] != ' ')
						return (FAILED);
				}
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (SUCCESS);
}

int	is_map_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '0' || is_player(map[j][i]))
			{
				if (detect_walls(i, j, map) == FAILED)
					return (FAILED);
			}
			i++;
		}
		j++;
	}
	return (SUCCESS);
}

int	map_parsing(t_data *data, char ***copy_map, char *path)
{
	(void)path;
	(void)copy_map;
	if (trash_detector(*copy_map))
		return ((void)ft_printf("Error: trash detected\n"), FAILED);
	if (only_one_player(data->map.copy_map) == FAILED)
		return ((void)ft_printf("Error: two player found\n"), FAILED);
	if (is_map_closed(data->map.copy_map) == FAILED)
		return ((void)ft_printf("Error: map unclosed !\n"), FAILED);
	return (SUCCESS);
}
