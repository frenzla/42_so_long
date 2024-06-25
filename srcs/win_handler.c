/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:05:30 by alarose           #+#    #+#             */
/*   Updated: 2024/06/25 16:55:10 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	win(t_data *data)
{
	void	*win_img;
	int		img_width;
	int		img_height;

	data->game_over = 1;
	win_img = mlx_xpm_file_to_image(data->mlx, WIN_IMG_PATH, &img_width, &img_height);
	mlx_clear_window(data->mlx, data->mlx_win);
	mlx_put_image_to_window(data->mlx, data->mlx_win, win_img, (data->map.width*TILE_SIZE/2)-(img_width/2), (data->map.height*TILE_SIZE/2)-(img_height/2));
	return ;
}

int	close_win(t_data *data, int player_i)
{
	//(void)player_i;
	printf("HELLO!");
	if (data->mlx_win)
	{
		clean_quit(data);
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	return (0);
}
