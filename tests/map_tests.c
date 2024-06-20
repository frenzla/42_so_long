/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:49:18 by alarose           #+#    #+#             */
/*   Updated: 2024/06/17 18:58:04 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include </home/alarose/Criterion/include/criterion/criterion.h>

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


	int	get_nb_lines(char *map_path)
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
			nb_lines = 1;
		while (line)
		{
			nb_lines++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		return (nb_lines);
	}

// to change when other checks will be implemented
Test(map_checks, map_validity)
{
	int i = 0;
	while (map_paths[i])
	{
		ret = get_map(map_paths[i], &map);
		if (i == 0)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, get_map should FAIL", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: empty file, get_map should FAIL", i);
		else if (i == 2)
		{
			cr_expect_eq(ret, 1, "map[%d]: get_map should generate a map & return 1", i);
			free_map(&map);
		}
//THIS TEST SHOULD RETURN 0 ONCE FLOOD FILL IS DONE!
		else if (i == 11)
		{
			cr_expect_eq(ret, 1, "map[%d]: get_map should generate a map & return 1", i);
			free_map(&map);
		}
		else if (i == 12)
		{
			cr_expect_eq(ret, 1, "map[%d]: get_map should generate a map & return 1", i);
			free_map(&map);
		}
		else
		{
			cr_expect_eq(ret, 0, "map[%d]: get_map should FAIL because of checks", i);
			free_map(&map);
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
		get_map(map_paths[i], &map);
		ret = have_one_exit(&map);
		if (i == 0)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on Exit check", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on Exit check", i);
		else if (i == 2)
		{
			cr_expect_eq(ret, 1, "map[%d]: perfect map - should PASS", i);
			free_map(&map);
		}
		else if (i == 3)
		{
			cr_expect_eq(ret, 0, "map[%d]: no exit on map - should FAIL", i);
			free_map(&map);
		}
		else if (i == 7)
		{
			cr_expect_eq(ret, 0, "map[%d]: 2 exits, should FAIL", i);
			free_map(&map);
		}
		else
		{
			cr_expect_eq(ret, 1, "map[%d]: map has only 1 exit, should PASS", i);
			free_map(&map);
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
		get_map(map_paths[i], &map);
		ret = have_one_start(&map);
		if (i == 0)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on Start check", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on Start check", i);
		else if (i == 2)
		{
			cr_expect_eq(ret, 1, "map[%d]: perfect map - should PASS", i);
			free_map(&map);
		}
		else if (i == 5)
		{
			cr_expect_eq(ret, 0, "map[%d]: no starting point on map - should FAIL", i);
			free_map(&map);
		}
		else if (i == 6)
		{
			cr_expect_eq(ret, 0, "map[%d]: 2 starting points, should FAIL", i);
			free_map(&map);
		}
		else
		{
			cr_expect_eq(ret, 1, "map[%d]: map has only 1 starting point, should PASS", i);
			free_map(&map);
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
		get_map(map_paths[i], &map);
		ret = have_collectibles(&map);
		if (i == 0)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on Collectibles check", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on Collectibles check", i);
		else if (i == 2)
		{
			cr_expect_eq(ret, 1, "map[%d]: perfect map - should PASS", i);
			free_map(&map);
		}
		else if (i == 4)
		{
			cr_expect_eq(ret, 0, "map[%d]: no collectibles on map - should FAIL", i);
			free_map(&map);
		}
		else
		{
			cr_expect_eq(ret, 1, "map[%d]: map has more than 1 collectible, should PASS", i);
			free_map(&map);
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
		get_map(map_paths[i], &map);
		ret = is_rectangle(&map);
		if (i == 0)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on Rectangle check", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on Rectangle check", i);
		else if (i == 8)
		{
			cr_expect_eq(ret, 0, "map[%d]: no rectangular map - should FAIL", i);
			free_map(&map);
		}
		else
		{
			cr_expect_eq(ret, 1, "map[%d]: map is a rectangle, should PASS", i);
			free_map(&map);
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
		get_map(map_paths[i], &map);
		ret = check_chars(&map);
		if (i == 0)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on check_chars", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on check_chars", i);
		else if (i == 8 || i == 9 || i == 10)
		{
			cr_expect_eq(ret, 0, "map[%d]: not spaces allowed before map - should FAIL", i);
			free_map(&map);
		}
		else if (i == 13 || i == 14)
		{
			cr_expect_eq(ret, 0, "map[%d]: unrecognised char in map - should FAIL", i);
			free_map(&map);
		}
		else
		{
			cr_expect_eq(ret, 1, "map[%d]: all char of the map are in charset, should PASS", i);
			free_map(&map);
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
	get_map(map_paths[i], &map);
	nb_lines = get_nb_lines(map_paths[i]);
	ret = check_external_walls(&map, nb_lines);
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
			free_map(&map);
		}
		else if (i == 9 || i == 10)
		{
			cr_expect_eq(ret, 0, "map[%d]: unreconised chars before map, should FAIL", i);
			free_map(&map);
		}
		else if (i == 15)
		{
			cr_expect_eq(ret, 0, "map[%d]: not closed by wall, should FAIL", i);
			free_map(&map);
		}
		else
		{
			cr_expect_eq(ret, 1, "map[%d]: valide map, it should PASS", i);
			free_map(&map);
		}
		i++;
	}
}
