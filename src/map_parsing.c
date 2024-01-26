#include "../cub3d.h"

int is_player(char letter)
{
	if (letter == 'N' || letter == 'S' || letter == 'E' || letter == 'W')
	{	
		dprintf(2, "letter found = %c\n", letter);
		return (1);
	}
	return (0);
}

int only_one_player(char **map)
{
	int i;
	int j;
	int flag;

	i = 0;
	j = 0;
	flag = 0;
	while (map[j])
	{
		while(map[j][i])
		{
			if (is_player(map[j][i]) == 1)
			{
				if (flag == 1)
				{
					dprintf(2, "second player [%d][%d]\n", j, i);
					return (FAILED);
				}
				else 
					flag = 1;
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (SUCCESS);
}

void	print_map(char **map)
{
    int i;

    i = 0;
    
    if (!map)
    { 
        dprintf(2, "No loaded map\n");
        return ;
    }
    while (map[i])
    {
        dprintf(2, "%s", map[i]);
        dprintf(2, "\n");
        i++;
    }
}

int		trash_detector(char **copy_map)
{
	int i;
	int j;

	i = 0;
	j = 0;
    dprintf(2, BLUE "trash_detector()\n" RESET_COLOR);
	while (copy_map[j])
	{
		while(copy_map[j][i])
		{
			if (copy_map[j][i] != '0' && copy_map[j][i] != '1')
			{
				if (copy_map[j][i] != 'N' && copy_map[j][i] != 'S')
				{
					if (copy_map[j][i] != 'W' && copy_map[j][i] != 'E')
					{	
						dprintf(2, "copy_map[%d][%d] = %c\n",j, i, copy_map[j][i]);
						return (FAILED);
					}
				}
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (SUCCESS);
}

int detect_walls(int start_i, int start_j, char **map)
{
	int flag_wall;
	int flag_space;
	int temp_i;
	int temp_j;

	temp_i = start_i;
	temp_j = start_j;
	flag_wall = -1;
	flag_space = -1;
	//RIGHT
	ft_printf(BLUE "detect_walls\n" RESET_COLOR);
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
		dprintf(2, "flag_wall = %d\n", flag_wall);
		dprintf(2, "flag_space = %d\n", flag_space);
		if (flag_space != -1 && flag_wall > flag_space)
			return (FAILED);
	}
	else if (flag_wall == -1)
	{
		dprintf(2, "FAIL RIGHT\n");
		return (FAILED);
	}
	flag_space = -1;
	flag_wall = -1;
	printf("Right OK\n");
	//LEFT
	start_i = temp_i;
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
		dprintf(2, "flag_wall = %d\n", flag_wall);
		dprintf(2, "flag_space = %d\n", flag_space);
		if (flag_space != -1 && flag_wall < flag_space)
			return (FAILED);
	}
	else if (flag_wall == -1)
		return (FAILED);	
	flag_wall = -1;
	flag_space = -1;
	printf("Left OK\n");
	//UP
	start_i = temp_i;
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
		dprintf(2, "flag_wall = %d\n", flag_wall);
		dprintf(2, "flag_space = %d\n", flag_space);
		if (flag_space != -1 && flag_wall < flag_space)
			return (FAILED);
	}
	else if (flag_wall == -1)
		return (FAILED);
	flag_wall = -1;
	flag_space = -1;
	printf("UP OK\n");
	start_j = temp_j;
	//DOWN
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
		dprintf(2, "flag_wall = %d\n", flag_wall);
		dprintf(2, "flag_space = %d\n", flag_space);
		if (flag_space != -1 && flag_wall > flag_space)
			return (FAILED);
	}
	else if (flag_wall == -1)
		return (FAILED);
	printf("DOWN OK\n");
	return (SUCCESS);
}

int is_map_closed(char **map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[j])
	{
		i = 0;
		while(map[j][i])
		{
			if (map[j][i] == '0' || is_player(map[j][i]))
			{	
				if (detect_walls(i, j, map) == FAILED)
				{
					ft_printf("unshut floor at [%d][%d] = %c\n", j, i, map[j][i]);
					return (FAILED);
				}
			}
			i++;
		}
		j++;
	}
	return (SUCCESS);
}

int		map_parsing(t_data *data, char ***copy_map, char *path)
{
    dprintf(2, BLUE "map_parsing()\n" RESET_COLOR);
	(void)path;
	(void)copy_map;
	print_map(data->map.copy_map);
	if (only_one_player(data->map.copy_map) == FAILED)
		return((void)ft_printf("Error: two player found\n"), FAILED);
	if (is_map_closed(data->map.copy_map) == FAILED)
		return ((void)ft_printf("Error: map unclosed !\n"), FAILED);
    return (SUCCESS);
}
