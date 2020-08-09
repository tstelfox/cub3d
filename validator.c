/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validator.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 18:52:01 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/09 18:38:58 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		cub_check(char *argv[])
{
	if (ft_strlen(argv[1]) < 4)
		bad_input("Error\nToo short to be a .cub file\n");
	if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub"))
		bad_input("Error\nConfiguration file must be .cub\n");
}

void		validator(t_data *data, int argc, char *argv[])
{
	int		fd;

	if (argc == 1)
		bad_input("Error\nDidn't attach a map file, bleedin eejit\n");
	else if (argc == 2)
		cub_check(argv);
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
	if (read(fd, NULL, 0) == -1)
		bad_input("Error\nCub file is a directory isn't it? Nice try\n");
	prs_wrld(data, fd);
	close(fd);
}
