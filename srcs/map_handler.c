/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:52:20 by alarose           #+#    #+#             */
/*   Updated: 2024/06/20 11:15:37 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	get_map_info(t_data *data)
{
	int		nb_collectibles;
	int		i;
	int		k;

	i = -1;
	data->map.nb_collectibles = 0;
	data->map.width = ft_strlen(data->map.map_layout[i + 1]);
	while (data->map.map_layout[++i])
	{
		k = 0;
		while (data->map.map_layout[i][k])
		{
			if (data->map.map_layout[i][k] == 'P')
			{
				data->map.start_x = k;
				data->map.start_y = i;
			}
			if (data->map.map_layout[i][k++] == 'C')
				data->map.nb_collectibles++;
		}
	}
	if (!data->map.width || !data->map.start_x || !data->map.start_y || \
		!data->map.nb_collectibles)
		return (RET_ERR);
	return (1);
}

/*int	main(int argc, char **argv)
{

	t_data	data;
	int		ret;
	int		nb_lines;

	//check if more than 1 elements in argv
	if (argc != 2)
		return (ft_printf("Error\nIncorrect input. Please enter map path (only)"), 1);

	//parse map
	ret = get_map(argv[1], &data);
	if (!data.map.map_layout || ret == RET_ERR)
		return (1);

	//show map
	nb_lines = 0;
	while (data.map.map_layout[nb_lines])
		printf(BLUE"%s\n" RESET, data.map.map_layout[nb_lines++]);

	printf(GREEN "Map path = %s\n", data.map.map_path);
	printf("Map width = %d & Map height = %d\n", data.map.width, data.map.height);
	printf("Starting position: y = %d | x = %d\n", data.map.start_y, data.map.start_x);
	printf("NB collectibles = %d\n" RESET, data.map.nb_collectibles);

	return (0);
}*/