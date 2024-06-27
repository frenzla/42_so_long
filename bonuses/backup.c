int	handle_input(int keysym, t_data *data)
{
	static int					nb_moves = 0;
	int							i;
	const t_keycode_f_mapping	f_table[] = {
	{XK_d, go_right},
	{XK_a, go_left},
	{XK_w, go_up},
	{XK_s, go_down},
	{XK_Escape, close_game}
	};
	int							ret;

	if (data->map.map_layout[data->img[PLAYER].y][data->img[PLAYER].x] == 'P')
		data->map.move_out_i_img = BG;
	i = 0;
	while ((long unsigned)i < (sizeof(f_table) / sizeof(f_table[0])))
	{
		if (f_table[i].keycode == keysym)
		{
			ret = f_table[i].func(data, PLAYER);
			if (ret)
				return(display_nb_moves(data, nb_moves += ret), 1);
		}
		i++;
	}
	return (RET_ERR);
}


/*
	t_img	banner;
	banner.img = mlx_new_image(data.mlx, data.map.width * TILE_SIZE, data.map.height * TILE_SIZE);
	banner.addr = mlx_get_data_addr(banner.img, &banner.bits_per_pixel, &banner.line_length, &banner.endian);
	my_mlx_pixel_put(&banner, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(data.mlx, data.mlx_win, banner.img, data.map.width * TILE_SIZE, data.map.height * TILE_SIZE);
*/


void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	display_nb_moves(t_data *data , int nb_moves)
{
	char	*str;


	mlx_set_font(data->mlx, data->mlx_win, "-schumacher-clean-bold-r-normal--15-150-75-75-c-90-iso646.1991-irv");
	str = ft_strjoin("NB MOVES : ", ft_itoa(nb_moves));
	if (!str)
		return (RET_ERR);
	mlx_string_put(data->mlx, data->mlx_win, 10, (data->map.height + 1) * TILE_SIZE - 12, 0xcccccc, str);
	free(str);
	return (1);
}