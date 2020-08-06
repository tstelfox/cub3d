/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validator.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 18:52:01 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/06 13:37:35 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		validator(t_data *data, int argc, char *argv[])
{
	int		fd;

	if (argc == 1)
		bad_input(data, "Error\nDidn't attach a map file, bleedin eejit\n");
	if (argc == 2)
	{
		if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub"))
			bad_input(data, "Error\nConfiguration file must be .cub\n");
	}
	if (argc == 3)
	{
		if (!ft_strcmp(argv[2], "--save"))
			data->save = 1;
		else
			bad_input(data, "Error\nToo many arguments, like yer mum\n");
	}
	fd = open(argv[1], O_RDONLY);
	prs_wrld(data, fd);
	close(fd);
}
