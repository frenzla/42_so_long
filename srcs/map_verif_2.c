/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:10:42 by alarose           #+#    #+#             */
/*   Updated: 2024/06/17 18:32:27 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_chars(char ***map)
{
	int	i;
	int	k;

	if (!(*map))
		return (ft_printf(RED"Error\nUnknown map\n"RESET), RET_ERR);
	i = 0;
	while ((*map)[i])
	{
		k = 0;
		while ((*map)[i][k])
		{
			if (!is_in_charset((*map)[i][k]))
				return (ft_printf(RED"Error\n	\
					Unknown char in map\n"RESET), RET_ERR);
			k++;
		}
		i++;
	}
	return (1);
}

int	is_in_charset(char c)
{
	const char	charset[] = {'0', '1', 'P', 'C', 'E', 0};
	int			i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (RET_ERR);
}

int	check_external_walls(char ***map, int nb_lines)
{
	int	x;
	int	y;
	int	len;

	if (!(*map) || !nb_lines || nb_lines < 3)
		return (ft_printf(RED"Error\nUnvalid map\n"RESET), RET_ERR);
	y = 0;
	len = ft_strlen((*map)[y]);
	while ((*map)[y])
	{
		x = 0;
		while ((*map)[y][x])
		{
			if (y == 0 || y == nb_lines - 2 || x == 0 || x == len - 1)
				if ((*map)[y][x] != '1')
					return (ft_printf(RED"Error\n	\
					Map should be surrounded by walls\n"RESET), RET_ERR);
			x++;
		}
		y++;
	}
	return (1);
}

//flood fill