/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_copy_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:31:30 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/29 14:20:14 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	nbr_line_file(int fd)
{
	char	*line;
	int		count_line;

	count_line = 0;
	line = get_next_line(fd);
	while (line)
	{
		count_line++;
		free(line);
		line = get_next_line(fd);
	}
	return (count_line);
}

size_t	ft_strlen_tabu( const char *s)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] == '\t')
		{	
			size += 4;
			i++;
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

int	copy_file(t_data *data)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	line = get_next_line(data->map.fd);
	while (line != NULL)
	{
		j = 0;
		data->map.copy_file[i] = ft_calloc((ft_strlen(line) + 1), sizeof(char));
		if (!data->map.copy_file[i])
			return (msg_err("problem malloc copy_file"), FAILED);
		while (line[j] != '\0')
		{
			data->map.copy_file[i][j] = line[j];
			j++;
		}
		data->map.copy_file[i][j] = '\0';
		free(line);
		i++;
		line = get_next_line(data->map.fd);
	}
	data->map.copy_file[i] = NULL;
	return (SUCCESS);
}

int	creat_copy_file(char *file, t_data *data)
{	
	int	i;

	data->map.fd = open(file, O_RDONLY);
	if (data->map.fd == -1)
		return (msg_err("problem fonction open"), FAILED);
	i = nbr_line_file(data->map.fd);
	data->name_file = ft_strdup(file);
	data->map.copy_file = ft_calloc((i + 1), sizeof(char *));
	if (!data->map.copy_file)
		return (close(data->map.fd), msg_err("plobleme calloc"), FAILED);
	close(data->map.fd);
	data->map.fd = open(file, O_RDONLY);
	if (data->map.fd == -1)
		return (msg_err("problem fonction open"), FAILED);
	if (copy_file(data))
		return (FAILED);
	close(data->map.fd);
	return (SUCCESS);
}
