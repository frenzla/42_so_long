/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:33:46 by alarose           #+#    #+#             */
/*   Updated: 2024/06/29 14:45:41 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	get_nb_lines(char *map_path)
{
	int		fd;
	char	*line;
	int		nb_lines;

	fd = open(map_path, O_RDONLY);
	if (fd < 1)
		return (ft_printf(RED"Error\nCouldn't open file" RESET), RET_ERR);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), ft_printf(RED"Error\nFile empty\n"RESET), RET_ERR);
	else
		nb_lines = 0;
	while (line)
	{
		nb_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nb_lines);
}

int	get_map(char *map_path, t_data *data)
{
	int		fd;
	int		ret;
	char	**temp;

	data->map.map_path = map_path;
	data->map.height = get_nb_lines(map_path);
	if (data->map.height == RET_ERR || !data->map.map_path)
		return (RET_ERR);
	fd = open(map_path, O_RDONLY);
	if (fd < 1)
		return (ft_printf(RED"Error\nCouldn't open file\n" RESET), RET_ERR);
	ret = parse_map(fd, data);
	close(fd);
	if (!map_is_valid(&(data->map.map_layout), data->map.height) || \
		!map_path_valid(map_path) || ret == RET_ERR)
		return (RET_ERR);
	if (get_map_info(data) == RET_ERR)
		return (ft_printf(RED"Error\nCouldn't get map data\n" RESET), RET_ERR);
	temp = copy_map(data->map.map_layout, data->map.height);
	data->map.free_space = 0;
	if (!path_ok(data->map.start_y, data->map.start_x, data, temp))
		return (free_map(temp), ft_printf(RED"Error\n\
No valid path in map\n" RESET), RET_ERR);
	return (free_map(temp), 1);
}

int	parse_map(int fd, t_data *data)
{
	char	*line;
	int		i;

	data->map.map_layout = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.map_layout)
		return (ft_printf(RED"Error\n	\
		Map couldn't be malloc\n"RESET), RET_ERR);
	line = get_next_line(fd);
	i = 0;
	while (i < data->map.height - 1)
	{
		(data->map.map_layout)[i] = malloc(sizeof(char) * (ft_strlen(line)));
		if (!((data->map.map_layout)[i]))
			return (ft_printf(RED"Error\n	\
				Line in Map couldn't be malloc\n"RESET), RET_ERR);
		ft_strlcpy((data->map.map_layout)[i], line, ft_strlen(line));
		i++;
		free(line);
		line = get_next_line(fd);
	}
	(data->map.map_layout)[i] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	ft_strlcpy((data->map.map_layout)[i], line, ft_strlen(line) + 1);
	free(line);
	(data->map.map_layout)[++i] = 0;
	return (1);
}

int	map_is_valid(char ***map, int nb_lines)
{
	if (have_one_exit(map) && have_one_start(map) && \
		have_collectibles(map) && is_rectangle(map) && \
		check_chars(map) && check_external_walls(map, nb_lines))
		return (1);
	else
		return (RET_ERR);
}
