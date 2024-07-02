/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_handler_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:05:30 by alarose           #+#    #+#             */
/*   Updated: 2024/07/02 15:05:00 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	handle_input(int keysym, t_data *data)
{
	static int					nb_moves = 0;
	int							i;
	const t_keycode_f_mapping	f_table[] = {
	{XK_d, go_right},
	{XK_a, go_left},
	{XK_w, go_up},
	{XK_s, go_down},
	{XK_Escape, close_game}
	};
	int							ret;

	if (data->map.map_layout[data->img[PLAYER].y][data->img[PLAYER].x] == 'P')
		data->img[PLAYER].move_out_i_img = BG;
	i = 0;
	while ((long unsigned)i < (sizeof(f_table) / sizeof(f_table[0])))
	{
		if (f_table[i].keycode == keysym)
		{
			ret = f_table[i].func(data, PLAYER);
			if (ret)
				return (display_banner(data, nb_moves += ret), 1);
		}
		i++;
	}
	return (RET_ERR);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

void	clean_quit(t_data *data)
{
	int	i;

	i = 0;
	if (data->map.map_layout)
		free_map(data->map.map_layout);
	while (i < NB_IMAGES)
	{
		if (data->img[i].img)
			mlx_destroy_image(data->mlx, data->img[i].img);
		i++;
	}
	if (data->enemies)
		free(data->enemies);
	return ;
}

void	win(t_data *data)
{
	void	*win_img;
	int		img_width;
	int		img_height;

	data->game_over = 1;
	win_img = mlx_xpm_file_to_image(data->mlx, \
	WIN_IMG_PATH, &img_width, &img_height);
	mlx_clear_window(data->mlx, data->mlx_win);
	mlx_put_image_to_window(data->mlx, data->mlx_win, win_img, \
	(data->map.width * TILE_SIZE / 2) - (img_width / 2), (\
	data->map.height * TILE_SIZE / 2) - (img_height / 2));
	mlx_destroy_image(data->mlx, win_img);
	ft_printf(GREEN "\n\n\
	░█──░█ ░█▀▀▀█ ░█─░█ 　 ░█──░█ ▀█▀ ░█▄─░█ █ \n\
	░█▄▄▄█ ░█──░█ ░█─░█ 　 ░█░█░█ ░█─ ░█░█░█ ▀ \n\
	──░█── ░█▄▄▄█ ─▀▄▄▀ 　 ░█▄▀▄█ ▄█▄ ░█──▀█ ▄\n\n" RESET);
	return ;
}

void	lose(t_data *data) //CHANGE TO LOSE
{
	void	*win_img;
	int		img_width;
	int		img_height;

	data->game_over = 1;
	win_img = mlx_xpm_file_to_image(data->mlx, \
	GA_IMG_PATH, &img_width, &img_height);
	mlx_clear_window(data->mlx, data->mlx_win);
	mlx_put_image_to_window(data->mlx, data->mlx_win, win_img, \
	(data->map.width * TILE_SIZE / 2) - (img_width / 2), (\
	data->map.height * TILE_SIZE / 2) - (img_height / 2));
	mlx_destroy_image(data->mlx, win_img);
	ft_printf(RED "\n\n\
░██████╗░░█████╗░███╗░░░███╗███████╗  ░█████╗░██╗░░░██╗███████╗██████╗░\n\
██╔════╝░██╔══██╗████╗░████║██╔════╝  ██╔══██╗██║░░░██║██╔════╝██╔══██╗\n\
██║░░██╗░███████║██╔████╔██║█████╗░░  ██║░░██║╚██╗░██╔╝█████╗░░██████╔╝\n\
██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░  ██║░░██║░╚████╔╝░██╔══╝░░██╔══██╗\n\
╚██████╔╝██║░░██║██║░╚═╝░██║███████╗  ╚█████╔╝░░╚██╔╝░░███████╗██║░░██║\n\
░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝  ░╚════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝\n" RESET);
	return ;
}

int	close_game(t_data *data, int i)
{
	clean_quit(data);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}
	return (i);
}
