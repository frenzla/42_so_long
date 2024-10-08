/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_events_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:01:28 by alarose           #+#    #+#             */
/*   Updated: 2024/07/02 19:32:09 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	handle_no_event(t_data *data)
{
	static int	i = 0;

	i++;
	if (i % 20000 == 0 && data->game_over == 0)
		move_enemies(data);
	if (i % 20000 == 0)
		i = 0;
	return (0);
}
