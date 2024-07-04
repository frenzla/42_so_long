/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:52:25 by alarose           #+#    #+#             */
/*   Updated: 2024/07/04 11:47:47 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_data(char **imgs_paths, t_data *data)
{
	int	i;

	data->mlx = NULL;
	data->mlx_win = NULL;
	data->map.map_layout = NULL;
	data->enemies = NULL;
	i = 0;
	while (i < NB_IMAGES)
	{
		imgs_paths[i] = NULL;
		data->img[i].img = NULL;
		data->img[i].addr = NULL;
		i++;
	}
}

int	init_prog(t_data *data, char **img_paths)
{
	srand(time(NULL));
	define_enemies(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_printf("Error\nMinilibX error"), RET_ERR);
	data->mlx_win = mlx_new_window(data->mlx, data->map.width * TILE_SIZE, \
	(data->map.height + 1) * TILE_SIZE, "Hello world!");
	if (!data->mlx_win)
		return (ft_printf("Error\nWindow couldn't open"), RET_ERR);
	if (!init_imgs(img_paths, data))
		return (RET_ERR);
	data->game_over = 0;
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	*img_paths[NB_IMAGES];

	if (argc != 2)
		return (ft_printf(RED "Error\nIncorrect input" RESET), 1);
	init_data(img_paths, &data);
	if (!get_map(argv[1], &data))
		return (close_game(&data, 0), 1);
	if (!init_prog(&data, img_paths))
		return (close_game(&data, 1), 1);
	render_map(&data);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, \
	close_game, &data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, handle_input, &data);
	mlx_loop_hook(data.mlx, handle_no_event, &data),
	mlx_loop(data.mlx);
	return (0);
}
