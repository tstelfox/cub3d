/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validator.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 18:52:01 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/25 19:12:59 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		validator(t_data *data, int argc, char *argv[])
{
	if (argc == 1)
	{
		printf("Didn't attach a map file, bleedin eejit\n");
		quit(data);
	}
	if (argc == 3)
	{
		if (!ft_strcmp(argv[2], "--save"))
			data->save = 1;
		else
		{
			printf("Misspelling\n");
			quit(data);
		}
	}
}
