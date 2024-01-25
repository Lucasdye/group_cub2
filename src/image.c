/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <sycourbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:46:59 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/18 12:48:14 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_text_color(t_data *data)
{
	if (data->side == 0)
	{
		if (data->raydir_x < 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (data->raydir_y > 0)
			return (1);
		else
			return (0);
	}
}

void	dessin_img_tab(t_data *data, int x, double step)
{
	int		y;
	int		color;
	double	tex_pos;
	int		tex_y;
	int		index;

	index = get_text_color(data);
	tex_pos = (data->draw_start - HEIGHT / 2 + data->line_height / 2) * step;
	y = -1;
	while (++y < data->draw_start)
		data->tab[y][x] = data->rgb_c;
	y = data->draw_end - 1;
	while (++y < HEIGHT - 1)
		data->tab[y][x] = data->rgb_f;
	y = data->draw_start;
	while (y < data->draw_end - 1)
	{
		tex_y = (int)tex_pos & (64 -1);
		tex_pos += step;
		color = data->texture_nsew[index][64 * tex_y + data->tex_x];
		if (data->side == 1)
			color = (color >> 1) & 8355711;
		data->tab[y][x] = color;
		y++;
	}
}

int	load_image(t_data *data, int *texture, char *nsew, t_img *img)
{
	int	x;
	int	y;

	y = -1;
	img->img = mlx_xpm_file_to_image(data->mlx_ptr,
			nsew, &img->img_width, &img->img_height);
	if (!img->img)
		return (FAILED);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp,
			&img->size_l, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(data->mlx_ptr, img->img);
		return (FAILED);
	}
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			texture[img->img_width * y + x] = img->addr[img->img_width * y + x];
	}
	mlx_destroy_image(data->mlx_ptr, img->img);
	return (SUCCESS);
}

int	go_image(t_data *data)
{
	if (malloc_texture_nsew(data))
		return (FAILED);
	if (load_image(data, data->texture_nsew[0],
			data->texture->text_north, &data->img))
		return (FAILED);
	if (load_image(data, data->texture_nsew[1],
			data->texture->text_south, &data->img))
		return (FAILED);
	if (load_image(data, data->texture_nsew[2],
			data->texture->text_west, &data->img))
		return (FAILED);
	if (load_image(data, data->texture_nsew[3],
			data->texture->text_east, &data->img))
		return (FAILED);
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img.img)
		return (msg_err("Failed mlx_new_image"), FAILED);
	data->img.addr = (int *)mlx_get_data_addr(data->img.img,
			&data->img.bpp, &data->img.size_l, &data->img.endian);
	if (!data->img.addr)
		return (msg_err("Failed mlx_get_data_addr"), FAILED);
	return (SUCCESS);
}
