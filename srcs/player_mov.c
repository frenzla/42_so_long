/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:31:06 by alarose           #+#    #+#             */
/*   Updated: 2024/07/02 16:50:12 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	adjust_map(t_data *data, int i_img)
{
	if (data->map.move_in == '0')
		data->map.move_out_i_img = BG;
	else if (data->map.move_in == 'C')
	{
		data->map.move_out_i_img = BG;
		data->map.map_layout[data->img[i_img].y][data->img[i_img].x] = BG_CODE;
		data->map.nb_collectibles--;
	}
	else if (data->map.move_in == 'E')
	{
		if (data->map.nb_collectibles == 0)
			return (win(data), RET_ERR);
		else
		{
			data->map.move_out_i_img = EXIT;
			mlx_put_image_to_window(data->mlx, data->mlx_win, \
			data->img[PLAYER_EXIT].img, data->img[i_img].x * TILE_SIZE, \
			data->img[i_img].y * TILE_SIZE);
			return (1);
		}
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[i_img].img, \
	data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	return (1);
}

int	go_right(t_data *data, int i_img)
{
	if (data->map.map_layout[data->img[i_img].y][data->img[i_img].x + 1] == '1' \
	|| data->game_over)
		return (RET_ERR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	data->img[data->map.move_out_i_img].img, data->img[i_img].x * TILE_SIZE, \
	data->img[i_img].y * TILE_SIZE);
	data->map.move_in = \
	data->map.map_layout[data->img[i_img].y][data->img[i_img].x + 1];
	(data->img[i_img].x)++;
	return (adjust_map(data, i_img));
}

int	go_left(t_data *data, int i_img)
{
	if (data->map.map_layout[data->img[i_img].y][data->img[i_img].x - 1] == '1' \
	|| data->game_over)
		return (RET_ERR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	data->img[data->map.move_out_i_img].img, data->img[i_img].x * TILE_SIZE, \
	data->img[i_img].y * TILE_SIZE);
	data->map.move_in = \
	data->map.map_layout[data->img[i_img].y][data->img[i_img].x - 1];
	(data->img[i_img].x)--;
	return (adjust_map(data, i_img));
}

int	go_up(t_data *data, int i_img)
{
	if (data->map.map_layout[data->img[i_img].y - 1][data->img[i_img].x] == '1' \
	|| data->game_over)
		return (RET_ERR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	data->img[data->map.move_out_i_img].img, data->img[i_img].x * TILE_SIZE, \
	data->img[i_img].y * TILE_SIZE);
	data->map.move_in = \
	data->map.map_layout[data->img[i_img].y - 1][data->img[i_img].x];
	(data->img[i_img].y)--;
	return (adjust_map(data, i_img));
}

int	go_down(t_data *data, int i_img)
{
	if (data->map.map_layout[data->img[i_img].y + 1][data->img[i_img].x] == '1' \
	|| data->game_over)
		return (RET_ERR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	data->img[data->map.move_out_i_img].img, data->img[i_img].x * TILE_SIZE, \
	data->img[i_img].y * TILE_SIZE);
	data->map.move_in = \
	data->map.map_layout[data->img[i_img].y + 1][data->img[i_img].x];
	(data->img[i_img].y)++;
	return (adjust_map(data, i_img));
}
