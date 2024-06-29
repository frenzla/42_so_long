/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_events_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:01:28 by alarose           #+#    #+#             */
/*   Updated: 2024/06/29 17:35:42 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	handle_no_event(t_data *data)
{
	static int	i = 0;

	i++;
	if (i % 4000 == 0)
	{
		printf("i = %d\n", i); //delete
		i = 0;
		move_enemies(data);
	}
	if (i % 8000 == 0) //can change interval for reset (if other event need larger interval)
		i = 0; // reset for i not to go beyond int max
	return (0);
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
		{
			go_right(data, ENEMY);
			set_new_position(data, data->img[ENEMY].x++,data->img[ENEMY].y, i);
		}
		if (rand_nb == 1)
		{
			go_down(data, ENEMY);
			set_new_position(data, data->img[ENEMY].x,data->img[ENEMY].y++, i);
		}
		if (rand_nb == 2)
		{
			go_left(data, ENEMY);
			set_new_position(data, data->img[ENEMY].x--,data->img[ENEMY].y, i);
		}
		if (rand_nb == 3)
		{
			go_up(data, ENEMY);
			set_new_position(data, data->img[ENEMY].x++,data->img[ENEMY].y--, i);
		}
		i++;
	}
	k = 0; //delete
	while (k < data->map.height) // delete
		printf("%s\n", data->map.map_layout[k++]); // delete
	return (0);
}
