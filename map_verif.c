/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:33:46 by alarose           #+#    #+#             */
/*   Updated: 2024/06/12 19:38:12 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char **get_map(char *map_path)
{
	int		fd;
	char	*line;
	int		nb_lines;
	char	**map;
	int		ret;

	fd = open(map_path, O_RDONLY);
	if (fd < 1)
		return (ft_printf("Error\nCouldn't open map: invalid path"), NULL);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), ft_printf("Error\nMap is empty"), NULL);
	else
		nb_lines = 1;
	while (line)
	{
		nb_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd); // tested until here
	ret = parse_map(open(map_path, O_RDONLY), nb_lines, map);
	if (!map_is_valid(map) || !map_path_valid(map_path) || ret == RET_ERR)
		return (NULL);
	return (map);
}

int parse_map(int fd, int nb_lines, char **map)
{
	char	*line;
	int		i;

	map = malloc(sizeof(char *) * (nb_lines + 1));
	if (!map)
		return (ft_printf("Error\nCouldn't create map (malloc error)"), RET_ERR);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map[i] = line;
		i++;
		free(line);
		get_next_line(fd);
	}
	map[i] = 0;
	return (1);
}

int	map_is_valid(char **map)
{
/*	INCLUDE ALL CHECKS HERE (aggregator)
	e.g. have_all_elements(char **map)*/
}

int	map_path_valid(char *map_path)
{
	//check if "*.ber"
}

int	have_all_elements(char **map)
{
	int	count_exit;
	int	count_coll;
	int	count_sp;

}