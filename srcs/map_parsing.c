/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:33:46 by alarose           #+#    #+#             */
/*   Updated: 2024/06/17 16:34:08 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map(char *map_path, char ***map)
{
	int		fd;
	char	*line;
	int		nb_lines;
	int		ret;

	fd = open(map_path, O_RDONLY);
	if (fd < 1)
		return (ft_printf(RED"Error\nCouldn't open file" RESET), RET_ERR);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), ft_printf(RED"Error\nFile empty\n"RESET), RET_ERR);
	else
		nb_lines = 1;
	while (line)
	{
		nb_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ret = parse_map(open(map_path, O_RDONLY), nb_lines, map);
/*	if (!map_is_valid(map) || !map_path_valid(map_path) || ret == RET_ERR)
		return (RET_ERR);*/
	return (1);
}

int	parse_map(int fd, int nb_lines, char ***map)
{
	char	*line;
	int		i;

	line = NULL;
	*map = malloc(sizeof(char *) * (nb_lines));
	if (!*map)
		return (ft_printf(RED"Error\nMap couldn't be malloc\n"RESET), RET_ERR);
	line = get_next_line(fd);
	i = 0;
	while (i < nb_lines - 2)
	{
		(*map)[i] = malloc(sizeof(char) * (ft_strlen(line)));
		if (!((*map)[i]))
			return (ft_printf(RED"Error\n	\
				Line in Map couldn't be malloc\n"RESET), RET_ERR);
		ft_strlcpy(((*map)[i]), line, ft_strlen(line));
		i++;
		free(line);
		line = get_next_line(fd);
	}
	(*map)[i] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	ft_strlcpy(((*map)[i]), line, ft_strlen(line) + 1);
	free(line);
	(*map)[++i] = 0;
	return (1);
}

int	map_is_valid(char ***map)
{
/*	INCLUDE ALL CHECKS HERE (aggregator)
	e.g. have_all_elements(char **map)*/
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
