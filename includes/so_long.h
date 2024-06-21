/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:31:00 by alarose           #+#    #+#             */
/*   Updated: 2024/06/21 18:50:45 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "/home/alarose/sgoinfre/mlx/mlx.h"
# include "libft.h"
# include <stdio.h>
# include <errno.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdlib.h>
//To delete
# include </home/alarose/Criterion/include/criterion/criterion.h>
#include <unistd.h>

// Définir les codes de couleur ANSI
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

# define TRUE 1
# define FALSE 0
# define RET_ERR 0
# define TILE_SIZE 32

# define MAP_PATH "./maps/mapOK.ber"

# define NB_IMAGES 5
# define WALL 0
# define WALL_PATH "./assets/tree_on_grass.xpm"
# define WALL_CODE '1'
# define COLL 1
# define COLL_PATH "./assets/carrot_on_grass.xpm"
# define COLL_CODE 'C'
# define EXIT 2
# define EXIT_PATH "./assets/exit_on_grass.xpm"
# define EXIT_CODE 'E'
# define PLAYER 3
# define PLAYER_PATH "./assets/player_on_grass.xpm"
# define PLAYER_CODE 'P'
# define BG 4
# define BG_PATH "./assets/grass.xpm"
# define BG_CODE '0'

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		x;
	int		y;
	char	map_code;
}	t_img;

typedef	struct s_map {
	char	*map_path;
	int		width;
	int		height;
	char	**map_layout;
	int		start_x;
	int		start_y;
	int		nb_collectibles;
} t_map;

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	t_img	img[5];
	t_map	map;
}	t_data;

typedef int (*keystroke_func)(t_data *data, int i_img);

typedef struct {
	unsigned int	keycode;
	keystroke_func	func;
} keycode_f_mapping;

int		go_right(t_data *data, int i_img);
int		go_left(t_data *data, int i_img);
int		go_up(t_data *data, int i_img);
int		go_down(t_data *data, int i_img);
int		handle_input(int keysym, t_data *data);
int		init_imgs(char **img_paths, t_data *data);
int		new_img_from_file(char *path, t_data *data, int i);
void	set_img_position(t_data *data, int i, int x, int y);
int		render(t_data *data);
int		get_map(char *map_path, t_data *data);
int		parse_map(int fd, t_data *data);
void	free_map(char **map);
void	clean_quit(char ***map, t_data *data);
int		map_is_valid(char ***map, int nb_lines);
int		map_path_valid(char *map_path);
int		have_one_exit(char ***map);
int		have_collectibles(char ***map);
int		have_one_start(char ***map);
int		is_in_charset(char c);
int		check_chars(char ***map);
int		is_rectangle(char ***map);
int		check_external_walls(char ***map, int nb_lines);
int		position_is_valid(int x, int y, char ***map, int nb_lines);
int		path_ok(int y, int x, t_data *data, char **map);
int		get_nb_lines(char *map_path);
int		get_map_info(t_data *data);
char	**copy_map(char **map, int height);
int		add_map_code(t_data *data);
void	render_map(t_data *data);

#endif