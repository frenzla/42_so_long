/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:10:42 by alarose           #+#    #+#             */
/*   Updated: 2024/06/19 11:10:04 by alarose          ###   ########.fr       */
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
			if (y == 0 || y == nb_lines - 1 || x == 0 || x == len - 1)
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

#include <unistd.h>

int	position_is_valid(int y, int x, char ***map, int nb_lines)
{
	printf("Char = %c\n", (*map)[y][x]);
	if (x < 1 || x > strlen((*map)[0]) - 2 || y < 0 || y > nb_lines - 2)
		return (0);
	if ((*map)[y][x] == '0' || (*map)[y][x] == 'E' || (*map)[y][x] == 'C')
		return (1);
	return (0);
}

int	there_is_a_valid_path(int y, int x, char **map, int nb_lines, int nb_collectibles)
{
	char	temp;

	if (!position_is_valid(y, x, &map, nb_lines))
		return (0);
	if (map[y][x] == 'E' && nb_collectibles == 0)
		return (1);
	if (map[y][x] == 'C')
		(nb_collectibles)--;
	temp = map[y][x];
	map[y][x] = '-';
	if (there_is_a_valid_path(y, x + 1, map, nb_lines, nb_collectibles) || \
		there_is_a_valid_path(y, x - 1, map, nb_lines, nb_collectibles) || \
		there_is_a_valid_path(y + 1, x, map, nb_lines, nb_collectibles) || \
		there_is_a_valid_path(y - 1, x, map, nb_lines, nb_collectibles))
		return (1);
	map[y][x] = temp;
	if (temp == 'C')
		nb_collectibles++;
	return (0);
}

int	main(int argc, char **argv)
{
	char	**map;
	int		ret;
	int		i;
	int		nb_lines;

	map = NULL;
	//check if more than 1 elements in argv
	if (argc != 2)
		return (ft_printf("Error\nIncorrect input. Please enter map path (only)"), 1);

	//parse map
	ret = get_map(argv[1], &map);
	if (!map || ret == RET_ERR)
		return (1);

	//show map
	nb_lines = 0;
	while (map[nb_lines])
		printf("%s\n", map[nb_lines++]);

	printf(GREEN"NB LINES: %d\n" RESET, nb_lines);
	printf(BLUE"Len: %ld\n" RESET, ft_strlen(map[0]));

	ret = position_is_valid(1, 34, &map, nb_lines);
	printf("ret = %d\n", ret);
	return (0);
}