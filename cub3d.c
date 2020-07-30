/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 13:27:44 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/30 18:12:53 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	data_init(t_data *data)
{
	int i;

	ft_bzero(&data->casts, sizeof(t_cast));
	ft_bzero(&data->ray, sizeof(t_ray));
	ft_bzero(&data->player, sizeof(t_player));
	ft_bzero(&data->sprite, sizeof(t_thijs));
	i = 0;
	while (i < 4)
	{
		ft_bzero(&data->walls[i], sizeof(t_xpm));
		ft_bzero(&data->tex[i], sizeof(char));
		i++;
	}
	data->resx = 0;
	data->resy = 0;
	data->ray.mspeed = 0.09;
	data->ray.rotspeed = 0.07;
	data->maptemp = NULL;
	data->save = 0;
	i = 0;
	while (i < 9)
	{
		data->parse[i] = 0;
		i++;
	}
}

void	zero_mlx(t_mlx *mlx)
{
	mlx->mlx = NULL;
	mlx->mlx_win = NULL;
	mlx->img = NULL;
	mlx->addr = NULL;
	mlx->bpp = 0;
	mlx->linelen = 0;
	mlx->endian = 0;
}

int		main(int argc, char *argv[])
{
	t_data	data;
	t_mlx	mlx;

	data_init(&data);
	zero_mlx(&mlx);
	data.mlx = mlx;
	validator(&data, argc, argv);
	mlx_start(&data);
	return (0);
}
