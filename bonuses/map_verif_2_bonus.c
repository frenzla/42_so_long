/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif_2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:10:42 by alarose           #+#    #+#             */
/*   Updated: 2024/06/29 11:30:39 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
				return (ft_printf(RED"Error\n\
Unknown char in map\n"RESET), RET_ERR);
			k++;
		}
		i++;
	}
	return (1);
}

int	is_in_charset(char c)
{
	const char	charset[] = {'0', '1', 'P', 'C', 'E', 'X', 0};
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
			if (y == 0 || y == nb_lines - 1 || x == 0 || x == len - 1)
				if ((*map)[y][x] != '1')
					return (ft_printf(RED"Error\n\
Map should be surrounded by walls\n"RESET), RET_ERR);
			x++;
		}
		y++;
	}
	return (1);
}

int	position_is_valid(int y, int x, char ***map, int nb_lines)
{
	if (x < 1 || (unsigned long) x > \
	ft_strlen((*map)[0]) - 2 || y < 0 || y > nb_lines - 2)
		return (0);
	if ((*map)[y][x] == '0' || (*map)[y][x] == 'E' || \
		(*map)[y][x] == 'C' || (*map)[y][x] == 'P')
		return (1);
	return (0);
}

int	path_ok(int y, int x, t_data *data, char **map)
{
	static int	got_exit = 0;
	static int	collec = 0;

	if (!map || !data->map.height || data->map.height < 3)
		return (ft_printf(RED"Error\nUnvalid map\n"RESET), RET_ERR);
	if (!position_is_valid(y, x, &map, data->map.height))
		return (RET_ERR);
	if (map[y][x] == 'E')
		got_exit = 1;
	if (map[y][x] == 'C')
		collec++;
	if (got_exit && collec == data->map.nb_collectibles)
		return (got_exit = 0, collec = 0, 1);
	map[y][x] = 'X';
	data->map.free_space++;
	if (path_ok(y, x + 1, data, map) || path_ok(y, x - 1, data, map) || \
		path_ok(y + 1, x, data, map) || path_ok(y - 1, x, data, map))
		return (1);
	return (RET_ERR);
}
