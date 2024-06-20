/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:31:00 by alarose           #+#    #+#             */
/*   Updated: 2024/06/11 13:57:03 by alarose          ###   ########.fr       */
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

# define MLX_ERROR 1

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

void	go_right(t_img *img);
void	go_left(t_img *img);
void	go_up(t_img *img);
void	go_down(t_img *img);
void	craft_pixel_in_img(t_img *img, int x, int y, int color);
int		handle_input(int keysym, t_data *data);
void	init_img_paths(char **img_paths);
int		new_img_from_file(char **paths, t_data *data, int i);
int		render(t_data *data);

#endif