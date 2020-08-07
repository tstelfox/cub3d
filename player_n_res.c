/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_n_res.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 13:27:03 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/07 13:33:15 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_res(char *line, t_data *data, int i)
{
	int x;
	int y;

	while (!ft_isdigit(line[i]))
		!ft_whitespace(line[i]) ? bad_input(ERR_RES) : i++;
	data->resx = ft_atoilong(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	data->resy = ft_atoilong(&line[i]);
	while (ft_isdigit(line[i]) || ft_whitespace(line[i]))
		i++;
	while (line[i] != '\0')
		!ft_whitespace(line[i]) ? bad_input(ERR_RES) : i++;
	if (data->resx <= 0 || data->resy <= 0)
		bad_input(ERR_RES);
	if (data->save == 1)
		return ;
	mlx_get_screen_size(data->mlx.mlx, &x, &y);
	if (data->resx > x)
		data->resx = x;
	if (data->resy > y)
		data->resy = y;
}

void		southwest_dir(t_data *data, int i, int k)
{
	if (data->maparr[i][k] == 'S')
	{
		data->player.dirx = 0;
		data->player.diry = 1;
		data->player.planey = 0;
		data->player.planex = -0.66;
	}
	if (data->maparr[i][k] == 'W')
	{
		data->player.dirx = -1;
		data->player.diry = 0;
		data->player.planex = 0;
		data->player.planey = -0.66;
	}
}

void		player_pos(t_data *data, int i, int k)
{
	data->player.posx = (double)(k + 0.5);
	data->player.posy = (double)(i + 0.5);
	if (data->maparr[i][k] == 'E')
	{
		data->player.dirx = 1;
		data->player.diry = 0;
		data->player.planex = 0;
		data->player.planey = 0.66;
	}
	if (data->maparr[i][k] == 'N')
	{
		data->player.dirx = 0;
		data->player.diry = -1;
		data->player.planey = 0;
		data->player.planex = 0.66;
	}
	if (data->maparr[i][k] == 'W' || data->maparr[i][k] == 'S')
		southwest_dir(data, i, k);
}

void		player(t_data *data)
{
	int		i;
	int		k;
	char	p;

	i = 1;
	k = 0;
	while (data->maparr[i][k])
	{
		if (ft_isalpha(data->maparr[i][k]))
		{
			p = data->maparr[i][k];
			if (p != 'N' && p != 'S' && p != 'W' && p != 'E')
				bad_input(ERR_MAP);
			player_pos(data, i, k);
			data->maparr[i][k] = '0';
			break ;
		}
		k++;
		if (!data->maparr[i][k])
		{
			k = 0;
			i++;
		}
	}
}
