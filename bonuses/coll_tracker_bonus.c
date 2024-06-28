/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coll_tracker_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:31:49 by alarose           #+#    #+#             */
/*   Updated: 2024/06/28 18:55:59 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int add_full_square(t_data *data, t_img *banner, int x, int y)
{
	int	i;
	int j;

	if (!data->mlx_win)
		return (RET_ERR);
	i = 0;
	while (i < SQUARE_LEN)
	{
		j = 0;
		while (j < SQUARE_LEN)
		{
			img_pixel_put(banner, x + i, y + j, FONT_COLOR);
			j++;
		}
		i++;
	}
	return (0);
}

int add_empty_square(t_data *data, t_img *banner, int x, int y)
{
	int	i;
	int j;

	if (!data->mlx_win)
		return (RET_ERR);
	i = 0;
	while (i < SQUARE_LEN)
	{
		j = 0;
		while (j < SQUARE_LEN)
		{
			if ((i < 2 || i > SQUARE_LEN - 3 || j < 2 || j > SQUARE_LEN - 3))
				img_pixel_put(banner, x + i, y + j, FONT_COLOR);
			j++;
		}
		i++;
	}
	return (0);
}

int	add_coll_tracker(t_data *data, t_img *banner)
{
	t_img		tracker;
	static int	len;
	static int	first_time = 0;
	static int	total_coll;
	int			x;
	int			y;


	if (!data->mlx_win)
		return (RET_ERR);
	if (first_time++ == 0)
	{
		len = SQUARE_LEN * data->map.nb_collectibles + (data->map.nb_collectibles - 1) * IN_BETWEEN + (TILE_SIZE / 2);
		total_coll = data->map.nb_collectibles;
	}
	printf("time coming in the function: %d | total_coll: %d | len: %d\n", first_time, total_coll, len);

	if (data-> map.width > (8 + len / TILE_SIZE))
	{
		tracker.img = mlx_new_image(data->mlx, len, SQUARE_LEN + 4);
		tracker.width = len;
		tracker.height = SQUARE_LEN + 4;
		if (!tracker.img)
			return (ft_printf("Couldn't load tracker\n"), RET_ERR);
		tracker.addr = mlx_get_data_addr(tracker.img, &tracker.bpp, &tracker.line_len, &tracker.endian);
		render_bg(&tracker, BANNER_COLOR);
		put_squares(data, total_coll, &tracker);
		x = data->map.width * TILE_SIZE - len;
		y = TILE_SIZE / 2 - tracker.height / 2;
		put_img_to_img(banner, &tracker, x, y);
	}
	return (1);
}

void	put_squares(t_data *data, int total_coll, t_img *tracker)
{
	int x;
	int	diff_coll;
	int	i;

	x = 6;
	diff_coll = total_coll - data->map.nb_collectibles;

	i = 0;
	while (i++ < diff_coll)
	{
		add_full_square(data, tracker, x, 2);
		x += SQUARE_LEN + IN_BETWEEN;
	}
	while (i++ < total_coll)
	{
		add_empty_square(data, tracker, x, 2);
		x += SQUARE_LEN + IN_BETWEEN;
	}
}