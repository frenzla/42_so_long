/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation_tests.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:49:18 by alarose           #+#    #+#             */
/*   Updated: 2024/06/12 19:22:18 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;
	char	*img_paths[NB_IMAGES];
	char 	**map;
	char	*map_path = "./maps/mapOK.ber";
	int		fd;
	char	*line;
	int		nb_lines;

	fd = open(map_path, O_RDONLY);
	printf("\n%d\n", fd);

	line = get_next_line(fd);
	printf("%s", line);
		if (!line)
		return (close(fd), ft_printf("Error\nMap is empty"), NULL);
	else
		nb_lines = 1;
	printf("          %d\n", nb_lines);
	while (line)
	{
		nb_lines++;
		free(line);
		line = get_next_line(fd);
		printf("%s", line);
		printf("          %d\n", nb_lines);
	}


/*	line = get_next_line(fd);
	printf("%s\n", line);*/

/*	map = get_map(argv[1]);
	if (!map)
		return (1);*/

	return (0);
}