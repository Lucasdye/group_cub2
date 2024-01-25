/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:46:51 by sycourbi          #+#    #+#             */
/*   Updated: 2024/01/24 16:36:54 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# include <stddef.h>
/*fonction write, close, read*/
# include <unistd.h>
/*fonction open*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
/*fonction printf, perror*/
# include <stdio.h>
/*fonction malloc, free, exit*/
# include <stdlib.h>
/*fonction strerror*/
# include <string.h>
# include <math.h>
/* Fonction mlx */
# include <X11/keysym.h>
# include <X11/X.h>

# define FAILED 1
# define SUCCESS 0
# define WIDTH 1080
# define HEIGHT 720
# define BLUE "\033[34m"
# define RESET_COLOR "\033[0m"

typedef struct s_player
{
	double	startpos_x;
	double	startpos_y;

}	t_player;

typedef struct s_text
{
	int		*color_c;
	int		*color_f;
	char	*text_north;
	char	*text_south;
	char	*text_west;
	char	*text_east;

}	t_text;

typedef struct s_map
{
	char	**copy_map;
	char	**copy_file;
	int		map_height;
	int		map_width;
	char 	**map_frame;
	int		fd;
}	t_map;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_height;
	int		img_width;
}	t_img;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				win_height;
	int				win_width;
	int				pixel_img;
	char			*name_file;
	char			**map_fini;
	int				**text_pix;
	int				**texture_nsew;
	double			movespeed;
	double			rotspeed;
	char			dir;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				line_height;
	double			wall_x;
	double			wall_dist;
	int				draw_start;
	int				draw_end;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			raydir_x;
	double			raydir_y;
	double			camera_x;
	double			deltadist_x;
	double			deltadist_y;
	double			sidedist_x;
	double			sidedist_y;
	int				side;
	unsigned int	rgb_c;
	unsigned int	rgb_f;
	int				tab[HEIGHT + 1][WIDTH + 1];
	int				tex_x;
	t_map			map;
	t_text			*texture;
	t_player		player;
	t_img			img;
}	t_data;

/*main.c*/
size_t	ft_strlen_tabu( const char *s);
int		main(int argc, char **argv);
/*check_arg.c*/
int		check_arg(char *av, t_data *data);
int     map_parsing(t_data *data, char ***map, char *path);
/*creat_copy_file.c*/
int		creat_copy_file(char *file, t_data *data);
/*creat_map_carre*/
int		creat_map_carre(t_data *data);
/*init.c*/
int		init_data(t_data *data);
void	init_ray(t_data *data);
/*error.c*/
void print_map(char **map);
void	msg_err(char *str);
void	ft_delete(t_data *data);
void	all_free(t_data *data);
/*utils.c*/
void	free_tab(void **tab);
int		malloc_texture_nsew(t_data *data);
int		size_big_line(char **file, int i);
int		nbr_line_map(char **map, int i, int j);
/*text_infile*/
int		texture_infile(t_data *data, char **map);
/*color_infile*/
int		ajout_color(char *map, int j, t_text *texture);
/*creat_map*/
int		creat_map(char **copy_file, int i, int j, t_data *data);
/*verif_map*/
int		ft_verif_map(t_data *data, char **map);
/*text_color_check*/
int		verif_texture_color(t_text *text);
/*pos_player.c*/
int		check_pos_player(char **map, t_data *data);
/*start_mlx.c*/
int		start_mlx(t_data *data);
/*image.c*/
int		go_image(t_data *data);
//int		load_image(t_data *data, int *texture, char *text_nswe, t_img *img);
//void	init_texture_pix(t_data *data);
void	init_img(t_img	*img);
int		raycaster(t_data *data);
void	dessin(t_data *data);
//void	init_texture_image(t_data *data, t_img *img, char *path);
void	dessin_img_tab(t_data *data, int x, double step);
int		check_pos_player(char **map, t_data *data);
void	ajout_pos_player(char **map, t_data *data);
int		load_image(t_data *data, int *texture, char *nsew, t_img *img);
void	dessin_fini(t_data *data);
//int	render(t_data *data);
int		keypress(int key, t_data *data);
/*keypress_move.c*/
void	haut(t_data *data);
void	bas(t_data *data);
void	droite(t_data *data);
void	gauche(t_data *data);
#endif
