/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:49:18 by alarose           #+#    #+#             */
/*   Updated: 2024/06/17 10:46:33 by alarose          ###   ########.fr       */
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
		NULL
	};
	int	ret;

// to change when other checks will be implemented
Test(map_checks, map_parsing)
{
	int i = 0;
	while (map_paths[i])
	{
		ret = get_map(map_paths[i], &map);
		if (i == 0)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, get_map should FAIL", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: empty file, get_map should FAIL", i);
		else
		{
			cr_expect_eq(ret, 1, "map[%d]: get_map should generate a map & return 1", i);
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
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on Exit check", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on Exit check", i);
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
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on Start check", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on Start check", i);
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
			cr_expect_eq(ret, 0, "map[%d]: empty_file, should FAIL on Start check", i);
		else if (i == 1)
			cr_expect_eq(ret, 0, "map[%d]: invalid_file_path, should FAIL on Start check", i);
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