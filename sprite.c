/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 18:13:18 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/15 18:33:11 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		count_sprites(t_data *data)
{
	int i;
	int thijs;

	thijs = 0;
	i = 0;
	while (data->maptemp[i])
	{
		if (data->maptemp[i] == '2')
			thijs++;
		i++;
	}
	data->spritenum = thijs;
}
