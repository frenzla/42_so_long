/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_count_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:22 by alarose           #+#    #+#             */
/*   Updated: 2024/06/28 11:30:21 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	display_nb_moves(t_data *data , int nb_moves)
{
	char	*nb_moves_char;
	char	*str;

	mlx_set_font(data->mlx, data->mlx_win, FONT);
	nb_moves_char = ft_itoa(nb_moves);
	str = ft_strjoin("NB MOVES : ", nb_moves_char);
	free(nb_moves_char);
	if (!str)
		return (RET_ERR);
	render_banner(data);
	mlx_string_put(data->mlx, data->mlx_win, 10, (data->map.height + 1) * TILE_SIZE - 12, FONT_COLOR, str);
	free(str);
	return (1);
}

int	render_banner(t_data *data)
{
	t_img	banner;

	if (!data->mlx_win)
		return (RET_ERR);
	banner.img = mlx_new_image(data->mlx, data->map.width * TILE_SIZE, TILE_SIZE);
	banner.addr = mlx_get_data_addr(banner.img, &banner.bpp, &banner.line_len, &banner.endian);
	render_bg(data, &banner, BANNER_COLOR);
	mlx_put_image_to_window(data->mlx, data->mlx_win, banner.img, 0, data->map.height * TILE_SIZE);
	mlx_destroy_image(data->mlx, banner.img);
	return (1);
}

void	render_bg(t_data *data, t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < data->map.width * TILE_SIZE)
		{
			img_pixel_put(img, j++, i, color);
		}
		++i;
	}
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}