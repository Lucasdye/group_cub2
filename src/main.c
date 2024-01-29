/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:46:59 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/29 14:17:32 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	if (argc != 2)
		return (printf("problem nbr arg\n"), 1);
	if (init_data(&data))
		return (FAILED);
	if (check_arg(argv[1], &data))
		return (FAILED);
	if (start_mlx(&data))
		return (FAILED);
	printf("fin du programme tout est nickel\n");
	return (SUCCESS);
}
