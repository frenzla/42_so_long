/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:10:42 by alarose           #+#    #+#             */
/*   Updated: 2024/06/25 09:45:28 by alarose          ###   ########.fr       */
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

//flood fill

#include <unistd.h>

int	position_is_valid(int y, int x, char ***map, int nb_lines)
{
	if (x < 1 || x > ft_strlen((*map)[0]) - 2 || y < 0 || y > nb_lines - 2)
		return (0);
	if ((*map)[y][x] == '0' || (*map)[y][x] == 'E' ||	\
		(*map)[y][x] == 'C' || (*map)[y][x] == 'P')
		return (1);
	return (0);
}

//#include <time.h> // For below checks. Must stay here
/*  Add this inside "path_ok" to see filling up in real time:
	struct timespec req;	// Define the timespec structure for sleeping half a second
	req.tv_sec = 0;				// Seconds
	req.tv_nsec = 100000000L;	// Nanoseconds (500 milliseconds)
	nanosleep(&req, (struct timespec *)NULL); // Sleep

	//print map for checks
	int	i = 0;
	while (map[i]) // delete when checks are done
		printf("%s\n", map[i++]); // delete when checks are done
*/

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
	if (path_ok(y, x + 1, data, map) || path_ok(y, x - 1, data, map) || \
		path_ok(y + 1, x, data, map) || path_ok(y - 1, x, data, map))
		return (1);
	return (RET_ERR);
}
/*
int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;
	int		nb_lines;

	if (argc != 2)
		return (ft_printf("Error\nIncorrect input. Please enter map path (only)"), 1);

	//parse map
	ret = get_map(argv[1], &data);
	if (!data.map.map_layout || ret == RET_ERR)
		printf(RED "parsing failed OR map not valid, but here carrying on...\n" RESET);

	//show map & info
	nb_lines = 0;
	while (data.map.map_layout[nb_lines])
		printf(BLUE"%s\n" RESET, data.map.map_layout[nb_lines++]);
	printf(GREEN "Map path = %s\n", data.map.map_path);
	printf("Map width = %d & Map height = %d\n", data.map.width, data.map.height);
	printf("Starting position: y = %d | x = %d\n", data.map.start_y, data.map.start_x);
	printf("NB collectibles = %d\n" RESET, data.map.nb_collectibles);

	//Flood fill
	ret = path_ok(data.map.start_y, data.map.start_x, &data, data.map.map_layout);
	printf("ret = %d\n", ret);
	return (0);
}
*/
/*
int	main(int argc, char **argv)
{
	int fd;
	t_data data;
	int ret;
	int nb_lines;

	data.map.map_path = argv[1];
	data.map.height = get_nb_lines(argv[1]);

	fd = open(argv[1], O_RDONLY);
	ret = parse_map(fd, &data);
	close(fd);

	nb_lines = 0;
	while (data.map.map_layout[nb_lines])
		printf(BLUE"%s\n" RESET, data.map.map_layout[nb_lines++]);

	ret = get_map_info(&data);

	printf(GREEN "Map path = %s\n", data.map.map_path);
	printf("Map width = %d & Map height = %d\n", data.map.width, data.map.height);
	printf("Starting position: y = %d | x = %d\n", data.map.start_y, data.map.start_x);
	printf("NB collectibles = %d\n" RESET, data.map.nb_collectibles);

	nb_lines = 0;
	while (data.map.map_layout[nb_lines])
		printf(BLUE"%s\n" RESET, data.map.map_layout[nb_lines++]);

}
*/