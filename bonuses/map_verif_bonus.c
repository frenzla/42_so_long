/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:15:58 by alarose           #+#    #+#             */
/*   Updated: 2024/06/20 18:40:41 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	have_one_exit(char ***map)
{
	int	count_exit;
	int	i;
	int	k;

	if (!(*map))
		return (ft_printf(RED"Error\nUnknown map\n"RESET), RET_ERR);
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
		return (ft_printf(RED"Error\nWrong NB of Exit\n"RESET), RET_ERR);
	return (1);
}

int	have_collectibles(char ***map)
{
	int	count_coll;
	int	i;
	int	k;

	if (!(*map))
		return (ft_printf(RED"Error\nUnknown map\n"RESET), RET_ERR);
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
		return (ft_printf(RED"Error\nWrong NB of Collectibles\n"RESET), RET_ERR);
	return (1);
}

int	have_one_start(char ***map)
{
	int	count_start;
	int	i;
	int	k;

	if (!(*map))
		return (ft_printf(RED"Error\nUnknown map\n"RESET), RET_ERR);
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
		return (ft_printf(RED"Error\n\
Wrong NB of Starting point\n"RESET), RET_ERR);
	return (1);
}

int	is_rectangle(char ***map)
{
	int	i;

	if (!(*map))
		return (ft_printf(RED"Error\nUnknown map\n"RESET), RET_ERR);
	i = 0;
	while ((*map)[i])
	{
		if (i != 0)
			if (ft_strlen((*map)[i]) != ft_strlen((*map)[i - 1]))
				return (ft_printf(RED"Error\n\
Map is not a rectangle\n"RESET), RET_ERR);
		i++;
	}
	return (1);
}

int	map_path_valid(char *map_path)
{
	char	*temp;

	if (!map_path)
		return (ft_printf(RED"Error\nUnknown path\n"RESET), RET_ERR);
	temp = map_path + ft_strlen(map_path) - 4;
	if (ft_strncmp(temp, ".ber", 4) == 0)
		return (1);
	return (ft_printf(RED"Error\nInvalid file format\n"RESET), RET_ERR);
}
