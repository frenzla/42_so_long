/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:52:25 by alarose           #+#    #+#             */
/*   Updated: 2024/06/26 15:04:33 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;
	char	*img_paths[NB_IMAGES];
	int		ret;
	int 	nb_lines;

	//check if more than 1 elements in argv
	if (argc != 2)
		return (ft_printf(RED "Error\nIncorrect input" RESET), 1);

	//parse map
	ret = get_map(argv[1], &data);
	if (ret == RET_ERR)
		return (1);

	//initialize connection for display
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_printf("Error\nConnection between program and display couldn't be established"), 1);

	//open new window
	data.mlx_win = mlx_new_window(data.mlx, data.map.width*TILE_SIZE, data.map.height*TILE_SIZE, "Hello world!");
	if (!data.mlx_win)
		return (ft_printf("Error\nNew window couldn't open"), free(data.mlx), 1);

	ret = init_imgs(img_paths, &data);
	if (ret == RET_ERR)
		return (close_game(&data, 0), 1); // The close_game function doesn't work if init_imgs fails

	data.game_over = 0;

	render_map(&data);

	//Register window closing event
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, close_game, &data);
	//Register key press event
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, handle_input, &data);

//	mlx_loop_hook(data.mlx, &handle_no_event, &data);

	//Rendering
	mlx_loop(data.mlx);
	return (0);
}

/*
int	handle_no_event(void *data)
{
    //This function needs to exist, but it is useless for the moment
    return (0);
}
*/
