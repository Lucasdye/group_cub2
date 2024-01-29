/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_color_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:46:47 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/29 14:20:36 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	verif_color(t_text *text)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (text->color_c[i] < 0 || text->color_c[i] > 255)
			return (FAILED);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (text->color_f[i] < 0 || text->color_f[i] > 255)
			return (FAILED);
		i++;
	}
	return (SUCCESS);
}

int	verif_xpm(t_text *text)
{
	int	len;

	len = ft_strlen(text->text_east);
	if (text->text_east[len - 1] != 'm' || text->text_east[len - 2] != 'p'
		|| text->text_east[len - 3] != 'x' || text->text_east[len - 4] != '.')
		return (msg_err("texture pas fini par .xpm"), FAILED);
	len = ft_strlen(text->text_west);
	if (text->text_west[len - 1] != 'm' || text->text_west[len - 2] != 'p'
		|| text->text_west[len - 3] != 'x' || text->text_west[len - 4] != '.')
		return (msg_err("texture pas fini par .xpm"), FAILED);
	len = ft_strlen(text->text_north);
	if (text->text_north[len - 1] != 'm' || text->text_north[len - 2] != 'p'
		|| text->text_north[len - 3] != 'x' || text->text_north[len - 4] != '.')
		return (msg_err("texture pas fini par .xpm"), FAILED);
	len = ft_strlen(text->text_south);
	if (text->text_south[len - 1] != 'm' || text->text_south[len - 2] != 'p'
		|| text->text_south[len - 3] != 'x' || text->text_south[len - 4] != '.')
		return (msg_err("texture pas fini par .xpm"), FAILED);
	return (SUCCESS);
}

int	check_text(t_text *text)
{
	int	fd;

	fd = open(text->text_east, O_RDONLY);
	if (fd == -1)
		return (msg_err("erreur open texture east"), FAILED);
	close(fd);
	fd = open(text->text_north, O_RDONLY);
	if (fd == -1)
		return (msg_err("erreur open texture north"), FAILED);
	close(fd);
	fd = open(text->text_south, O_RDONLY);
	if (fd == -1)
		return (msg_err("erreur open texture south"), FAILED);
	close(fd);
	fd = open(text->text_west, O_RDONLY);
	if (fd == -1)
		return (msg_err("erreur open texture west"), FAILED);
	close(fd);
	return (verif_xpm(text));
}

int	verif_texture_color(t_text *text)
{
	if (!text->text_east || !text->text_north || !text->text_south
		|| !text->text_west)
		return (msg_err("Erreur de texture"), FAILED);
	if (!text->color_c || !text->color_f)
		return (msg_err("Erreur color"), FAILED);
	if (check_text(text))
		return (FAILED);
	if (verif_color(text))
		return (msg_err("erreur color"), FAILED);
	return (SUCCESS);
}
