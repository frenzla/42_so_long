/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:33:46 by alarose           #+#    #+#             */
/*   Updated: 2024/06/19 17:20:40 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	char	*line;
	int		ret;

	data->map.height = get_nb_lines(map_path);
	if (data->map.height == RET_ERR)
		return (RET_ERR);
	fd = open(map_path, O_RDONLY);
	if (fd < 1)
		return (ft_printf(RED"Error\nCouldn't open file" RESET), RET_ERR);
	ret = parse_map(fd, data);
	close(fd);
	if (!map_is_valid(&(data->map.map_layout), data->map.height) ||	\
		!map_path_valid(map_path) || ret == RET_ERR) // here
		return (RET_ERR);
	return (1);
}

int	parse_map(int fd, t_data *data)
{
	char	*line;
	int		i;

	data->map.map_layout = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.map_layout)
		return (close(fd), ft_printf(RED"Error\n	\
		Map couldn't be malloc\n"RESET), RET_ERR);
	line = get_next_line(fd);
	i = 0;
	while (i < data->map.height - 1)
	{
		(data->map.map_layout)[i] = malloc(sizeof(char) * (ft_strlen(line)));
		if (!((data->map.map_layout)[i]))
			return (close(fd), ft_printf(RED"Error\n	\
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

int	free_map(char ***map)
{
	int	i;

	i = 0;
	while ((*map)[i])
	{
		free((*map)[i]);
		(*map)[i] = NULL;
		i++;
	}
	free(*map);
	(*map) = NULL;
}
