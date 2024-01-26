/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:46:59 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/26 15:54:39 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	dessin_fini(t_data *data)
{
	int	y;
	int	x;

	mlx_destroy_image(data->mlx_ptr, data->img.img);
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			data->img.addr[y * WIDTH + x] = data->tab[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}

int	render(t_data *data)
{
	raycaster(data);
	return (0);
}

int	start_mlx(t_data *data)
{
	init_ray(data);
	ajout_pos_player(data->map_fini, data);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (ft_delete(data), msg_err("Failed mlx_init"), FAILED);
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1080, 720, "Cub3D");
	if (!data->win_ptr)
		return (all_free(data), msg_err("Failed mlx_new_window"), FAILED);
	if (go_image(data) == FAILED)
		return (all_free(data), msg_err("Failed go_image"), FAILED);
	mlx_loop_hook(data->mlx_ptr, render, data);
	mlx_hook(data->win_ptr, 17, 0, mlx_loop_end, data->mlx_ptr);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, keypress, data);
	mlx_loop(data->mlx_ptr);
	all_free(data);
	return (SUCCESS);
}
