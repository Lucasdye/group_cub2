/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:01:59 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/29 14:14:20 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	nbr_line_map(char **map, int i, int j)
{
	int	start;

	start = i;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\r')
			j++;
		if (map[i][j] != '1')
			return (0);
		i++;
	}
	return (i - start);
}

int	size_big_line(char **file, int i)
{
	int	res;

	res = ft_strlen(file[i]);
	while (file[i])
	{
		if (res < (int)ft_strlen(file[i]))
			res = ft_strlen(file[i]);
		i++;
	}
	return (res);
}

int	check_char_tab(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j] != NULL)
	{
		while (map[j][i])
		{
			if (map[j][i] == '\t')
				return ((void)ft_printf("ERROR: tab found at [%d][%d]\n", j, i)
					, FAILED);
			i++;
		}
		i = 0;
		j++;
	}
	return (SUCCESS);
}

int	ajout_map(char **file, int start, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->map.map_width = size_big_line(file, start);
	while (++i < data->map.map_height)
	{
		j = 0;
		data->map.copy_map[i] = malloc(sizeof(char)
				* (ft_strlen(data->map.copy_file[start]) + 1));
		if (!data->map.copy_file[i])
			return (msg_err("probleme malloc"), -3);
		while (file[start][j] && file[start][j] != '\n')
		{
			data->map.copy_map[i][j] = file[start][j];
			j++;
		}
		data->map.copy_map[i][j] = '\0';
		start++;
	}
	data->map.copy_map[i] = NULL;
	if (check_char_tab(data->map.copy_map))
		return (-1);
	return (2);
}

int	creat_map(char **copy_file, int i, int j, t_data *data)
{
	data->map.map_height = nbr_line_map(copy_file, i, j);
	if (data->map.map_height == 0)
		return (-1);
	data->map.copy_map = malloc(sizeof(char *) * (data->map.map_height + 1));
	if (!data->map.copy_map)
		return (msg_err("probleme de map"), -3);
	return (ajout_map(copy_file, i, data));
}
