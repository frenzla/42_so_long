/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_mov_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:52:32 by alarose           #+#    #+#             */
/*   Updated: 2024/07/02 18:48:18 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	enemy_right(t_data *data, int i, int enemy_move)
{
	int	player_x;
	int	player_y;

	player_x = data->img[PLAYER].x;
	player_y = data->img[PLAYER].y;
	if ((data->enemies[i].x) + 1 == player_x && data->enemies[i].y == player_y)
		return(lose(data));
	go_right(data, enemy_move);
	set_new_position(data, data->img[enemy_move].x,data->img[enemy_move].y, i);
}

static void	enemy_down(t_data *data, int i, int enemy_move)
{
	int	player_x;
	int	player_y;

	player_x = data->img[PLAYER].x;
	player_y = data->img[PLAYER].y;
	if ((data->enemies[i].x) == player_x && (data->enemies[i].y) + 1 == player_y)
		return(lose(data));
	go_down(data, enemy_move);
	set_new_position(data, data->img[enemy_move].x,data->img[enemy_move].y, i);
}

static void	enemy_left(t_data *data, int i, int enemy_move)
{
	int	player_x;
	int	player_y;

	player_x = data->img[PLAYER].x;
	player_y = data->img[PLAYER].y;
	if ((data->enemies[i].x) - 1 == player_x && data->enemies[i].y == player_y)
		return(lose(data));
	go_left(data, enemy_move);
	set_new_position(data, data->img[enemy_move].x,data->img[enemy_move].y, i);
}

static void	enemy_up(t_data *data, int i, int enemy_move)
{
	int	player_x;
	int	player_y;

	player_x = data->img[PLAYER].x;
	player_y = data->img[PLAYER].y;
	if ((data->enemies[i].x) == player_x && (data->enemies[i].y) - 1 == player_y)
		return(lose(data));
	go_up(data, enemy_move);
	set_new_position(data, data->img[enemy_move].x, data->img[enemy_move].y, i);
}

void	set_enemy_data(t_data *data, int enemy_move, int i)
{
		data->img[enemy_move].y = data->enemies[i].y;
		data->img[enemy_move].x = data->enemies[i].x;
		data->img[enemy_move].move_out_i_img = BG;
		if (enemy_move == 7)
			enemy_up(data, i, enemy_move);
		if (enemy_move == 8)
			enemy_right(data, i, enemy_move);
		if (enemy_move == 9)
			enemy_down(data, i, enemy_move);
		if (enemy_move == 10)
			enemy_left(data, i, enemy_move);
}

int	move_enemies(t_data *data)
{
	int	i;
	int	rand_nb;

	i = 0;
	while (i < data->map.nb_enemies)
	{
		data->img[ENEMY].y = data->enemies[i].y;
		data->img[ENEMY].x = data->enemies[i].x;
		data->img[ENEMY].move_out_i_img = BG;
		rand_nb = 7 + rand() % 4;
		set_enemy_data(data, rand_nb, i);
		i++;
	}
	i = 0;
	return (0);
}
