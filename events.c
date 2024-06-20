/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:31:06 by alarose           #+#    #+#             */
/*   Updated: 2024/06/11 09:38:08 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_input(int keysym, t_data *data)
{

	if (keysym == XK_Right)
	{
		go_right(&(data->img[CARROT]));
	}
	return (0);
}

void	go_right(t_img *img)
{
	img->x += 50;
}

void	go_left(t_img *img)
{
	img->x -= 50;
}

void	go_up(t_img *img)
{
	img->y -= 50;
}

void	go_down(t_img *img)
{
	img->y += 50;
}