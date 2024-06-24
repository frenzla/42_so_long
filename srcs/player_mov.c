/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:31:06 by alarose           #+#    #+#             */
/*   Updated: 2024/06/24 12:06:44 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_input(int keysym, t_data *data)
{
	static int				nb_moves = 0;
	int						i;
	const keycode_f_mapping	f_table[] = {
	{XK_d, go_right},
	{XK_a, go_left},
	{XK_w, go_up},
	{XK_s, go_down}
	};

	if (data->map.map_layout[data->img[PLAYER].y][data->img[PLAYER].x] == 'P')
		data->map.move_out_i_img = BG;
	i = 0;
	while (i < (sizeof(f_table) / sizeof(f_table[0])))
	{
		if (f_table[i].keycode == keysym)
		{
			nb_moves += f_table[i].func(data, PLAYER);
			return (ft_printf("Move number %d\n", nb_moves), 0);
		}
		i++;
	}
	return (ft_printf("Unknown keystroke: 0x%x\n", keysym), -1);
}

int	go_right(t_data *data, int i_img)
{
	if (data->map.map_layout[data->img[i_img].y][data->img[i_img].x + 1] == '1')
		return (0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[data->map.move_out_i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);

	data->map.move_in = data->map.map_layout[data->img[i_img].y][data->img[i_img].x + 1];
	if (data->map.move_in == '0' || data->map.move_in == 'C')
		data->map.move_out_i_img = BG;
	else if (data->map.move_in == 'E' && data->map.nb_collectibles != 0)
		data->map.move_out_i_img = EXIT;
	(data->img[i_img].x)++;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	return (1);
}

int	go_left(t_data *data, int i_img)
{
	if (data->map.map_layout[data->img[i_img].y][data->img[i_img].x - 1] == '1')
		return (0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[data->map.move_out_i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);

	data->map.move_in = data->map.map_layout[data->img[i_img].y][data->img[i_img].x - 1];
	if (data->map.move_in == '0' || data->map.move_in == 'C')
		data->map.move_out_i_img = BG;
	else if (data->map.move_in == 'E' && data->map.nb_collectibles != 0)
		data->map.move_out_i_img = EXIT;
	(data->img[i_img].x)--;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	return (1);
}

int	go_up(t_data *data, int i_img)
{
	if (data->map.map_layout[data->img[i_img].y - 1][data->img[i_img].x] == '1')
		return (0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[data->map.move_out_i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);

	data->map.move_in = data->map.map_layout[data->img[i_img].y - 1][data->img[i_img].x];
	if (data->map.move_in == '0' || data->map.move_in == 'C')
		data->map.move_out_i_img = BG;
	else if (data->map.move_in == 'E' && data->map.nb_collectibles != 0)
		data->map.move_out_i_img = EXIT;
	(data->img[i_img].y)--;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	return (1);
}

int	go_down(t_data *data, int i_img)
{
	if (data->map.map_layout[data->img[i_img].y + 1][data->img[i_img].x] == '1')
		return (0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[data->map.move_out_i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);

	data->map.move_in = data->map.map_layout[data->img[i_img].y + 1][data->img[i_img].x];
	if (data->map.move_in == '0' || data->map.move_in == 'C')
		data->map.move_out_i_img = BG;
	else if (data->map.move_in == 'E' && data->map.nb_collectibles != 0)
		data->map.move_out_i_img = EXIT;
	(data->img[i_img].y)++;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	return (1);
}
