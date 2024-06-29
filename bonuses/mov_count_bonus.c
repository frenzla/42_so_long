/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_count_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:22 by alarose           #+#    #+#             */
/*   Updated: 2024/06/29 14:44:39 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	display_banner(t_data *data, int nb_moves)
{
	char	*nb_moves_char;
	char	*str;

	mlx_set_font(data->mlx, data->mlx_win, FONT);
	nb_moves_char = ft_itoa(nb_moves);
	str = ft_strjoin("NB MOVES : ", nb_moves_char);
	free(nb_moves_char);
	if (!str)
		return (RET_ERR);
	if (!render_banner(data))
		return (RET_ERR);
	mlx_string_put(data->mlx, data->mlx_win, 20, \
	(data->map.height + 1) * TILE_SIZE - 12, FONT_COLOR, str);
	free(str);
	return (1);
}

int	render_banner(t_data *data)
{
	t_img	banner;

	if (!data->mlx_win)
		return (RET_ERR);
	banner.width = data->map.width * TILE_SIZE;
	banner.height = TILE_SIZE;
	banner.img = mlx_new_image(data->mlx, banner.width, banner.height);
	if (!banner.img)
		return (ft_printf("Error\nCouldn't load banner\n"), RET_ERR);
	banner.addr = mlx_get_data_addr(banner.img, &banner.bpp, \
	&banner.line_len, &banner.endian);
	render_bg(&banner, BANNER_COLOR);
	if (!add_logo(data, &banner) || !add_coll_tracker(data, &banner))
		return (RET_ERR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
	banner.img, 0, data->map.height * TILE_SIZE);
	mlx_destroy_image(data->mlx, banner.img);
	return (1);
}

int	add_logo(t_data *data, t_img *banner)
{
	t_img	text;

	if (data->map.width > 8)
	{
		text.img = mlx_xpm_file_to_image(data->mlx, \
		"./assets/so_long_img.xpm", &text.width, &text.height);
		if (!text.img)
			return (ft_printf("Error\nCouldn't load logo\n"), RET_ERR);
		text.addr = mlx_get_data_addr(text.img, &text.bpp, \
		&text.line_len, &text.endian);
		put_img_to_img(banner, &text, \
		(data->map.width * TILE_SIZE / 2) - (text.width / 2), 0);
		mlx_destroy_image(data->mlx, text.img);
	}
	return (1);
}
