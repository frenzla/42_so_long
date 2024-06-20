/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:50:15 by alarose           #+#    #+#             */
/*   Updated: 2024/06/11 17:51:16 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_img_paths(char **img_paths)
{
	int	i;
	char *paths[NB_IMAGES] = {
		SQUARE_PATH,
		CARROT_PATH
	};

	i = 0;
	while (i < NB_IMAGES)
	{
		img_paths[i] = malloc(ft_strlen(paths[i]) + 1);
		if (img_paths[i] != NULL)
			ft_strlcpy(img_paths[i], paths[i], ft_strlen(paths[i])+1);
		i++;
	}
}

int	new_img_from_file(char **paths, t_data *data, int i)
{
	data->img[i].img = mlx_xpm_file_to_image(data->mlx, paths[i], &(data->img[i].width), &(data->img[i].height));
	if (!(data->img[i].img))
		return (MLX_ERROR);
	data->img[i].addr = mlx_get_data_addr(data->img[i].img, &(data->img[i].bits_per_pixel), &(data->img[i].line_length), &(data->img[i].endian));
	//Define position of image
/*	data->img[i].x = 300;
	data->img[i].y = 300;*/
}

int	main(void)
{
	t_data	data;
	char	*img_paths[NB_IMAGES];

	//initialize connection for display
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_printf("Error\nConnection between program and display couldn't be established"), free(data.mlx), MLX_ERROR);

	//open new window
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_LENGTH, "Hello world!");
	if (!data.mlx_win)
		return (ft_printf("Error\nNew window couldn't open"), free(data.mlx), MLX_ERROR);

	init_img_paths(img_paths);

	if (new_img_from_file(img_paths, &data, CARROT) == -1)
		return (ft_printf("Error\nFile could not be read"), free(data.mlx), MLX_ERROR); // add free & destro windows

	printf("%d\n", data.img[1].height);

	mlx_loop_hook(data.mlx, render, &data);

	//Register key
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, handle_input, &data);
	//mlx_key_hook(data.mlx_win, &handle_input, &data);

	//Rendering
	mlx_loop(data.mlx);

	mlx_destroy_display(data.mlx);
	free(data.mlx);

	return (0);
}
