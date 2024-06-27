/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_count_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:22 by alarose           #+#    #+#             */
/*   Updated: 2024/06/27 15:31:07 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	display_nb_moves(t_data *data , int nb_moves)
{
	mlx_string_put(data->mlx, data->mlx_win, 10, 3, 0x00FFFFFF, "NB MOVES:");
	return (nb_moves);
}