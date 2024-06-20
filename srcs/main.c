/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:52:25 by alarose           #+#    #+#             */
/*   Updated: 2024/06/20 18:00:02 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean_quit(char ***map, t_data *data)
{
	if (*map)
		free_map(*map);
	if (data->mlx)
		free(data->mlx);
	return ;
}
/*
int	main(int argc, char **argv)
{
	t_data	data;
	char	*img_paths[NB_IMAGES];
	int		ret;
	int 	nb_lines;

	//check if more than 1 elements in argv
	if (argc != 2)
		return (ft_printf("Error\nIncorrect input. Please enter map path (only)"), 1);
	//parse map
	ret = get_map(argv[1], &data);
	if (!data.map.map_layout)
	{
		printf("No working: can't find data.map.map_layout\n");
		return (1);
	}
	if (ret == RET_ERR)
	{
		printf("get_map doesn't work\n");
		return (1);
	}

	printf("ret: %d\n", ret);

	nb_lines = 0;
	while (data.map.map_layout[nb_lines])
		printf(BLUE"%s\n" RESET, data.map.map_layout[nb_lines++]);

	//initialize connection for display
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_printf("Error\nConnection between program and display couldn't be established"), 1);

	//open new window
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_LENGTH, "Hello world!");
	if (!data.mlx_win)
		return (ft_printf("Error\nNew window couldn't open"), free(data.mlx), 1);

	init_img_paths(img_paths);
	if (new_img_from_file(img_paths, &data, CARROT) == -1)
		return (ft_printf("Error\nFile could not be read"), free(data.mlx), 1); // add free & destro windows

	mlx_loop_hook(data.mlx, render, &data);

	//Register key
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, handle_input, &data);
	//mlx_key_hook(data.mlx_win, &handle_input, &data);

	//Rendering
	mlx_loop(data.mlx);

	mlx_destroy_display(data.mlx);
	free(data.mlx);

	return (0);
}*/

