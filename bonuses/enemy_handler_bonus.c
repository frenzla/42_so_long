/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:54:22 by alarose           #+#    #+#             */
/*   Updated: 2024/06/29 17:35:25 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long_bonus.h>
/*
int	count_free_space(t_data * data)
{
	int zero_count;
	int i;
	int j;

	zero_count = 0;
	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.map_layout[i][j] == '0')
				zero_count++;
			j++;
		}
		i++;
	}
	return (zero_count);
}
*/
int	define_enemies(t_data *data)
{
	char	**temp;

	data->map.nb_enemies = (data->map.free_space - data->map.nb_collectibles - 2 ) / ENEMY_ZONE;
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

int	put_enemies(int y, int x, t_data *data, char **map)
{
	static int	got_exit = 0;
	static int	collec = 0;
	static int	count = 0;
	static int	i = 0;

	if (!position_is_valid(y, x, &map, data->map.height))
		return (RET_ERR);
	if (map[y][x] == 'E')
		got_exit = 1;
	if (map[y][x] == 'C')
		collec++;
	if (got_exit && collec == data->map.nb_collectibles)
		return (got_exit = 0, collec = 0, 1);
	if (map[y][x] != 'E' && map[y][x] != 'C')
		count++;
	map[y][x] = 'X';
	if(count % ENEMY_ZONE == 0)
		set_enemy_position(data, x, y, i++);
	if (put_enemies(y, x + 1, data, map) || put_enemies(y, x - 1, data, map) || \
		put_enemies(y + 1, x, data, map) || put_enemies(y - 1, x, data, map))
		return (1);
	return (RET_ERR);
}

void	set_enemy_position(t_data *data, int x, int y, int i)
{
		data->map.map_layout[y][x] = 'K';
		data->enemies[i].x = x;
		data->enemies[i].y = y;
}

void	set_new_position(t_data *data, int x, int y, int i)
{
		data->map.map_layout[data->enemies[i].y][data->enemies[i].x] = '0';
		data->map.map_layout[y][x] = 'K';
		data->enemies[i].x = x;
		data->enemies[i].y = y;
}
/*
int	main(int argc, char **argv)
{
	t_data	data;
	int		i; // delete
	char	*img_paths[NB_IMAGES];

	if (argc != 2)
		return (ft_printf(RED "Error\nIncorrect input" RESET), 1);
	if (!get_map(argv[1], &data))
		return (1);
	define_enemies(&data);

	i = 0; // delete
	while (i < data.map.height) // delete
		printf("%s\n", data.map.map_layout[i++]); // delete

	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_printf("Error\nMinilibX error"), 1);
	data.mlx_win = mlx_new_window(data.mlx, data.map.width * TILE_SIZE, \
	(data.map.height + 1) * TILE_SIZE, "Hello world!");
	if (!data.mlx_win)
		return (ft_printf("Error\nNew window couldn't open"), free(data.mlx), 1);
	if (!init_imgs(img_paths, &data))
		return (close_game(&data, 0), 1);
	data.game_over = 0;
	render_map(&data);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, \
	close_game, &data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, handle_input, &data);
	mlx_loop(data.mlx);
	return (0);
}*/