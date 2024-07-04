/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:33:46 by alarose           #+#    #+#             */
/*   Updated: 2024/07/04 11:42:07 by alarose          ###   ########.fr       */
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

static void	init_layout(t_data *data, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		data->map.map_layout = NULL;
		i++;
	}
}

int	get_map(char *map_path, t_data *data)
{
	int		fd;
	int		ret;
	char	**temp;

	data->map.height = get_nb_lines(map_path);
	if (data->map.height == RET_ERR)
		return (RET_ERR);
	init_layout(data, data->map.height);
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
	if (!temp)
		return (ft_printf(RED"Error\nCouldn't copy map\n" RESET), RET_ERR);
	if (!path_ok(data->map.start_y, data->map.start_x, data, temp))
		return (free_map(temp), ft_printf(RED"Error\n\
No valid path in map\n" RESET), RET_ERR);
	return (free_map(temp), 1);
}

static char	*trans_map(int fd, t_data *data, char *line)
{
	int	i;

	i = 0;
	while (i < data->map.height - 1)
	{
		(data->map.map_layout)[i] = malloc(sizeof(char) * (ft_strlen(line)));
		if (!((data->map.map_layout)[i]))
			return (ft_printf(RED"Error\n	\
				Line in Map couldn't be malloc\n"RESET), free(line), NULL);
		ft_strlcpy((data->map.map_layout)[i], line, ft_strlen(line));
		i++;
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

int	parse_map(int fd, t_data *data)
{
	char	*line;

	data->map.map_layout = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.map_layout)
		return (ft_printf(RED"Error\n	\
		Map couldn't be malloc\n"RESET), RET_ERR);
	line = get_next_line(fd);
	line = trans_map(fd, data, line);
	if (line == NULL)
		return (RET_ERR);
	(data->map.map_layout)[data->map.height - 1] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (((data->map.map_layout)[data->map.height - 1]) == NULL)
		return (free(line), RET_ERR);
	ft_strlcpy((data->map.map_layout)[data->map.height - 1], line, ft_strlen(line) + 1);
	free(line);
	(data->map.map_layout)[data->map.height] = 0;
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
