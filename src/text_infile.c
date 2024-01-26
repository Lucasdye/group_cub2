/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:46:47 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/26 14:19:19 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ajout_new_texture(char *map, int j)
{
	int		len;
	char	*line;
	int		i;

	while (map[j] == ' ' || map[j] == '\t' || map[j] == '\r')
		j++;
	len = j;
	while (map[len] && (map[len] != ' ' && map[len] != '\t'))
		len++;
	line = malloc(sizeof(char) * (len - j + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (map[j] && (map[j] != ' ' && map[j] != '\t' && map[j] != '\n'))
	{
		line[i++] = map[j++];
	}
	line[i] = '\0';
	while (map[j] && (map[j] == ' ' || map[j] == '\t'))
		j++;
	if (map[j] && map[j] != '\n')
		return (free(line), NULL);
	return (line);
}

int	ajout_texture(char *map, int j, t_text *texture)
{
	if (map[j] == 'N' && map[j + 1] == 'O' && !texture->text_north)
		texture->text_north = ajout_new_texture(map, j + 2);
	else if (map[j] == 'S' && map[j + 1] == 'O' && !texture->text_south)
		texture->text_south = ajout_new_texture(map, j + 2);
	else if (map[j] == 'W' && map[j + 1] == 'E' && !texture->text_west)
		texture->text_west = ajout_new_texture(map, j + 2);
	else if (map[j] == 'E' && map[j + 1] == 'A' && !texture->text_east)
		texture->text_east = ajout_new_texture(map, j + 2);
	else
		return (-1);
	return (0);
}

int	check_whitespace(char **file, int i, int j, t_data *data)
{
	while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r')
		j++;
	if (file[i][j] && (file[i][j] >= 'A' && file[i][j] <= 'Z'))
	{
		if (file[i][j + 1] && (file[i][j + 1] >= 'A' && file[i][j + 1] <= 'Z'))
			return (ajout_texture(file[i], j, &data->texture));
		else if (file[i][j + 1])
			return (ajout_color(file[i], j, &data->texture));
	}
	if (file[i][j] == '\0' || file[i][j] == '\n')
		return (1);
	else if (file[i][j] != '\0' && (file[i][j] == '0' || file[i][j] == '1'))
		return (creat_map(file, i, j, data));
	return (-1);
}

int	texture_infile(t_data *data, char **copy_file)
{
	int	i;
	int	res;

	i = 0;
	dprintf(2, BLUE "texture_infile()\n" RESET_COLOR);
	while (copy_file[i])
	{
		res = check_whitespace(copy_file, i, 0, data);
		if (res == -1)
			return (msg_err("erreur trouver dans le fichier"), FAILED);
		if (res == 2)
			return (SUCCESS);
		if (res == -3)
			return (FAILED);
		i++;
	}
	return (FAILED);
}
