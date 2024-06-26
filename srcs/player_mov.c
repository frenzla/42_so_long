/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:31:06 by alarose           #+#    #+#             */
/*   Updated: 2024/06/26 16:32:40 by alarose          ###   ########.fr       */
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
	{XK_s, go_down},
	{XK_Escape, close_game}
	};
	int						ret;

	if (data->map.map_layout[data->img[PLAYER].y][data->img[PLAYER].x] == 'P')
		data->map.move_out_i_img = BG;
	i = 0;
	while (i < (sizeof(f_table) / sizeof(f_table[0])))
	{
		if (f_table[i].keycode == keysym)
		{
			ret = f_table[i].func(data, PLAYER);
			if (ret != 0)
			{
				printf("NB_COLL: %d\n", data->map.nb_collectibles);
				return (ft_printf("Move number %d\n", nb_moves += ret), 0);
			}
		}
		i++;
	}
	return (RET_ERR);
}

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
		if (data->map.nb_collectibles == 0)
			return (win(data), RET_ERR);
		else
		{
			data->map.move_out_i_img = EXIT;
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[PLAYER_EXIT].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);
			return (RET_ERR);
		}
	return (1);
}

int	go_right(t_data *data, int i_img)
{
	if (data->map.map_layout[data->img[i_img].y][data->img[i_img].x + 1] == '1' || data->game_over)
		return (RET_ERR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[data->map.move_out_i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	data->map.move_in = data->map.map_layout[data->img[i_img].y][data->img[i_img].x + 1];
	(data->img[i_img].x)++;
	if (adjust_map(data, i_img))
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	return (1);
}

int	go_left(t_data *data, int i_img)
{
	if (data->map.map_layout[data->img[i_img].y][data->img[i_img].x - 1] == '1' || data->game_over)
		return (RET_ERR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[data->map.move_out_i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);

	data->map.move_in = data->map.map_layout[data->img[i_img].y][data->img[i_img].x - 1];
	(data->img[i_img].x)--;
	if (adjust_map(data, i_img))
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	return (1);
}

int	go_up(t_data *data, int i_img)
{
	if (data->map.map_layout[data->img[i_img].y - 1][data->img[i_img].x] == '1' || data->game_over)
		return (RET_ERR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[data->map.move_out_i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);

	data->map.move_in = data->map.map_layout[data->img[i_img].y - 1][data->img[i_img].x];
	(data->img[i_img].y)--;
	if (adjust_map(data, i_img))
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	return (1);
}

int	go_down(t_data *data, int i_img)
{
	if (data->map.map_layout[data->img[i_img].y + 1][data->img[i_img].x] == '1' || data->game_over)
		return (RET_ERR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[data->map.move_out_i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);

	data->map.move_in = data->map.map_layout[data->img[i_img].y + 1][data->img[i_img].x];
	(data->img[i_img].y)++;
	if (adjust_map(data, i_img))
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);
	return (1);
}
