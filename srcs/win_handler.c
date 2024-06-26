/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:05:30 by alarose           #+#    #+#             */
/*   Updated: 2024/06/26 17:05:13 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	clean_quit(t_data *data)
{
	int	i;

	i = 0;
	if (data->map.map_layout)
		free_map(data->map.map_layout);
	while (i < NB_IMAGES)
	{
		if (data->img[i].img)
			mlx_destroy_image(data->mlx, data->img[i].img);
		i++;
	}
	return ;
}

void	win(t_data *data)
{
	void	*win_img;
	int		img_width;
	int		img_height;

	data->game_over = 1;
	win_img = mlx_xpm_file_to_image(data->mlx, WIN_IMG_PATH, &img_width, &img_height);
	mlx_clear_window(data->mlx, data->mlx_win);
	mlx_put_image_to_window(data->mlx, data->mlx_win, win_img, (data->map.width*TILE_SIZE/2)-(img_width/2), (data->map.height*TILE_SIZE/2)-(img_height/2));
	mlx_destroy_image(data->mlx, win_img);
	ft_printf(GREEN "\n\n\
	░█──░█ ░█▀▀▀█ ░█─░█ 　 ░█──░█ ▀█▀ ░█▄─░█ █ \n\
	░█▄▄▄█ ░█──░█ ░█─░█ 　 ░█░█░█ ░█─ ░█░█░█ ▀ \n\
	──░█── ░█▄▄▄█ ─▀▄▄▀ 　 ░█▄▀▄█ ▄█▄ ░█──▀█ ▄\n\n" RESET);
	return ;
}

int	close_game(t_data *data, int i)
{
	clean_quit(data);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}
	return (i);
}
