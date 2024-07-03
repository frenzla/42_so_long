/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:05:04 by alarose           #+#    #+#             */
/*   Updated: 2024/07/03 16:59:30 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_imgs_path(char **img_paths)
{
	int	i;

	i = 0;
	while (i < NB_IMAGES)
	{
		if (img_paths[i])
			free(img_paths[i]);
		i++;
	}
}
