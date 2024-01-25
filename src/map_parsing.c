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

int		top_nd_down_lines(t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	//North wall
    while(data->map.copy_map[j][i])
    {
        if (data->map.copy_map[j][i] && data->map.copy_map[j][i] != '1')
		{
			if (data->map.copy_map[j + 1][i] == '0' || is_player(data->map.copy_map[j + 1][i])/*data->map.copy_map[j + 1][i] == 'N'*/)
				return ((void)ft_printf("Error: north border unclosed\n"), FAILED);
		}
        i++;
    }
	i = 0;
	//South wall 
    while(data->map.copy_map[data->map.map_height - 1][i])
    {
		if (data->map.copy_map[data->map.map_height - 1][i] != '1')
		{
			if (data->map.copy_map[data->map.map_height - 1][i] == '0' 
				|| is_player(data->map.copy_map[data->map.map_height - 1][i])/*data->map.copy_map[data->map.map_height - 1][i] == 'N'*/)
				return ((void)ft_printf("Error: south border unclosed\n"), FAILED);
		}
        i++;
    }
	return (SUCCESS);
}

int		left_nd_right_colums(t_data *data)
{
	int j;
	j = 0;

	//dprintf(2, "data->map.copy_map[j][ft_strlen(data->map.copy_map[j]) - 1] == %c\n", data->map.copy_map[1][ft_strlen(data->map.copy_map[1]) - 1]);
	//dprintf(2, "data->map.copy_map[j]== %s\n", data->map.copy_map[1]);
   
    while (data->map.copy_map[j])
    {
        if (data->map.copy_map[j][0] == '0'
			|| data->map.copy_map[j][ft_strlen(data->map.copy_map[j]) - 1] == 'N')
            return ((void)ft_printf("Error: west border unclosed\n"), FAILED);
        if (data->map.copy_map[j][ft_strlen(data->map.copy_map[j]) - 1] == '0'
			||  is_player(data->map.copy_map[j][ft_strlen(data->map.copy_map[j]) - 1])/*data->map.copy_map[j][ft_strlen(data->map.copy_map[j]) - 1] == 'N'*/)
            return ((void)ft_printf("Error: east border unclosed\n"), FAILED);
        j++;
    }
	return (SUCCESS);
}	

int		check_map_borders(t_data *data)// NO '0' in map borderss map closed ?
{
    dprintf(2, BLUE "check_map_borders()\n" RESET_COLOR);// NO '0' in map borders);
	if (top_nd_down_lines(data))
		return (FAILED);
	if (left_nd_right_colums(data))
		return (FAILED);
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

// int		cross_checking(t_data *data, int i, int j, char **map)
// {
// 	int temp_i;
// 	int temp_j;

// 	temp_j = j;
// 	temp_i = i;
// 	dprintf(2, BLUE "cross_checking\n" RESET_COLOR);
// 	dprintf(2, "received i = %d, received j = %d\n", i, j);
// 	while (map[j][i] && map[j][i] == ' ')//RIGHT
// 		i++;
// 	if (map[j][i] && map[j][i] != ' ' && map[j][i] != '1' && map[j][i] != '\0')
// 		return ((void)ft_printf("Error: wall missing at : [%d][%d]\n", j, i), (void)ft_printf("map[%d][%d]\n", j, i, data->map.copy_map[j][i]), FAILED);
// 	i = temp_i;
// 	while (i > 0 && map[j][i] && map[j][i] == ' ')//LEFT
// 		i--;
// 	if (map[j][i] && map[j][i] != ' ' && map[j][i] != '1')
// 		return ((void)ft_printf("Error: wall missing at : [%d][%d]\n", j, i), FAILED);
// 	i = temp_i;
// 	while (j < data->map.map_height - 1 && map[j][i] && map[j][i] == ' ' && map[j] != NULL)//UP
// 		j++;
// 	if (map[j][i] && map[j][i] != ' ' && map[j][i] != '1')
// 		return ((void)ft_printf("Error: wall missing at : [%d][%d]\n", j, i), FAILED);
// 	j = temp_j;
// 	while (j > 0 && map[j][i] && map[j][i] == ' ')//DOWN
// 		j--;
// 	if (map[j][i] && map[j][i] != ' ' && map[j][i] != '1')
// 		return ((void)ft_printf("Error: wall missing at : [%d][%d]\n", j, i), FAILED);
// 	j = temp_j;
// 	return (SUCCESS);
// }


int		cross_checking(t_data *data, int i, int j, char **map)
{
	int temp_i;
	int temp_j;

	temp_j = j;
	temp_i = i;
	//dprintf(2, BLUE "cross_checking\n" RESET_COLOR);
	//dprintf(2, "received i = %d, received j = %d\n", i, j);
	while (map[j][i] && map[j][i] != '1')//RIGHT
		i++;
	if (map[j][i] && map[j][i] != ' ' && map[j][i] != '1' && map[j][i] != '\0')
		return ((void)ft_printf("Error: wall missing at : [%d][%d]\n", j, i), (void)ft_printf("map[%d][%d]\n", j, i, data->map.copy_map[j][i]), FAILED);
	i = temp_i;
	while (i > 0 && map[j][i] && map[j][i] != '1')//LEFT
		i--;
	if (map[j][i] && map[j][i] != ' ' && map[j][i] != '1')
		return ((void)ft_printf("Error: wall missing at : [%d][%d]\n", j, i), FAILED);
	i = temp_i;
	while (j < data->map.map_height - 1 && map[j][i] && map[j][i] == ' ' && map[j] != NULL && map[j][i] != '1')//UP
		j++;
	if (map[j][i] && map[j][i] != ' ' && map[j][i] != '1')
		return ((void)ft_printf("Error: wall missing at : [%d][%d]\n", j, i), FAILED);
	j = temp_j;
	while (j > 0 && map[j][i] && map[j][i] == ' ' && map[j][i] != '1')//DOWN
		j--;
	if (map[j][i] && map[j][i] != ' ' && map[j][i] != '1')
		return ((void)ft_printf("Error: wall missing at : [%d][%d]\n", j, i), FAILED);
	j = temp_j;
	return (SUCCESS);
}

int		check_inside_map_walls(t_data *data, char **map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[j])
	{
		while (map[j][i])
		{
			if (map[j][i] == ' ')
			{
				if (cross_checking(data, i, j, map))
					return (FAILED);
			}
			// while(map[j][i] == ' ')
			// 	i++;
			i++;
		}
		i = 0;
		j++;
	}
	return (SUCCESS);
}

