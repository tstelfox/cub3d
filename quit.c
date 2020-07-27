/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 13:15:41 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/27 18:13:35 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bad_input(t_data *data, int type)
{
	if (type == 1)
		write(2, "Error\nResolution can't be negative\n", 36);
	if (type == 2)
		write(2, "Error\nDidn't attach a map file, bleedin eejit\n", 47);
	if (type == 3)
		write(2, "Error\nToo many arguments, like yer mum\n", 40);
	
	quit(data);
}

int		quit(t_data *data)
{
	// free(data->maparr);
	exit(0);
}
