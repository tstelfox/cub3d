/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 13:15:41 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/05 16:58:35 by tmullan       ########   odam.nl         */
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
	int i;

	i = data->spritenum;
	exit(0);
}
