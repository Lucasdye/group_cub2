/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sycourbi <sycourbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:26:52 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/18 12:50:44 by sycourbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_tab(void **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	malloc_texture_nsew2(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < (64 * 64))
			data->texture_nsew[i][j] = 0;
	}
}

int	malloc_texture_nsew(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			data->tab[i][j] = 0;
	}
	data->texture_nsew = malloc(sizeof(int *) * 5);
	if (!data->texture_nsew)
		return (FAILED);
	i = -1;
	while (++i < 4)
	{
		data->texture_nsew[i] = malloc(sizeof(int) * (64 * 64));
		if (!data->texture_nsew[i])
			return (FAILED);
	}
	data->texture_nsew[4] = NULL;
	malloc_texture_nsew2(data);
	return (SUCCESS);
}
