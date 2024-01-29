/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_map_carre.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:49:44 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/29 14:18:02 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	change_whitespace(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.map_height && data->map.copy_map[i])
	{
		j = 0;
		while (j < (int)ft_strlen(data->map.copy_map[i]))
		{
			if (data->map.copy_map[i][j] != '0' && data->map.copy_map[i][j]
				!= '1' && data->map.copy_map[i][j] != 'N'
				&& data->map.copy_map[i][j] != 'S'
				&& data->map.copy_map[i][j] != 'E'
				&& data->map.copy_map[i][j] != 'W'
				&& data->map.copy_map[i][j] != '\0')
				data->map_fini[i][j] = '1';
			else
				data->map_fini[i][j] = data->map.copy_map[i][j];
			j++;
		}
		data->map_fini[i][j] = '\0';
		i++;
	}
	data->map_fini[i] = NULL;
}

int	creat_map_carre(t_data *data)
{
	int	i;

	i = 0;
	data->map.map_height = nbr_line_map(data->map.copy_map, 0, 0);
	data->map_fini = malloc(sizeof(char *) * (data->map.map_height + 1));
	if (!data->map_fini)
		return (FAILED);
	data->map.map_width = size_big_line(data->map.copy_map, 0);
	while (i < data->map.map_height)
	{
		data->map_fini[i] = malloc(sizeof(char) * data->map.map_width + 1);
		if (!data->map_fini[i])
			return (FAILED);
		i++;
	}
	data->map_fini[i] = NULL;
	change_whitespace(data);
	return (SUCCESS);
}
