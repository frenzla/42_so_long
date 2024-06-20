/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:31:00 by alarose           #+#    #+#             */
/*   Updated: 2024/06/18 18:04:05 by alarose          ###   ########.fr       */
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
# define TILE_SIZE 20

# define MAP_PATH "./maps/mapOK.ber"

# define NB_IMAGES 2
# define SQUARE 0	//No path
# define SQUARE_PATH ""	//No path
# define CARROT 1
# define CARROT_PATH "./assets/carrot.xpm"

# define WIN_WIDTH 640
# define WIN_LENGTH 480

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
}	t_img;

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	t_img	img[5];
}	t_data;

typedef void (*keystroke_func)(t_img*);

typedef struct {
	unsigned int	keycode;
	keystroke_func	func;
} keycode_f_mapping;

void	go_right(t_img *img);
void	go_left(t_img *img);
void	go_up(t_img *img);
void	go_down(t_img *img);
int		handle_input(int keysym, t_data *data);
void	init_img_paths(char **img_paths);
int		new_img_from_file(char **paths, t_data *data, int i);
int		render(t_data *data);
int		get_map(char *map_path, char ***map);
int		parse_map(int fd, int nb_lines, char ***map);
int		free_map(char ***map);
void	clean_quit(char ***map, t_data *data);
int		map_is_valid(char ***map, int nb_lines);
int		map_path_valid(char *map_path);
int		have_all_elements(char ***map);
int		have_one_exit(char ***map);
int		have_collectibles(char ***map);
int		have_one_start(char ***map);
int		is_in_charset(char c);
int		check_chars(char ***map);
int		is_rectangle(char ***map);
int		map_path_valid(char *map_path);
int		check_external_walls(char ***map, int nb_lines);
int		position_is_valid(int x, int y, char ***map, int nb_lines);

#endif