/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:05:04 by alarose           #+#    #+#             */
/*   Updated: 2024/07/04 12:11:56 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_imgs_path(char **img_paths)
{
	int	i;

	i = 0;
	while (i < NB_IMAGES)
	{
		if (img_paths[i])
			free(img_paths[i]);
		i++;
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

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

void	set_new_position(t_data *data, int x, int y, int i)
{
		data->map.map_layout[data->enemies[i].y][data->enemies[i].x] = '0';
		data->map.map_layout[y][x] = 'K';
		data->enemies[i].x = x;
		data->enemies[i].y = y;
}
