/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:58:02 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/26 14:16:09 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_data *data)
{
	data->dir = 0;
	data->movespeed = 0.099;
	data->rotspeed = 0.09;
	data->raydir_x = 0;
	data->raydir_y = 0;
	data->camera_x = 0;
	data->deltadist_x = 0;
	data->deltadist_y = 0;
	data->sidedist_x = 0;
	data->sidedist_y = 0;
	data->wall_x = 0;
	data->wall_dist = 0;
	data->step_x = 0;
	data->step_y = 0;
	data->tex_x = 0;
	data->side = 0;
	data->pixel_img = 64;
	data->line_height = 0;
	data->draw_start = 0;
	data->draw_end = 0;
}

void	init_img(t_img	*img)
{
	img->addr = NULL;
	img->img = NULL;
	img->endian = 0;
	img->bpp = 0;
	img->size_l = 0;
	img->img_height = 64;
	img->img_width = 64;
}

void	init_texture(t_text *texture)
{
	texture->color_c = NULL;
	texture->color_f = NULL;
	texture->text_north = NULL;
	texture->text_south = NULL;
	texture->text_east = NULL;
	texture->text_west = NULL;
}

int	init_data(t_data *data)
{
	if (!data)
		return (FAILED);
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->win_height = HEIGHT;
	data->win_width = WIDTH;
	data->name_file = NULL;
	data->map.copy_file = NULL;
	data->map.copy_map = NULL;
	data->text_pix = NULL;
	data->texture_nsew = NULL;
	// data->texture = malloc(sizeof(t_text));
	// if (!data->texture)
	// 	return (free(data), FAILED);
	init_texture(&data->texture);
	init_img(&data->img);
	return (SUCCESS);
}
