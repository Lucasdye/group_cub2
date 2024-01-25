/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <sycourbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:27:55 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/18 12:31:27 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_camera_droite(t_data *data)
{
	double	old;

	old = data->dir_x;
	data->dir_x = data->dir_x * cos(-data->rotspeed)
		- data->dir_y * sin(-data->rotspeed);
	data->dir_y = old * sin(-data->rotspeed)
		+ data->dir_y * cos(-data->rotspeed);
	old = data->plane_x;
	data->plane_x = data->plane_x * cos(-data->rotspeed)
		- data->plane_y * sin(-data->rotspeed);
	data->plane_y = old * sin(-data->rotspeed)
		+ data->plane_y * cos(-data->rotspeed);
}

void	move_camera_gauche(t_data *data)
{
	double	old;

	old = data->dir_x;
	data->dir_x = data->dir_x * cos(data->rotspeed)
		- data->dir_y * sin(data->rotspeed);
	data->dir_y = old * sin(data->rotspeed)
		+ data->dir_y * cos(data->rotspeed);
	old = data->plane_x;
	data->plane_x = data->plane_x * cos(data->rotspeed)
		- data->plane_y * sin(data->rotspeed);
	data->plane_y = old * sin(data->rotspeed)
		+ data->plane_y * cos(data->rotspeed);
}

int	keypress(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		mlx_loop_end(data->mlx_ptr);
	}
	if (key == XK_w)
		haut(data);
	if (key == XK_s)
		bas(data);
	if (key == XK_d)
		droite(data);
	if (key == XK_a)
		gauche(data);
	if (key == XK_Right)
		move_camera_droite(data);
	if (key == XK_Left)
		move_camera_gauche(data);
	return (0);
}
