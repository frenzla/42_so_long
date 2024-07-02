/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_mov_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:52:32 by alarose           #+#    #+#             */
/*   Updated: 2024/07/02 15:00:46 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	enemy_right(t_data *data, int i)
{
	//if (data->img[ENEMY].x + 1 == data->img[PLAYER].x && data->img[ENEMY].y + 1 == data->img[PLAYER].y)
	//	return(lose(data)); // not working
	go_right(data, ENEMY);
	set_new_position(data, data->img[ENEMY].x,data->img[ENEMY].y, i);
}

static void	enemy_down(t_data *data, int i)
{
	go_down(data, ENEMY);
	set_new_position(data, data->img[ENEMY].x,data->img[ENEMY].y, i);
}

static void	enemy_left(t_data *data, int i)
{
	go_left(data, ENEMY);
	set_new_position(data, data->img[ENEMY].x,data->img[ENEMY].y, i);
}

static void	enemy_up(t_data *data, int i)
{
	go_up(data, ENEMY);
	set_new_position(data, data->img[ENEMY].x,data->img[ENEMY].y, i);
}

int	move_enemies(t_data *data)
{
	int	i;
	int	k;
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
	k = 0; //delete
	while (k < data->map.height) // delete
		printf("%s\n", data->map.map_layout[k++]); // delete
	return (0);
}