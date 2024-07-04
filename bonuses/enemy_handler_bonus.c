/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:54:22 by alarose           #+#    #+#             */
/*   Updated: 2024/07/04 12:11:51 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long_bonus.h>

static void	count_enemies(int y, int x, t_data *data, char **map)
{
	if (!position_is_valid(y, x, &map, data->map.height))
		return ;
	if (map[y][x] == '0' || map[y][x] == 'C' || map[y][x] == 'P')
	{
		data->map.free_space++;
		map[y][x] = 'V';
		count_enemies(y - 1, x, data, map);
		count_enemies(y + 1, x, data, map);
		count_enemies(y, x - 1, data, map);
		count_enemies(y, x + 1, data, map);
	}
}

int	define_enemies(t_data *data)
{
	char	**temp;

	temp = copy_map(data->map.map_layout, data->map.height);
	if (!temp)
		return (RET_ERR);
	data->map.free_space = 0;
	count_enemies(data->map.start_y, data->map.start_x, data, temp);
	free_map(temp);
	printf("COUNT: %d\n", data->map.free_space);
	data->map.nb_enemies = (data->map.free_space - \
	data->map.nb_collectibles - 2) / ENEMY_ZONE;
	temp = copy_map(data->map.map_layout, data->map.height);
	if (!temp)
		return (ft_printf(RED"Error\nCouldn't copy map\n" RESET), RET_ERR);
	data->enemies = malloc(sizeof(t_enemy) * data->map.nb_enemies);
	if (!data->enemies)
		return (ft_printf("Error\nCouldn't create enemies\n"), RET_ERR);
	put_enemies(data->map.start_y, data->map.start_x, data, temp);
	free_map(temp);
	return (1);
}

void	put_enemies(int y, int x, t_data *data, char **map)
{
	static int	count = 0;
	static int	i = 0;

	if (!position_is_valid(y, x, &map, data->map.height))
		return ;
	if (map[y][x] == '0' || map[y][x] == 'C' || map[y][x] == 'P')
	{
		map[y][x] = 'V';
		if (map[y][x] != 'E' || map[y][x] != 'C')
		{
			count++;
			if (count % ENEMY_ZONE == 0)
				set_enemy_position(data, x, y, i++);
		}
		put_enemies(y - 1, x, data, map);
		put_enemies(y + 1, x, data, map);
		put_enemies(y, x - 1, data, map);
		put_enemies(y, x + 1, data, map);
	}
}

void	set_enemy_position(t_data *data, int x, int y, int i)
{
	if (i == data->map.nb_enemies)
		return ;
	data->map.map_layout[y][x] = 'K';
	data->enemies[i].x = x;
	data->enemies[i].y = y;
}

int	move_enemies(t_data *data)
{
	int	i;
	int	rand_nb;

	i = 0;
	while (i < data->map.nb_enemies)
	{
		data->img[ENEMY].y = data->enemies[i].y;
		data->img[ENEMY].x = data->enemies[i].x;
		data->img[ENEMY].move_out_i_img = BG;
		rand_nb = 7 + rand() % 4;
		set_enemy_data(data, rand_nb, i);
		i++;
	}
	i = 0;
	return (0);
}
