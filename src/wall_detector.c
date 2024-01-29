/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:54:29 by lbouguet          #+#    #+#             */
/*   Updated: 2024/01/29 14:08:42 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	west(int start_i, int start_j, char **map)
{
	int	flag_wall;
	int	flag_space;

	flag_wall = -1;
	flag_space = -1;
	while (map[start_j][start_i] && flag_wall == -1)
	{
		if (map[start_j][start_i] == '1')
			flag_wall = start_i;
		else if (map[start_j][start_i] == ' ')
			flag_space = start_i;
		start_i++;
	}
	if (flag_wall != -1)
	{
		if (flag_space != -1 && flag_wall > flag_space)
			return (FAILED);
	}
	else if (flag_wall == -1)
		return (FAILED);
	return (SUCCESS);
}

static int	east(int start_i, int start_j, char **map)
{
	int	flag_wall;
	int	flag_space;

	flag_wall = -1;
	flag_space = -1;
	while (start_i >= 0 && flag_wall == -1)
	{
		if (map[start_j][start_i] == '1')
			flag_wall = start_i;
		else if (map[start_j][start_i] == ' ')
			flag_space = start_i;
		start_i--;
	}
	if (flag_wall != -1)
	{
		if (flag_space != -1 && flag_wall < flag_space)
			return (FAILED);
	}
	else if (flag_wall == -1)
		return (FAILED);
	return (SUCCESS);
}

static int	north(int start_i, int start_j, char **map)
{
	int	flag_wall;
	int	flag_space;

	flag_wall = -1;
	flag_space = -1;
	while (start_j >= 0 && flag_wall == -1)
	{
		if (map[start_j][start_i] == '1')
			flag_wall = start_j;
		else if (map[start_j][start_i] == ' ')
			flag_space = start_j;
		start_j--;
	}
	if (flag_wall != -1)
	{
		if (flag_space != -1 && flag_wall < flag_space)
			return (FAILED);
	}
	else if (flag_wall == -1)
		return (FAILED);
	return (SUCCESS);
}

static int	south(int start_i, int start_j, char **map)
{
	int	flag_wall;
	int	flag_space;

	flag_wall = -1;
	flag_space = -1;
	while (map[start_j] && flag_wall == -1)
	{
		if (map[start_j][start_i] == '1')
			flag_wall = start_j;
		else if (map[start_j][start_i] == ' ')
			flag_space = start_j;
		start_j++;
	}
	if (flag_wall != -1)
	{
		if (flag_space != -1 && flag_wall > flag_space)
			return (FAILED);
	}
	else if (flag_wall == -1)
		return (FAILED);
	return (SUCCESS);
}

int	detect_walls(int start_i, int start_j, char **map)
{
	if (west(start_i, start_j, map) == FAILED)
		return (FAILED);
	if (east(start_i, start_j, map) == FAILED)
		return (FAILED);
	if (north(start_i, start_j, map) == FAILED)
		return (FAILED);
	if (south(start_i, start_j, map) == FAILED)
		return (FAILED);
	return (SUCCESS);
}
