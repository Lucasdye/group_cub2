/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <sycourbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:10:39 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/18 12:53:32 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_first(char **map, int i)
{
	int	j;

	j = 0;
	if (!map)
		return (FAILED);
	while (map[i][j] && (map[i][j] == ' ' || map[i][j] == '\t'
		|| map[i][j] == '\r'))
	{
		j++;
	}	
	while (map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\t')
			return (msg_err("ERREUR MAP"), 1);
		j++;
	}
	return (0);
}

int	check_wall(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 1;
	if (check_first(data->map.copy_map, 0))
		return (FAILED);
	while (i < (data->map.map_height -1))
	{
		j = 0;
		while (map[i][j] && (map[i][j] == ' ' || map[i][j] == '\t'))
		{
			j++;
		}
		if (map[i][j] != '1')
			return (FAILED);
		j = (ft_strlen(map[i]) - 1);
		while (map[i][j] && (map[i][j] == ' ' || map[i][j] == '\t'))
			j--;
		if (map[i][j] != '1')
			return (FAILED);
		i++;
	}
	if (check_first(map, i))
		return (FAILED);
	return (SUCCESS);
}

int	verif_autour(char **map, int i, int j)
{
	if (map[i - 1][j] == ' ' || map[i - 1][j] == '\t' || map[i - 1][j] == '\0' )
		return (FAILED);
	if (map[i + 1][j] == ' ' || map[i + 1][j] == '\t' || map[i + 1][j] == '\0' )
		return (FAILED);
	if (map[i][j - 1] == ' ' || map[i][j - 1] == '\t' || map[i][j - 1] == '\0')
		return (FAILED);
	if (map[i][j + 1] == ' ' || map[i][j + 1] == '\t' || map[i][j + 1] == '\0')
		return (FAILED);
	return (SUCCESS);
}

int	verif_wall(char **map, int i, int j)
{
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (verif_autour(map, i, j))
					return (FAILED);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_verif_map(t_data *data, char **map)
{
	if (check_wall(map, data))
		return (msg_err("erreur map"), FAILED);
	if (verif_wall(map, 0, 0))
		return (msg_err("erreur MAP"), FAILED);
	if (check_pos_player(map, data))
		return (FAILED);
	return (SUCCESS);
}
