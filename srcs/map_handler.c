/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:52:20 by alarose           #+#    #+#             */
/*   Updated: 2024/06/26 15:09:48 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	get_map_info(t_data *data)
{
	int		nb_collectibles;
	int		i;
	int		k;

	i = -1;
	data->map.nb_collectibles = 0;
	data->map.width = ft_strlen(data->map.map_layout[i + 1]);
	while (data->map.map_layout[++i])
	{
		k = 0;
		while (data->map.map_layout[i][k])
		{
			if (data->map.map_layout[i][k] == 'P')
			{
				data->map.start_x = k;
				data->map.start_y = i;
			}
			if (data->map.map_layout[i][k++] == 'C')
				data->map.nb_collectibles++;
		}
	}
	if (!data->map.width || !data->map.start_x || !data->map.start_y || \
		!data->map.nb_collectibles)
		return (RET_ERR);
	return (1);
}

char **copy_map(char **map, int height)
{
	int	i;
	char **new_map;

	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (RET_ERR);
	i = 0;
	while (map[i])
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
		{
			while (--i >= 0)
				free(new_map[i]);
			free(new_map);
			return (RET_ERR);
		}
		i++;
	}
	new_map[i] = 0;
	return (new_map);
}

void free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

void	render_map(t_data *data)
{
	int		i;
	int		k;
	int		i_img;

	i = 0;
	while (data->map.map_layout[i])
	{
		k = 0;
		while (data->map.map_layout[i][k])
		{
			i_img = 0;
			while (i_img < NB_IMAGES)
			{
				if (data->map.map_layout[i][k] == data->img[i_img].map_code)
				{
					set_img_position(data, i_img, k, i);
					mlx_put_image_to_window(data->mlx, data->mlx_win, data->img[i_img].img, data->img[i_img].x * TILE_SIZE, data->img[i_img].y * TILE_SIZE);
				}
				i_img++;
			}
			k++;
		}
		i++;
	}
}
