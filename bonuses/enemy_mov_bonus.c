/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_mov_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:52:32 by alarose           #+#    #+#             */
/*   Updated: 2024/07/02 16:55:03 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	enemy_right(t_data *data, int i)
{
	int	player_x;
	int	player_y;

	player_x = data->img[PLAYER].x;
	player_y = data->img[PLAYER].y;
	if ((data->enemies[i].x) + 1 == player_x && data->enemies[i].y == player_y)
		return(lose(data));
	go_right(data, ENEMY);
	set_new_position(data, data->img[ENEMY].x,data->img[ENEMY].y, i);
}

static void	enemy_down(t_data *data, int i)
{
	int	player_x;
	int	player_y;

	player_x = data->img[PLAYER].x;
	player_y = data->img[PLAYER].y;
	if ((data->enemies[i].x) == player_x && (data->enemies[i].y) + 1 == player_y)
		return(lose(data));
	go_down(data, ENEMY);
	set_new_position(data, data->img[ENEMY].x,data->img[ENEMY].y, i);
}

static void	enemy_left(t_data *data, int i)
{
	int	player_x;
	int	player_y;

	player_x = data->img[PLAYER].x;
	player_y = data->img[PLAYER].y;
	if ((data->enemies[i].x) - 1 == player_x && data->enemies[i].y == player_y)
		return(lose(data));
	go_left(data, ENEMY);
	set_new_position(data, data->img[ENEMY].x,data->img[ENEMY].y, i);
}

static void	enemy_up(t_data *data, int i)
{
	int	player_x;
	int	player_y;

	player_x = data->img[PLAYER].x;
	player_y = data->img[PLAYER].y;
	if ((data->enemies[i].x) == player_x && (data->enemies[i].y) - 1 == player_y)
		return(lose(data));
	go_up(data, ENEMY);
	set_new_position(data, data->img[ENEMY].x,data->img[ENEMY].y, i);
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
		rand_nb = rand() % 4;
		if (rand_nb == 0)
			enemy_right(data, i);
		if (rand_nb == 1)
			enemy_down(data, i);
		if (rand_nb == 2)
			enemy_left(data, i);
		if (rand_nb == 3)
			enemy_up(data, i);
		i++;
	}
	i = 0;
	return (0);
}