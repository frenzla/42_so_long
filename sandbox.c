/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:33:14 by alarose           #+#    #+#             */
/*   Updated: 2024/06/12 17:20:53 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	craft_pixel_in_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*int	main(void)
{
	t_data	data;

	ft_printf("Hey! Libft is linked ;-)");

	init_img_paths(img_paths);

	//initialize connection for display
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_printf("Error\nConnection between program and display couldn't be established"), free(data.mlx), RET_ERR);

	//open new window
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_LENGTH, "Hello world!");
	if (!data.mlx_win)
		return (ft_printf("Error\nNew window couldn't open"), free(data.mlx), RET_ERR);

//SQUARE: Manually crafting, designing & displaying an image
	//Create image
	data.img[SQUARE].img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_LENGTH);
	if (!data.img[SQUARE].img)
		return (ft_printf("Error\nNew image couldn't be generated"), free(data.mlx), RET_ERR);
	data.img[SQUARE].addr = mlx_get_data_addr(data.img[SQUARE].img, &data.img[SQUARE].bits_per_pixel, &data.img[SQUARE].line_length, &data.img[SQUARE].endian);

	//Craft pixels in image
	i = 5;
	while (i < 105)
	{
		craft_pixel_in_img(&data.img[SQUARE], i, 5, 0x00FF0000);
		craft_pixel_in_img(&data.img[SQUARE], i, 105, 0x00FF0000);
		i++;
	}
	i = 5;
	while (i < 105)
	{

		craft_pixel_in_img(&data.img[SQUARE], 5, i, 0x00FF0000);
		craft_pixel_in_img(&data.img[SQUARE], 105, i, 0x00FF0000);
		i++;
	}
	//Show image
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img[SQUARE].img, 0, 0);

	//Rendering
	mlx_loop(data.mlx);

	mlx_destroy_display(data.mlx);
	free(data.mlx);

	return (0);
}*/