/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_count_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:22 by alarose           #+#    #+#             */
/*   Updated: 2024/06/27 19:31:42 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	display_nb_moves(t_data *data , int nb_moves)
{
	char	*str;

	mlx_set_font(data->mlx, data->mlx_win, "-schumacher-clean-bold-r-normal--15-150-75-75-c-90-iso646.1991-irv");
	str = ft_strjoin("NB MOVES : ", ft_itoa(nb_moves));
	if (!str)
		return (RET_ERR);
	mlx_string_put(data->mlx, data->mlx_win, 10, (data->map.height + 1) * TILE_SIZE - 12, 0xcccccc, str);
	free(str);
	return (1);
}
