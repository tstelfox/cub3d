/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 13:27:44 by tmullan       #+#    #+#                 */
/*   Updated: 2020/06/10 12:34:45 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	data_init(t_data *mapdata)
{
	mapdata->resx = 0;
	mapdata->resy = 0;
}

int		main(int argc, char *argv[])
{
	t_data	mapdata;

	data_init(&mapdata);
	prs_wrld(&mapdata, argc, argv);
	return (0);
}








// {
// 	char 	file[10000];
// 	int		fd;
	
// 	if (argc == 1)
// 	{
// 		printf("Didnt attach a map file, dipshit\n");
// 		return (1);
// 	}
// 	fd = open(argv[1],O_RDONLY);
// 	printf("fd is :%d\n", fd);
// 	read(fd, file, 10000);
// 	prs_wrld(file);
// 	return (0);
// }
