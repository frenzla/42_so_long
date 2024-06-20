/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:49:18 by alarose           #+#    #+#             */
/*   Updated: 2024/06/20 11:22:48 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include </home/alarose/Criterion/include/criterion/criterion.h>

	t_data	data;

	char	**map = NULL;
	char	*map_paths[] = {
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/mapXX.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map1.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map2.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map3.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map4.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map5.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map6.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map7.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map8.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map9.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map10.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map11.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map12.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map13.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map14.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map15.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map16.pue",
		NULL
	};
	int	ret;

	int	get_nb_lines_TEST(char *map_path)
	{
		int		fd;
		char	*line;
		int		nb_lines;
		int		ret;

		fd = open(map_path, O_RDONLY);
		if (fd < 1)
			return (0);
		line = get_next_line(fd);
		if (!line)
			return (close(fd), 0);
		else
			nb_lines = 0;
		while (line)
		{
			nb_lines++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		return (nb_lines);
	}

Test(map_checks, map_validity)
{
	int i = 0;
	while (map_paths[i])
	{
		ret = get_map(map_paths[i], &data);
		if (i == 0)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, get_map should FAIL", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: empty file, get_map should FAIL", i);
		else if (i == 2)
		{
			cr_expect_eq(ret, 1, "map[%d]: get_map should generate a map & return 1", i);
			free_map(&(data.map.map_layout));
		}
//THIS TEST SHOULD RETURN 0 ONCE FLOOD FILL IS DONE!
		else if (i == 11)
		{
			cr_expect_eq(ret, 1, "map[%d]: get_map should generate a map & return 1", i);
			free_map(&(data.map.map_layout));
		}
		else if (i == 12)
		{
			cr_expect_eq(ret, 1, "map[%d]: get_map should generate a map & return 1", i);
			free_map(&(data.map.map_layout));
		}
		else
		{
			cr_expect_eq(ret, 0, "map[%d]: get_map should FAIL because of checks", i);
			free_map(&(data.map.map_layout));
		}
		i++;
	}
}
//Checks that map contains 1 EXIT
Test(map_checks, exit_check)
{
	int i = 0;
	while (map_paths[i])
	{
		get_map(map_paths[i], &data);
		ret = have_one_exit(&(data.map.map_layout));
		if (i == 0)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on Exit check", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on Exit check", i);
		else if (i == 2)
		{
			cr_expect_eq(ret, 1, "map[%d]: perfect map - should PASS", i);
			free_map(&(data.map.map_layout));
		}
		else if (i == 3)
		{
			cr_expect_eq(ret, 0, "map[%d]: no exit on map - should FAIL", i);
			free_map(&(data.map.map_layout));
		}
		else if (i == 7)
		{
			cr_expect_eq(ret, 0, "map[%d]: 2 exits, should FAIL", i);
			free_map(&(data.map.map_layout));
		}
		else
		{
			cr_expect_eq(ret, 1, "map[%d]: map has only 1 exit, should PASS", i);
			free_map(&(data.map.map_layout));
		}
		i++;
	}
}

//Checks that map contains 1 STARTING position
Test(map_checks, start_check)
{
	int i = 0;
	while (map_paths[i])
	{
		get_map(map_paths[i], &data);
		ret = have_one_start(&(data.map.map_layout));
		if (i == 0)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on Start check", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on Start check", i);
		else if (i == 2)
		{
			cr_expect_eq(ret, 1, "map[%d]: perfect map - should PASS", i);
			free_map(&(data.map.map_layout));
		}
		else if (i == 5)
		{
			cr_expect_eq(ret, 0, "map[%d]: no starting point on map - should FAIL", i);
			free_map(&(data.map.map_layout));
		}
		else if (i == 6)
		{
			cr_expect_eq(ret, 0, "map[%d]: 2 starting points, should FAIL", i);
			free_map(&(data.map.map_layout));
		}
		else
		{
			cr_expect_eq(ret, 1, "map[%d]: map has only 1 starting point, should PASS", i);
			free_map(&(data.map.map_layout));
		}
		i++;
	}
}

//Checks that map contains at least 1 collectible
Test(map_checks, collectibles_check)
{
	int i = 0;
	while (map_paths[i])
	{
		get_map(map_paths[i], &data);
		ret = have_collectibles(&(data.map.map_layout));
		if (i == 0)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on Collectibles check", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on Collectibles check", i);
		else if (i == 2)
		{
			cr_expect_eq(ret, 1, "map[%d]: perfect map - should PASS", i);
			free_map(&(data.map.map_layout));
		}
		else if (i == 4)
		{
			cr_expect_eq(ret, 0, "map[%d]: no collectibles on map - should FAIL", i);
			free_map(&(data.map.map_layout));
		}
		else
		{
			cr_expect_eq(ret, 1, "map[%d]: map has more than 1 collectible, should PASS", i);
			free_map(&(data.map.map_layout));
		}
		i++;
	}
}

//Checks that map is a rectangle/square
Test(map_checks, is_rectangular)
{
	int i = 0;
	while (map_paths[i])
	{
		get_map(map_paths[i], &data);
		ret = is_rectangle(&(data.map.map_layout));
		if (i == 0)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on Rectangle check", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on Rectangle check", i);
		else if (i == 8)
		{
			cr_expect_eq(ret, 0, "map[%d]: no rectangular map - should FAIL", i);
			free_map(&(data.map.map_layout));
		}
		else
		{
			cr_expect_eq(ret, 1, "map[%d]: map is a rectangle, should PASS", i);
			free_map(&(data.map.map_layout));
		}
		i++;
	}
}

//Checks that every char in map is correct
Test(map_checks, checks_on_map_chars)
{
	int i = 0;
	while (map_paths[i])
	{
		get_map(map_paths[i], &data);
		ret = check_chars(&(data.map.map_layout));
		if (i == 0)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on check_chars", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on check_chars", i);
		else if (i == 8 || i == 9 || i == 10)
		{
			cr_expect_eq(ret, 0, "map[%d]: not spaces allowed before map - should FAIL", i);
			free_map(&(data.map.map_layout));
		}
		else if (i == 13 || i == 14)
		{
			cr_expect_eq(ret, 0, "map[%d]: unrecognised char in map - should FAIL", i);
			free_map(&(data.map.map_layout));
		}
		else
		{
			cr_expect_eq(ret, 1, "map[%d]: all char of the map are in charset, should PASS", i);
			free_map(&(data.map.map_layout));
		}
		i++;
	}
}

//Checks that map path end with ".ber"
Test(map_checks, check_map_path)
{
	int i = 0;
	while (map_paths[i])
	{
		ret = map_path_valid(map_paths[i]);
		if (i == 16)
			cr_expect_eq(ret, 0, "map[%d]: map path doesn't end with .ber, should FAIL", i);
		else
			cr_expect_eq(ret, 1, "map[%d]: map path ends with .ber, should PASS", i);
		i++;
	}
}

//Checks if map is closed by walls (1)
Test(map_checks, checks_walls)
{
	int i = 0;
	int	nb_lines;

	while (map_paths[i])
	{
	get_map(map_paths[i], &data);
	nb_lines = get_nb_lines_TEST(map_paths[i]); // ===>>> Function in test file (here above)
	ret = check_external_walls(&(data.map.map_layout), nb_lines);
		if (i == 0)
		{
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on check_walls", i);
		}
		else if (i == 1)
		{
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on check_walls", i);
		}
		else if (i == 8)
		{
			cr_expect_eq(ret, 0, "map[%d]: map not rectangular, should FAIL", i);
			free_map(&(data.map.map_layout));
		}
		else if (i == 9 || i == 10)
		{
			cr_expect_eq(ret, 0, "map[%d]: unreconised chars before map, should FAIL", i);
			free_map(&(data.map.map_layout));
		}
		else if (i == 15)
		{
			cr_expect_eq(ret, 0, "map[%d]: not closed by wall, should FAIL", i);
			free_map(&(data.map.map_layout));
		}
		else
		{
			cr_expect_eq(ret, 1, "map[%d]: valide map, it should PASS", i);
			free_map(&(data.map.map_layout));
		}
		i++;
	}
}

Test(map_checks, valid_position_for_flood_fill)
{
	long unsigned int i = 0;
	int	nb_lines;

	int	pos[10][2] = {
		{0, 0},
		{0, 1},
		{1, 1},
		{1, 33},
		{1, 34},
		{1, 35},
		{1, 36},
		{2, 20},
		{2, 22},
		{8, 1},
	};

	get_map(map_paths[2], &data);
	nb_lines = get_nb_lines_TEST(map_paths[2]); // ===>>> Function in test file (here above)
	while (i < sizeof(pos)/sizeof(pos[0]))
	{
		ret = position_is_valid(pos[i][0], pos[i][1], &(data.map.map_layout), nb_lines);
		if (i == 0 || i == 1 || i == 5 || i == 6 || i == 7)
			cr_expect_eq(ret, 0, "Position [%d, %d] (char: %c) shouldn't be valid", pos[i][0], pos[i][1], (data.map.map_layout)[pos[i][0]][pos[i][1]]);
		else if (i == 2 || i == 3 || i == 4 || i == 8 || i == 9)
			cr_expect_eq(ret, 1, "Position [%d, %d] (char: %c) should be valid", pos[i][0], pos[i][1], (data.map.map_layout)[pos[i][0]][pos[i][1]]);
		i++;
	}
}

Test(map_checks, flood_fill)
{
	int	z = 0;
	int i;
	int k;
	int	nb_lines;
	int	nb_collectibles;
	int	start_x;
	int	start_y;

	while (map_paths[z])
	{
		ret = get_map(map_paths[z], &data);
		nb_lines = get_nb_lines_TEST(map_paths[z]);
		//get stating position coordinates & nb_collectibles
		i = 0;
		nb_collectibles = 0;
		if (ret != 0)
		{
			while ((data.map.map_layout)[i])
			{
				k = 0;
				while ((data.map.map_layout)[i][k])
				{
					if ((data.map.map_layout)[i][k] == 'P')
					{
						start_x = k;
						start_y = i;
					}
					if ((data.map.map_layout)[i][k] == 'C')
						nb_collectibles++;
					k++;
				}
				i++;
			}
		ret = there_is_a_valid_path(start_y, start_x, data.map.map_layout, nb_lines, &nb_collectibles);
		}
		if (z == 2 || z == 12)
		{
			cr_expect_eq(ret, 1, "map[%d]: perfect map, should PASS", z);
			free_map(&(data.map.map_layout));
		}
		else if (z == 0 || z == 1)
			cr_expect_eq(ret, 0, "map[%d]: invalid map or empty_file, should FAIL", z);
		else
		{
			cr_expect_eq(ret, 0, "map[%d]: invalid format after checks: map should FAIL", z);
			free_map(&(data.map.map_layout));
		}
		z++;
	}
}

Test(map_checks, get_map_info_check)
{
	int	z = 2;
	int	fd = 0;
	int	nb_lines;

	while (map_paths[z])
	{
		data.map.map_path = map_paths[z];
		data.map.height = get_nb_lines(map_paths[z]);

		fd = open(map_paths[z], O_RDONLY);
		ret = parse_map(fd, &data);
		close(fd);

		ret = get_map_info(&data);

		if (z == 4)
			cr_expect_eq(ret, 0, "map[%d]: map with no collectibles, should FAIL", z);
		else
			cr_expect_eq(ret, 1, "map[%d]: good map, should PASS", z);

		free_map(&(data.map.map_layout));
		z++;
	}
}
