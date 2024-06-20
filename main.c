/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:52:25 by alarose           #+#    #+#             */
/*   Updated: 2024/06/11 18:53:01 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(void)
{
	t_data	data;
	char	*img_paths[NB_IMAGES];

	//initialize connection for display
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_printf("Error\nConnection between program and display couldn't be established"), free(data.mlx), MLX_ERROR);

	//open new window
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_LENGTH, "Hello world!");
	if (!data.mlx_win)
		return (ft_printf("Error\nNew window couldn't open"), free(data.mlx), MLX_ERROR);

	init_img_paths(img_paths);
	if (new_img_from_file(img_paths, &data, CARROT) == -1)
		return (ft_printf("Error\nFile could not be read"), free(data.mlx), MLX_ERROR); // add free & destro windows

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