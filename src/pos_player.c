/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:46:59 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/19 14:06:59 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ajout_dir(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->dir = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] == ' ' || map[i][j] == '\t')
				j++;
			if (ft_strchr("01NSEW", map[i][j]) == NULL)
				return (msg_err("mauvais caratere dans la map"), FAILED);
			if (ft_strchr("NSEW", map[i][j]) && data->dir == 0)
				data->dir = map[i][j];
			else if (ft_strchr("NSEW", map[i][j]) && data->dir != 0)
				return (msg_err("Erreur direction player"), FAILED);
			j++;
		}
		i++;
	}
	if (data->dir == 0)
		return (msg_err("aucun player dans la map"), FAILED);
	return (SUCCESS);
}

void	ajout_dir_plane2(t_data *data, char c)
{
	if (c == 'E')
	{
		data->dir_x = 0;
		data->plane_x = 0.6;
		data->dir_y = 0.99;
		data->plane_y = 0;
	}
	if (c == 'W')
	{
		data->dir_x = 0;
		data->plane_x = -0.6;
		data->dir_y = -0.99;
		data->plane_y = 0;
	}
}

void	ajout_dir_plane(t_data *data, char c)
{
	if (c == 'N')
	{
		data->dir_x = -0.99;
		data->plane_x = 0;
		data->dir_y = 0;
		data->plane_y = 0.6;
	}
	if (c == 'S')
	{
		data->dir_x = 0.99;
		data->plane_x = 0;
		data->dir_y = 0;
		data->plane_y = -0.6;
	}
	if (c == 'E' || c == 'W')
		ajout_dir_plane2(data, c);
}

void	ajout_pos_player(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				data->pos_x = (double)i + 0.5;
				data->pos_y = (double)j + 0.5;
				ajout_dir_plane(data, map[i][j]);
				map[i][j] = 0;
			}
			j++;
		}
		i++;
	}
}

int	check_pos_player(char **map, t_data *data)
{
	if (ajout_dir(map, data))
		return (FAILED);
	if (data->dir == 0)
		return (msg_err("Erreur direction player"), FAILED);
	return (SUCCESS);
}
