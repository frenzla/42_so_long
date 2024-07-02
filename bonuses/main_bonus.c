/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:52:25 by alarose           #+#    #+#             */
/*   Updated: 2024/07/02 15:40:11 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	init_prog(t_data *data, char **img_paths)
{
	srand(time(NULL));
	define_enemies(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_printf("Error\nMinilibX error"), 1);
	data->mlx_win = mlx_new_window(data->mlx, data->map.width * TILE_SIZE, \
	(data->map.height + 1) * TILE_SIZE, "Hello world!");
	if (!data->mlx_win)
		return (ft_printf("Error\nNew window couldn't open"), free(data->mlx), 1);
	if (!init_imgs(img_paths, data))
		return (close_game(data, 0), 1);
	data->game_over = 0;
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	*img_paths[NB_IMAGES];

	if (argc != 2)
		return (ft_printf(RED "Error\nIncorrect input" RESET), 1);
	if (!get_map(argv[1], &data))
		return (1);
	init_prog(&data, img_paths);
	render_map(&data);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, \
	close_game, &data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, handle_input, &data);
	mlx_loop_hook(data.mlx, handle_no_event, &data),
	mlx_loop(data.mlx);
	return (0);
}
