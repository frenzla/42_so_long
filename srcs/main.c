/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:52:25 by alarose           #+#    #+#             */
/*   Updated: 2024/07/03 16:00:06 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_data(t_data *data)
{
	int	i;

	data->mlx = NULL;
	data->mlx_win = NULL;
	data->map.map_path = NULL;
	data->map.map_layout = NULL;
	i = 0;
	while (i < NB_IMAGES)
	{
		data->img[i].img = NULL;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	*img_paths[NB_IMAGES];

	if (argc != 2)
		return (ft_printf(RED "Error\nIncorrect input" RESET), 1);
	init_data(&data);
	if (!get_map(argv[1], &data))
		return (close_game(&data, 0), 1);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_printf("Error\nMinilibX error"), close_game(&data, 0), 1);
	data.mlx_win = mlx_new_window(data.mlx, data.map.width * TILE_SIZE, \
	data.map.height * TILE_SIZE, "Hello world!");
	if (!data.mlx_win)
		return (ft_printf("Error\nNew window couldn't open"), close_game(&data, 0), 1);
	if (!init_imgs(img_paths, &data))
		return (close_game(&data, 0), 1);
	data.game_over = 0;
	render_map(&data);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, \
	close_game, &data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, handle_input, &data);
	mlx_loop(data.mlx);
	return (0);
}
