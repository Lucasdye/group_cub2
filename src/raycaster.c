/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <sycourbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:46:59 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/18 12:55:40 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_dda(t_data *data)
{
	data->deltadist_x = fabs(1 / data->raydir_x);
	data->deltadist_y = fabs(1 / data->raydir_y);
	if (data->raydir_x < 0)
	{
		data->step_x = -1;
		data->sidedist_x = (data->pos_x - data->map_x) * data->deltadist_x;
	}
	else
	{
		data->step_x = 1;
		data->sidedist_x = (data->map_x + 1.0 - data->pos_x)
			* data->deltadist_x;
	}
	if (data->raydir_y < 0)
	{
		data->step_y = -1;
		data->sidedist_y = (data->pos_y - data->map_y) * data->deltadist_y;
	}
	else
	{
		data->step_y = 1;
		data->sidedist_y = (data->map_y + 1.0 - data->pos_y)
			* data->deltadist_y;
	}
}

void	dda(t_data *data)
{
	while (data->map_x >= 0 && data->map_y >= 0)
	{
		if (data->sidedist_x < data->sidedist_y)
		{
			data->sidedist_x += data->deltadist_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->sidedist_y += data->deltadist_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		if (data->map_fini[data->map_x][data->map_y]
			&& data->map_fini[data->map_x][data->map_y] > '0')
			break ;
	}
}

void	dessin(t_data *data)
{
	if (data->side == 0)
		data->wall_dist = (data->map_x - data->pos_x + (1 - data->step_x)
				/ 2) / data->raydir_x;
	else
		data->wall_dist = (data->map_y - data->pos_y + (1 - data->step_y)
				/ 2) / data->raydir_y;
	data->line_height = (int)(HEIGHT / data->wall_dist);
	data->draw_start = -data->line_height / 2 + HEIGHT / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + HEIGHT / 2;
	if (data->draw_end >= HEIGHT)
		data->draw_end = data->win_height - 1;
	if (data->side == 0)
		data->wall_x = data->pos_y + data->wall_dist * data->raydir_y;
	else
		data->wall_x = data->pos_x + data->wall_dist * data->raydir_x;
	data->wall_x -= floor(data->wall_x);
	data->tex_x = (int)(data->wall_x * (double)data->pixel_img);
	if (data->side == 0 && data->raydir_x > 0)
		data->tex_x = 64 - data->tex_x - 1;
	if (data->side == 1 && data->raydir_y < 0)
		data->tex_x = 64 - data->tex_x - 1;
}

int	raycaster(t_data *data)
{
	int		x;
	double	step;

	x = 0;
	while (x < WIDTH - 1)
	{
		data->map_x = (int)data->pos_x;
		data->map_y = (int)data->pos_y;
		data->camera_x = (double)(2 * x / (double)WIDTH - 1);
		data->raydir_x = data->dir_x + data->plane_x * data->camera_x;
		data->raydir_y = data->dir_y + data->plane_y * data->camera_x;
		init_dda(data);
		dda(data);
		dessin(data);
		step = (1.0 * 64 / data->line_height);
		dessin_img_tab(data, x, step);
		x++;
	}
	dessin_fini(data);
	return (0);
}
