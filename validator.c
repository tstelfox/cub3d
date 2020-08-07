/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validator.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 18:52:01 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/07 16:33:19 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		validator(t_data *data, int argc, char *argv[])
{
	int		fd;

	if (argc == 1)
		bad_input("Error\nDidn't attach a map file, bleedin eejit\n");
	else if (argc == 2)
	{
		if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub"))
			bad_input("Error\nConfiguration file must be .cub\n");
	}
	else if (argc == 3)
	{
		if (!ft_strcmp(argv[2], "--save"))
			data->save = 1;
		else
			bad_input("Error\nToo many arguments, like yer mum\n");
	}
	else
		bad_input("Error\nWayyyy too many arguments gotta yeet\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		bad_input("Error\nCub file missing or damaged\n");
	prs_wrld(data, fd);
	close(fd);
}
