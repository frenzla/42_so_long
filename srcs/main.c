/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:52:25 by alarose           #+#    #+#             */
/*   Updated: 2024/06/24 12:00:07 by alarose          ###   ########.fr       */
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
		return (free(data.mlx), 1); // add free & destro windows

	render_map(&data);

	//Register key
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, handle_input, &data);

	//Rendering
	mlx_loop(data.mlx);

	mlx_destroy_display(data.mlx);
	free(data.mlx);

	return (0);
}
