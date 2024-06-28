/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:31:00 by alarose           #+#    #+#             */
/*   Updated: 2024/06/28 19:34:32 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

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
# include <unistd.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define RESET "\x1b[0m"

# define FONT "-schumacher-clean-bold-r-normal--15-150-75-75-c-90-iso646.1991-irv"
# define FONT_COLOR 0xf9d38c
# define BANNER_COLOR 0x6E356A

# define TRUE 1
# define FALSE 0
# define RET_ERR 0
# define TILE_SIZE 32
# define SQUARE_LEN 12
# define IN_BETWEEN 6

# define MAP_PATH "./maps/mapOK.ber"

# define NB_IMAGES 6
# define WALL 0
# define WALL_PATH "./assets/tree_on_grass.xpm"
# define WALL_CODE '1'
# define COLL 1
# define COLL_PATH "./assets/mushroom_on_grass.xpm"
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
# define PLAYER_EXIT 5
# define PLAYER_EXIT_PATH "./assets/player_on_exit.xpm"
# define PLAYER_EXIT_CODE 'X'
# define WIN_IMG_PATH "./assets/you_win.xpm"

//To delete
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		x;
	int		y;
	char	map_code;
}	t_img;

typedef struct s_map {
	char	*map_path;
	int		width;
	int		height;
	char	**map_layout;
	int		start_x;
	int		start_y;
	int		nb_collectibles;
	char	move_in;
	int		move_out_i_img;
}	t_map;

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	t_img	img[NB_IMAGES];
	t_map	map;
	int		game_over;
}	t_data;

typedef int	(*t_keystroke_func)(t_data *data, int i_img);

typedef struct s_keycode_f_mapping {
	int					keycode;
	t_keystroke_func	func;
}	t_keycode_f_mapping;

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
void	clean_quit(t_data *data);
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
int		add_map_code(t_data *data, int i);
void	render_map(t_data *data);
void	win(t_data *data);
int		close_game(t_data *data, int i);
void	free_imgs_path(char **img_paths);
int		adjust_map(t_data *data, int i_img);

//bonus functions
int		display_banner(t_data *data , int nb_moves);
void	img_pixel_put(t_img *img, int x, int y, int color);
void	render_bg(t_img *img, int color);
int		render_banner(t_data *data);
void	render_tile(t_data *data, int i, int k, int i_img);
void	put_img_to_img(t_img *dst, t_img *src, int x, int y);
int		get_pixel_img(t_img *img, int x, int y);
int		add_logo(t_data *data, t_img *banner);
int		add_full_square(t_data *data, t_img *banner, int x, int y);
int		add_empty_square(t_data *data, t_img *banner, int x, int y);
int		add_coll_tracker(t_data *data, t_img *banner);
void	put_squares(t_data *data, int total_coll, t_img *tracker);
int		gen_tracker(t_data *data, int len, int total_coll, t_img *banner);

#endif