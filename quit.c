/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 13:15:41 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/29 10:47:05 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bad_input(t_data *data, char *error)
{
	write(2, error, ft_strlen(error));
	quit(data);
}

int		quit(t_data *data)
{
	// free(data->maparr);
	exit(0);
}
