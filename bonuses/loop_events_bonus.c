/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_events_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:01:28 by alarose           #+#    #+#             */
/*   Updated: 2024/07/02 15:39:25 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	handle_no_event(t_data *data)
{
	static int	i = 0;

	i++;
	if (i % 8000 == 0 && data->game_over == 0) //change this for enemy mov.
		move_enemies(data);
	if (i % 8000 == 0) //can change interval for reset (if other event need larger interval)
		i = 0; // reset for i not to go beyond int max
	return (0);
}
