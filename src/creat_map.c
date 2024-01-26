/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:01:59 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/24 16:24:51 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	nbr_line_map(char **map, int i, int j)
{
	int	start;

	start = i;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\r')
			j++;
		if (map[i][j] != '1')
			return (0);
		i++;
	}
	return (i - start);
}

int	size_big_line(char **file, int i)
{
	int	res;

	res = ft_strlen(file[i]);
	while (file[i])
	{
		if (res < (int)ft_strlen(file[i]))
			res = ft_strlen(file[i]);
		i++;
	}
	//printf("res = %d\n", res);
	return (res);
}

int check_char_tab(char **map)
{	
	int i;
	int j;

	i = 0;
	j = 0;

	dprintf(2, BLUE "check_char_tab()\n" RESET_COLOR);
	while (map[j] != NULL)
	{
		while (map[j][i])
		{
			if (map[j][i] == '\t')
				return ((void)ft_printf("ERROR: tab found at [%d][%d]\n", j, i), FAILED);
			i++;
		}
		i = 0;
		j++;
	}
	return (SUCCESS);
}

int	ajout_map(char **file, int start, t_data *data)
{
	int	j;
	int	i;
	//int k;

	i = -1;
	//k = 0;
	data->map.map_width = size_big_line(file, start);
	dprintf(2, BLUE "ajout_map()\n" RESET_COLOR);
	//dprintf(2, "copy_file2:\n");
	//dprintf(2, "\t");
	//print_map(data->map.copy_file);
	//dprintf(2, "data->map.map_height = %d\n", data->map.map_height);
	while (++i < data->map.map_height)// ???
	{
		//dprintf(2, "start = %d\n", start);
		j = 0;
		//k = 0;
		//dprintf(2, "ft_strlen_tabu(data->map.copy_file[start] = %zu\n", ft_strlen_tabu(data->map.copy_file[start]) + 1);
		//dprintf(2, "i = %d\n", i);
		//dprintf(2, "HEY\n");
		data->map.copy_map[i] = malloc(sizeof(char) * (ft_strlen(data->map.copy_file[start]) + 1));
		if (!data->map.copy_file[i])
			return (msg_err("probleme malloc"), -3);
		while (file[start][j] && file[start][j] != '\n')
		{
			// if (file[start][j] == '\t')
			// {
			// 	data->map.copy_map[i][k] = ' ';
			// 	data->map.copy_map[i][++k] = ' ';
			// 	data->map.copy_map[i][++k] = ' ';
			// 	data->map.copy_map[i][++k] = ' ';
			// }
			// else 
				data->map.copy_map[i][j] = file[start][j];
			j++;
			//k++;
		}
	    data->map.copy_map[i][j] = '\0';
		//dprintf(2, "data->map.copy_map[i] = %s\n", data->map.copy_map[i]);
		// while (k < (int)ft_strlen_tabu(data->map.copy_file[i]))
		// {
		// 	data->map.copy_map[i][k] = '\0';
		// 	k++;
		// }
		start++;
	}
	//dprintf(2, "out of loop: i = %d\n", i);
	//dprintf(2,"HEYYYYYY2\n");
	data->map.copy_map[i] = NULL;
	if (check_char_tab(data->map.copy_map))
		return (-1);
	//dprintf(2, "copy_map:\n");
	//print_map(data->map.copy_map);
	return (2);
}

int	creat_map(char **copy_file, int i, int j, t_data *data)
{
	data->map.map_height = nbr_line_map(copy_file, i, j);
	if (data->map.map_height == 0)
		return (-1);
	dprintf(2, "data->map.map_height = %d\n", data->map.map_height);
	data->map.copy_map = malloc(sizeof(char *) * (data->map.map_height +  1));
	if (!data->map.copy_map)
		return (msg_err("probleme de map"), -3);
	return (ajout_map(copy_file, i, data));
}
