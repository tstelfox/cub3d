/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 16:41:28 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/05 18:48:07 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void		flood_fill(t_data *data, int x, int y, char **floodmap)
// {
// 	if ()
// }

void		map_check(t_data *data)
{
	int 	i;
	int 	flag;
	// char	**floodmap;

	i = 0;
	flag = 0;
	while (data->maptemp[i])
	{
		if (ft_isalpha(data->maptemp[i]))
			flag = 1;
		i++;
		if (ft_isalpha(data->maptemp[i]) && flag == 1)
			bad_input(data, ERR_MAP);
	}
	if (flag == 0)
		bad_input(data, ERR_MAP);
	player(data);
	// flood_fill(data, data->player.posx, data->player.posy, floodmap);
}