// int		is_map_closed(t_data *data, char **map)
// {
	
// 	dprintf(2, BLUE "is_map_closed()\n" RESET_COLOR);
// 	if (check_map_borders(data) == FAILED)// NO '0' in map borders (quick check)
// 		return (FAILED);
// 	if (check_inside_map_walls(data, map) == FAILED)
// 		return (FAILED);
//     return (SUCCESS);
// }

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

void	fill_spaces(char ***copy_map)
{
	int i;
	int j;
	
    dprintf(2, BLUE "fill_spaces()\n" RESET_COLOR);
	i = 0;
	j = 0;

	while ((*copy_map)[j])
	{
		while ((*copy_map)[j][i])
		{
			if ((*copy_map)[j][i] == ' ')
				(*copy_map)[j][i] = '1';
			i++;
		}
		i = 0;
		j++;
	}
	return ;
}

int map_frame(t_data *data, char **map)
{
	int i;
	int j;
	//size_t data->map.map_width;

	(void)map;
	dprintf(2, BLUE "map_frame()\n" RESET_COLOR);
	//data->map.map_width = 0;
	//longest_line(data, &data->map.map_width, map);
	i = -1;
	j = -1;
	data->map.map_frame = malloc(sizeof(char *) * (data->map.map_height + 3));
	//dprintf(2, "data->map.map_width = %zu\n", data->map.map_width);
	//dprintf(2, " data->map.map_height = %d\n", data->map.map_height);
	data->map.map_frame[data->map.map_height + 2] = NULL;
	while (++j < data->map.map_height + 2)
	{	
		data->map.map_frame[j] = malloc(data->map.map_width + 3);
		//data->map.map_frame[j][data->map.map_width + 2] = '\0';
	}
	j = -1;
	while (data->map.map_frame[++j])
	{
		while (++i < data->map.map_width + 3)
			data->map.map_frame[j][i] = ' ';
		i = -1;
	}
	//data->map.map_frame[data->map.map_height + 2] = NULL;
	//defining first line
	while (++i < data->map.map_width + 3)
		data->map.map_frame[0][i] = '*';
	data->map.map_frame[0][i] = 0;
	//defining last line 
	i = -1;
	while (++i < data->map.map_width + 3)
		data->map.map_frame[data->map.map_height + 1][i] = '*';
	data->map.map_frame[data->map.map_height + 1][i] = 0;
	//defining first column
	j = -1;
	while (++j < data->map.map_height + 2)
		data->map.map_frame[j][0] = '*';
	//defining last column
	j = -1;
	while (++j < data->map.map_height + 2)
	{
		//dprintf(2, "last column\n");
		data->map.map_frame[j][data->map.map_width + 2] = '*';
		dprintf(2, "data->map.map_frame[j][data->map.map_width + 1] = %c\n",data->map.map_frame[j][data->map.map_width + 2]);
	}
	//dprintf(2, "data->map.map_frame[j - 2] = %s\n", data->map.map_frame[j - 1]);
	//copy the map
	i = 0;
	j = 0;
	// while (map[j][i])
	// {
	// 	data->map.map_frame[j + 1][i + 1] = data->map.copy_map[j][i];
	// }
	//int i = 0;
	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
			data->map.map_frame[j + 1][i + 1] = map[j][i];
	}
	print_map(data->map.map_frame);
	return (SUCCESS);
}

