/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 13:15:41 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/07 15:03:24 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bad_input(char *error)
{
	write(2, error, ft_strlen(error));
	quit();
}

int		quit(void)
{
	exit(0);
}
