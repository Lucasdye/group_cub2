/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:49:44 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/24 16:28:26 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_extension(char *str)
{
	int	i;
	int	fd;

	dprintf(2, BLUE "check_extension()\n" RESET_COLOR);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (msg_err("error open fd"), FAILED);
	close (fd);
	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] != 'b' || str[i - 2] != 'u'
		|| str[i - 3] != 'c' || str[i - 4] != '.')
		return (msg_err("extension .cub demande"), FAILED);
	return (SUCCESS);
}

int	check_arg(char *av, t_data *data)
{
	dprintf(2, BLUE "check_arg()\n" RESET_COLOR);
	if (check_extension(av))
		return (ft_delete(data), FAILED);
	if (creat_copy_file(av, data))
		return (ft_delete(data), FAILED);
	dprintf(2, "copy_file:\n");
	//dprintf(2, "\t");
	//print_map(data->map.copy_file);
	if (texture_infile(data, data->map.copy_file))
		return (ft_delete(data), FAILED);
	//dprintf(2, "text->text_east %s\n", data->texture->text_east);
	if (verif_texture_color(data->texture))
		return (ft_delete(data), FAILED);
	//dprintf(2, "data->map.copy_map[j][i] = %c|\n", data->map.copy_map[0][0]);
	if (map_parsing(data, &data->map.copy_map, data->name_file))
		return (ft_delete(data),FAILED);
	if (creat_map_carre(data))
		return (ft_delete(data), FAILED);
	//printf("NNNNNNNNNNNNNNNNNNNNNN\n");
	//print_map(data->map_fini);
	if (check_pos_player(data->map_fini, data))
		return (ft_delete(data), FAILED);
	
	//if (ft_verif_map(data, data->map.copy_map))
	//	return (ft_delete(data), FAILED);
	//printf("height = %d\n width = %d\n", data->map.map_height, data->map.map_width);
	data->rgb_c = 256 * 256 * data->texture->color_c[0] + 256
		* data->texture->color_c[1] + data->texture->color_c[2];
	data->rgb_f = 256 * 256 * data->texture->color_f[0] + 256
		* data->texture->color_f[1] + data->texture->color_f[2];
	// if (creat_map_carre(data))
	// 	return (ft_delete(data), FAILED);
	return (0);
}
