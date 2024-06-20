/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:52:25 by alarose           #+#    #+#             */
/*   Updated: 2024/06/12 18:34:36 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;
	char	*img_paths[NB_IMAGES];
	char 	**map;

	//check if more than 1 elements in argv
	if (argc != 2)
		return (ft_printf("Error\nIncorrect input. Please enter only the map path"), 1);

	//parse map
	map = get_map(argv[1]);
	if (!map)
		return (1);

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
}