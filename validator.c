/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validator.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 18:52:01 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/27 18:03:25 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		validator(t_data *data, int argc, char *argv[])
{
	if (argc == 1)
		bad_input(data, 2);
	if (argc == 3)
	{
		if (!ft_strcmp(argv[2], "--save"))
			data->save = 1;
		else
			bad_input(data, 3);
	}
}
