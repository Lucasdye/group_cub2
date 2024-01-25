/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <sycourbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:32:54 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/18 12:03:13 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	msg_err(char *str)
{
	write(2, "cub3d error: ", 13);
	if (str)
		write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	free_texture(t_text *texture)
{
	if (!texture)
		return ;
	if (texture->text_north)
		free(texture->text_north);
	if (texture->text_east)
		free(texture->text_east);
	if (texture->text_south)
		free(texture->text_south);
	if (texture->text_west)
		free(texture->text_west);
	if (texture->color_c)
		free(texture->color_c);
	if (texture->color_f)
		free(texture->color_f);
	if (texture)
		free(texture);
}

void	free_map(t_map	*map)
{
	if (map->fd)
		close(map->fd);
	if (map->copy_file)
		free_tab((void **)map->copy_file);
	if (map->copy_map)
		free_tab((void **)map->copy_map);
}

void	ft_delete(t_data *data)
{
	if (data->name_file)
		free(data->name_file);
	if (data->text_pix)
		free_tab((void **)data->text_pix);
	if (data->map_fini)
		free_tab((void **)data->map_fini);
	if (data->texture_nsew)
		free_tab((void **)data->texture_nsew);
	free_map(&data->map);
	free_texture(data->texture);
	free(data);
}

void	all_free(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx_ptr, data->img.img);
	if (data->win_ptr != NULL)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (data->mlx_ptr != NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
	ft_delete(data);
}
