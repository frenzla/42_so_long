/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:33:14 by alarose           #+#    #+#             */
/*   Updated: 2024/06/09 17:08:54 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

void	craft_pixel_in_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	t_data	data;
	char	*relative_path = "./assets/carrot.xpm";
	int		img_width;
	int		img_height;
	int		i;

	ft_printf("Hey! Libft is linked ;-)");

	//initialize connection for display
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_printf("Error\nConnection between program and display couldn't be established"), free(data.mlx), MLX_ERROR);

	//open new window
	data.mlx_win = mlx_new_window(data.mlx, 640, 480, "Hello world!");
	if (!data.mlx_win)
		return (ft_printf("Error\nNew window couldn't open"), free(data.mlx), MLX_ERROR);

//Manually crafting, designing & displaying an image
	//Create image
	data.img[0].img = mlx_new_image(data.mlx, 1920, 1080);
	if (!data.img[0].img)
		return (ft_printf("Error\nNew image couldn't be generated"), free(data.mlx), MLX_ERROR);
	data.img[0].addr = mlx_get_data_addr(data.img[0].img, &data.img[0].bits_per_pixel, &data.img[0].line_length, &data.img[0].endian);

	//Craft pixels in image
	i = 5;
	while (i < 105)
	{
		craft_pixel_in_img(&data.img[0], i, 5, 0x00FF0000);
		craft_pixel_in_img(&data.img[0], i, 105, 0x00FF0000);
		i++;
	}
	i = 5;
	while (i < 105)
	{

		craft_pixel_in_img(&data.img[0], 5, i, 0x00FF0000);
		craft_pixel_in_img(&data.img[0], 105, i, 0x00FF0000);
		i++;
	}
	//Show image
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img[0].img, 0, 0);

//from file: crafting & displaying image
	//Craft img from file
	data.img[1].img = mlx_xpm_file_to_image(data.mlx, relative_path, &img_width, &img_height);
	//Show image
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img[1].img, 0, 0);

	//Rendering
	mlx_loop(data.mlx);

	free(data.mlx);

	return (0);
}