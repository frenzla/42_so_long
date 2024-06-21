/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:50:15 by alarose           #+#    #+#             */
/*   Updated: 2024/06/21 13:24:41 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//change this function with struct name/path. Takes name I need in parameter, nothing else.
int	init_imgs(char **img_paths, t_data *data)
{
	int		i;
	int		ret;
	char	*paths[NB_IMAGES] = {
		WALL_PATH,
		COLL_PATH,
		EXIT_PATH,
		PLAYER_PATH
	};

	i = 0;
	while (i < NB_IMAGES)
	{
		img_paths[i] = malloc(ft_strlen(paths[i]) + 1);
		if (!img_paths[i])
			return (ft_printf("Error\nCouldn't create img file\n"), RET_ERR);
		ft_strlcpy(img_paths[i], paths[i], ft_strlen(paths[i])+1);
		printf("img_paths before: %s\n", img_paths[i]);
		ret = new_img_from_file(img_paths[i], data, i);
		if (ret == RET_ERR)
			return (RET_ERR);
		i++;
	}
}

int	new_img_from_file(char *path, t_data *data, int i)
{
	data->img[i].img = mlx_xpm_file_to_image(data->mlx, path, &(data->img[i].width), &(data->img[i].height));
	if (!(data->img[i].img))
		return (ft_printf("Error\nImage file couldn't be open/read\n"), RET_ERR);
	data->img[i].addr = mlx_get_data_addr(data->img[i].img, &(data->img[i].bits_per_pixel), &(data->img[i].line_length), &(data->img[i].endian));
	if (!data->img[i].addr)
		return (ft_printf("Error\nCouldn't get data on img file\n"), RET_ERR);
	return (1);
}

int	set_img_position(t_data *data, int i, int x, int y)
{
		data->img[i].x = x;
		data->img[i].y = y;
}

int	render(t_data *data)
{
	if (data->mlx_win != NULL)
	{
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[PLAYER].img, data->img[PLAYER].x, data->img[PLAYER].y);
			return (0);
	}
	return (-1);
}