/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:17:03 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/26 14:05:07 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	haut(t_data *data)
{
	if ((data->pos_x + data->dir_x * data->movespeed) > 0
		&& data->map_fini[(int)(data->pos_x + data->dir_x
			* data->movespeed)][(int)data->pos_y] != '1')
		data->pos_x += data->dir_x * data->movespeed;
	if ((data->pos_y + data->dir_y * data->movespeed) > 0
		&& (int)data->map_fini[(int)data->pos_x][(int)
		(data->pos_y + data->dir_y * data->movespeed)] != '1')
		data->pos_y += data->dir_y * data->movespeed;
}

void	bas(t_data *data)
{
	if ((data->pos_x - data->dir_x * data->movespeed) > 0
		&& data->map_fini[(int)(data->pos_x - data->dir_x
			* data->movespeed)][(int)data->pos_y] != '1')
		data->pos_x -= data->dir_x * data->movespeed;
	if ((data->pos_y - data->dir_y * data->movespeed) > 0
		&& data->map_fini[(int)data->pos_x][(int)(data->pos_y
		- data->dir_y * data->movespeed)] != '1')
		data->pos_y -= data->dir_y * data->movespeed;
}

void	droite(t_data *data)
{
	if ((data->pos_x + data->dir_y * data->movespeed) > 0
		&& data->map_fini[(int)(data->pos_x + data->dir_y
			* data->movespeed)][(int)data->pos_y] != '1')
		data->pos_x += data->dir_y * data->movespeed;
	if ((data->pos_y - data->dir_x * data->movespeed) > 0
		&& data->map_fini[(int)data->pos_x][(int)(data->pos_y
		- data->dir_x * data->movespeed)] != '1')
		data->pos_y -= data->dir_x * data->movespeed;
}

void	gauche(t_data *data)
{
	if ((data->pos_x - data->dir_y * data->movespeed) > 0
		&& data->map_fini[(int)(data->pos_x - data->dir_y
			* data->movespeed)][(int)data->pos_y] != '1')
		data->pos_x -= data->dir_y * data->movespeed;
	if ((data->pos_y + data->dir_x * data->movespeed) > 0
		&& data->map_fini[(int)data->pos_x][(int)(data->pos_y
		+ data->dir_x * data->movespeed)] != '1')
		data->pos_y += data->dir_x * data->movespeed;
}
