/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_manager_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:50:15 by alarose           #+#    #+#             */
/*   Updated: 2024/06/29 13:24:03 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_imgs_path(char **img_paths)
{
	int	i;

	i = 0;
	while (i < NB_IMAGES)
	{
		if (img_paths[i])
			free(img_paths[i]);
		i++;
	}
}

int	init_imgs(char **img_paths, t_data *data)
{
	int			i;
	int			ret;
	const char	*paths[NB_IMAGES] = {
		WALL_PATH,
		COLL_PATH,
		EXIT_PATH,
		PLAYER_PATH,
		BG_PATH,
		PLAYER_EXIT_PATH,
		WOLF_PATH,
	};

	i = 0;
	while (i < NB_IMAGES)
	{
		img_paths[i] = malloc(ft_strlen(paths[i]) + 1);
		if (!img_paths[i])
			return (free_imgs_path(img_paths), \
			ft_printf("Error\nCouldn't create img file\n"), RET_ERR);
		ft_strlcpy(img_paths[i], paths[i], ft_strlen(paths[i]) + 1);
		ret = new_img_from_file(img_paths[i], data, i) + add_map_code(data, i);
		if (ret != 2)
			return (free_imgs_path(img_paths), RET_ERR);
		i++;
	}
	return (free_imgs_path(img_paths), 1);
}

int	new_img_from_file(char *path, t_data *data, int i)
{
	data->img[i].img = mlx_xpm_file_to_image(data->mlx, path, \
	&(data->img[i].width), &(data->img[i].height));
	if (!(data->img[i].img))
		return (ft_printf("Error\nImage file couldn't be open/read\n"), RET_ERR);
	set_img_position(data, i, 0, 0);
	return (1);
}

int	add_map_code(t_data *data, int i)
{
	const char	map_code[NB_IMAGES] = {
		WALL_CODE,
		COLL_CODE,
		EXIT_CODE,
		PLAYER_CODE,
		BG_CODE,
		PLAYER_EXIT_CODE,
		WOLF_CODE,
	};

	data->img[i].map_code = map_code[i];
	if (!is_in_charset(data->img[i].map_code))
		return (ft_printf("Error\nCouldn't link map code to image\n"), RET_ERR);
	return (1);
}

void	set_img_position(t_data *data, int i, int x, int y)
{
		data->img[i].x = x;
		data->img[i].y = y;
}
