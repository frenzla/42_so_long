/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:31:00 by alarose           #+#    #+#             */
/*   Updated: 2024/06/12 19:31:37 by alarose          ###   ########.fr       */
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

# define NB_KEY_FUNC 4

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
char	**get_map(char *map_path);
int		parse_map(int fd, int nb_lines, char **map);

#endif