int detect_walls(int start_i, int start_j, char **map)
{
	int flag_wall;
	int temp_i;
	int temp_j;

	flag_wall = 0;
	temp_i = start_i;
	temp_j = start_j;
	//RIGHT
	while (map[start_j][start_i])
	{
		if (map[start_j][start_i] == '1')
			flag_wall = 1;
		start_i++;
	}
	if (flag_wall == 0)
		return (FAILED);
	else 
		flag_wall = 0;
	printf("Right OK\n");
	//LEFT
	start_i = temp_i;
	while (start_i >= 0)
	{
		if (map[start_j][start_i] == '1')
			flag_wall = 1;
		start_i--;
	}
	if (flag_wall == 0)
		return (FAILED);
	else 
		flag_wall = 0;
	printf("Left OK\n");
	//UP
	start_i = temp_i;
	while (start_j >= 0)
	{
		if (map[start_j][start_i] == '1')
			flag_wall = 1;
		start_j--;
	}
	if (flag_wall == 0)
		return (FAILED);
	else 
		flag_wall = 0;
	printf("UP OK\n");
	start_j = temp_j;
	//DOWN
	while (map[start_j])
	{
		if (map[start_j][start_i] == '1')
			flag_wall = 1;
		start_j++;
	}
	if (flag_wall == 0)
		return (FAILED);
	else 
		flag_wall = 0;
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
			if (map[j][i] == '0')
			{	
				if (detect_walls(i, j, map) == FAILED)
				{
					dprintf(2, "unshut floor at [%d][%d]\n", j, i);
					return (FAILED);
				}
			}
			i++;
		}
		j++;
	}
	return (SUCCESS);
}

// int check_floating_floor(char **map_framed)
// {
// 	int i;
// 	int j;

// 	i = 1;
// 	//j = 0;

// 	//NORTH towards south
// 	while (i < ft_strlen(map_framed[0]))
// 	{
// 		j = 1;
// 		while (map_framed[j] && map_framed[j][i] == ' ')
// 			j++;
// 		if (map_framed[j][i] != 1)
// 		{
// 			ft_printf("Floating floor at [%d][%d]\n", j, i);
// 			return (FAILED);
// 		}
// 		i++;
// 	}
// 	return (SUCCESS);	
// }

int		map_parsing(t_data *data, char ***copy_map, char *path)
{
    dprintf(2, BLUE "map_parsing()\n" RESET_COLOR);
	(void)path;

	// dprintf(2, "copy_map:\n");
	// print_map(data->map.copy_map);
	// (void)copy_map;
	// if (only_one_player(data->map.copy_map) == FAILED)
	// 	return((void)ft_printf("Error: two player found\n"), FAILED);
    // if (is_map_closed(data, data->map.copy_map) == FAILED)
	// 	return ((void)ft_printf("Error: map unclosed\n"), FAILED);
	// fill_spaces(copy_map);
	// dprintf(2, "copy_map filled:\n");
	// print_map(data->map.copy_map);
	// if (trash_detector((*copy_map)) == FAILED)
	// 	return ((void)ft_printf("Error: map trash detected\n"), FAILED);
	// dprintf(2, "copy_map after fill_spaces:\n");
	// print_map(data->map.copy_map);
	(void)copy_map;
	if (only_one_player(data->map.copy_map) == FAILED)
		return((void)ft_printf("Error: two player found\n"), FAILED);
	if (is_map_closed(data->map.copy_map) == FAILED)
		return ((void)ft_printf("Error: map unclosed !\n"), FAILED);
	// map_frame(data, *(copy_map));
	// if (check_flotting_floors() == FAILED)
	// 	return ((void)ft_printf("Error: flotting floor !\n"), FAILED);

    return (SUCCESS);
}
