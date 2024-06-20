/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:15:58 by alarose           #+#    #+#             */
/*   Updated: 2024/06/17 10:40:05 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_path_valid(char *map_path)
{
	//check if "*.ber"
}

int	have_one_exit(char ***map)
{
	int	count_exit;
	int	i;
	int	k;

	if (!(*map))
		return (RET_ERR);
	count_exit = 0;
	i = 0;
	while ((*map)[i])
	{
		k = 0;
		while ((*map)[i][k])
		{
			if ((*map)[i][k] == 'E')
				count_exit++;
			k++;
		}
		i++;
	}
	if (count_exit != 1)
		return (RET_ERR);
	return (1);
}

int	have_collectibles(char ***map)
{
	int	count_coll;
	int	i;
	int	k;

	if (!(*map))
		return (RET_ERR);
	count_coll = 0;
	i = 0;
	while ((*map)[i])
	{
		k = 0;
		while ((*map)[i][k])
		{
			if ((*map)[i][k] == 'C')
				count_coll++;
			k++;
		}
		i++;
	}
	if (count_coll < 1)
		return (RET_ERR);
	return (1);
}

int	have_one_start(char ***map)
{
	int	count_start;
	int	i;
	int	k;

	if (!(*map))
		return (RET_ERR);
	count_start = 0;
	i = 0;
	while ((*map)[i])
	{
		k = 0;
		while ((*map)[i][k])
		{
			if ((*map)[i][k] == 'P')
				count_start++;
			k++;
		}
		i++;
	}
	if (count_start != 1)
		return (RET_ERR);
	return (1);
}
