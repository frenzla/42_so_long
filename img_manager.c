/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:50:15 by alarose           #+#    #+#             */
/*   Updated: 2024/06/12 16:24:05 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//change this function with struct name/path. Takes name I need in parameter, nothing else.
void	init_img_paths(char **img_paths)
{
	int	i;
	char *paths[NB_IMAGES] = {
		SQUARE_PATH,
		CARROT_PATH
	};

	i = 0;
	while (i < NB_IMAGES)
	{
		img_paths[i] = malloc(ft_strlen(paths[i]) + 1);
		if (img_paths[i] != NULL)
			ft_strlcpy(img_paths[i], paths[i], ft_strlen(paths[i])+1);
		i++;
	}
}

int	new_img_from_file(char **paths, t_data *data, int i)
{
	data->img[i].img = mlx_xpm_file_to_image(data->mlx, paths[i], &(data->img[i].width), &(data->img[i].height));
	if (!(data->img[i].img))
		return (MLX_ERROR);
	data->img[i].addr = mlx_get_data_addr(data->img[i].img, &(data->img[i].bits_per_pixel), &(data->img[i].line_length), &(data->img[i].endian));
	//Define position of image
/*	data->img[i].x = 300;
	data->img[i].y = 300;*/
}

int	render(t_data *data)
{
	if (data->mlx_win != NULL)
	{
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[CARROT].img, data->img[CARROT].x, data->img[CARROT].y);
			return (0);
	}
	return (-1);
}