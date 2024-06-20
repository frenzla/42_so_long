/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:49:18 by alarose           #+#    #+#             */
/*   Updated: 2024/06/14 19:09:31 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include </home/alarose/Criterion/include/criterion/criterion.h>

	char	**map = NULL;
	char	*map_paths[] = {
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map9.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map15.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map0.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map1.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map2.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map3.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map4.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map5.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map6.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map7.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map8.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map10.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map11.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map12.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map13.ber",
		"/home/alarose/projects/so_long/tests/map_tests/maps_for_tests/map14.ber",
		NULL
	};
	int	ret;

Test(mapcreation, map_empty)
{
	ret = get_map(map_paths[0], &map);
		cr_assert_eq(ret, 0, "get_map should return 0");
}

Test(mapcreation, map_invalid_path)
{
	ret = get_map(map_paths[1], &map);
		cr_assert_eq(ret, 0, "get_map should return 0");
}
//to change when checks will be implemented
Test(mapcreation, creation)
{
	int	i = 2;
	int k = 0;
	while (map_paths[i])
	{
		ret = get_map(map_paths[i], &map);
		cr_assert_eq(ret, 1, "get_map should return 1");
		map = NULL;
		i++;
	}
}

Test(mapverif, one_exit)
{
	int i = 0;
	get_map(map_paths[i], &map);
	ret = have_one_exit(&map);
		cr_assert_eq(ret, 0, "empty file should FAIL on Exit check");

	i = 1;
	get_map(map_paths[i], &map);
	ret = have_one_exit(&map);
		cr_assert_eq(ret, 0, "invalid_file_path should FAIL on Exit check");

	i = 2;
	get_map(map_paths[i], &map);
	ret = have_one_exit(&map);
		cr_assert_eq(ret, 1, "perfect map - should PASS");

	i = 3;
	get_map(map_paths[i], &map);
	ret = have_one_exit(&map);
		cr_assert_eq(ret, 0, "no exit on map - should FAIL");
}