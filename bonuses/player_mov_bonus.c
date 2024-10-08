/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:31:06 by alarose           #+#    #+#             */
/*   Updated: 2024/07/02 19:17:19 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	adjust_map(t_data *data, int i_img)
{
	if (data->img[i_img].move_in == '0')
		data->img[i_img].move_out_i_img = BG;
	else if (data->img[i_img].move_in == 'C')
	{
		data->img[i_img].move_out_i_img = BG;
		data->map.map_layout[data->img[i_img].y][data->img[i_img].x] = BG_CODE;
		data->map.nb_collectibles--;
	}
	else if (data->img[i_img].move_in == 'E')
	{
		if (data->map.nb_collectibles == 0)
			return (win(data), RET_ERR);
		else
		{
			data->img[i_img].move_out_i_img = EXIT;
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
	char	next_tile;

	next_tile = data->map.map_layout[data->img[i_img].y][data->img[i_img].x \
	+ 1];
	if (next_tile == '1' || data->game_over || (i_img >= ENEMY && \
	(next_tile == 'C' || next_tile == 'E' || next_tile == 'K')))
		return (RET_ERR);
	if (i_img == PLAYER && next_tile == 'K')
		return (lose(data), RET_ERR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	data->img[data->img[i_img].move_out_i_img].img, data->img[i_img].x * \
	TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	data->img[i_img].move_in = next_tile;
	(data->img[i_img].x)++;
	return (adjust_map(data, i_img));
}

int	go_left(t_data *data, int i_img)
{
	char	next_tile;

	next_tile = data->map.map_layout[data->img[i_img].y][data->img[i_img].x \
	- 1];
	if (next_tile == '1' || data->game_over || (i_img >= ENEMY && \
	(next_tile == 'C' || next_tile == 'E' || next_tile == 'K')))
		return (RET_ERR);
	if (i_img == PLAYER && next_tile == 'K')
		return (lose(data), RET_ERR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	data->img[data->img[i_img].move_out_i_img].img, data->img[i_img].x * \
	TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	data->img[i_img].move_in = next_tile;
	(data->img[i_img].x)--;
	return (adjust_map(data, i_img));
}

int	go_up(t_data *data, int i_img)
{
	char	next_tile;

	next_tile = data->map.map_layout[data->img[i_img].y \
	- 1][data->img[i_img].x];
	if (next_tile == '1' || data->game_over || (i_img >= ENEMY && \
	(next_tile == 'C' || next_tile == 'E' || next_tile == 'K')))
		return (RET_ERR);
	if (i_img == PLAYER && next_tile == 'K')
		return (lose(data), RET_ERR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	data->img[data->img[i_img].move_out_i_img].img, data->img[i_img].x * \
	TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	data->img[i_img].move_in = next_tile;
	(data->img[i_img].y)--;
	return (adjust_map(data, i_img));
}

int	go_down(t_data *data, int i_img)
{
	char	next_tile;

	next_tile = data->map.map_layout[data->img[i_img].y \
	+ 1][data->img[i_img].x];
	if (next_tile == '1' || data->game_over || (i_img >= ENEMY && \
	(next_tile == 'C' || next_tile == 'E' || next_tile == 'K')))
		return (RET_ERR);
	if (i_img == PLAYER && next_tile == 'K')
		return (lose(data), RET_ERR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	data->img[data->img[i_img].move_out_i_img].img, data->img[i_img].x * \
	TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	data->img[i_img].move_in = next_tile;
	(data->img[i_img].y)++;
	return (adjust_map(data, i_img));
}
