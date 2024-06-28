/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:12:36 by alarose           #+#    #+#             */
/*   Updated: 2024/06/28 15:02:28 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(int *)((img->addr + (y * img->line_len) + (x * img->bpp / 8))));
}

void	put_img_to_img(t_img *dst, t_img *src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while(i < src->width) {
		j = 0;
		while (j < src->height) {
			img_pixel_put(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}

//preserving transparency
void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (color == (int)0xFF000000)
		return ;
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
