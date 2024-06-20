/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:31:06 by alarose           #+#    #+#             */
/*   Updated: 2024/06/13 18:37:44 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_input(int keysym, t_data *data)
{
	static int			NB_moves = 0;
	int					i;
	keycode_f_mapping	f_table[] = {
		{XK_Right, go_right},
		{XK_d, go_right},
		{XK_Left, go_left},
		{XK_a, go_left},
		{XK_Up, go_up},
		{XK_w, go_up},
		{XK_Down, go_down},
		{XK_s, go_down}
	};

	i = 0;
	while (i < (sizeof(f_table)/sizeof(f_table[0])))
	{
		if (f_table[i].keycode == keysym)
		{
			f_table[i].func(&(data->img[CARROT]));
			ft_printf("Move number %d\n", ++NB_moves);
			return (0);
		}
		i++;
	}
	return (ft_printf("Unknown keystroke: 0x%x\n", keysym), -1);
}

void	go_right(t_img *img)
{
	img->x += TILE_SIZE;
}

void	go_left(t_img *img)
{
	img->x -= TILE_SIZE;
}

void	go_up(t_img *img)
{
	img->y -= TILE_SIZE;
}

void	go_down(t_img *img)
{
	img->y += TILE_SIZE;
}