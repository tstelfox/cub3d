/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_texget.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 13:13:23 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/10 19:59:36 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int			elem_check(t_data *data, int i)
{
	while (i < 8)
	{
		if (data->parse[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void		get_sprite(char *line, t_data *data, int i)
{
	int fd;

	while (ft_whitespace(line[i]))
		i++;
	data->sprite_addr = ft_strdup(&line[i]);
	if (ft_strcmp(&data->sprite_addr[ft_strlen(data->sprite_addr) - 4], ".xpm"))
		bad_input("Error\nTextures must be in .xpm format\n");
	fd = open(data->sprite_addr, O_RDONLY);
	if (fd == -1)
		bad_input("Error\nSprite texture damaged or missing\n");
	close(fd);
}

void		get_texture(char *line, t_data *data, int i, int side)
{
	int fd;

	while (ft_whitespace(line[i]))
		i++;
	data->tex[side] = ft_strdup(&line[i]);
	if (ft_strcmp(&data->tex[side][ft_strlen(data->tex[side]) - 4], ".xpm"))
		bad_input("Error\nTextures must be in .xpm format\n");
	fd = open(data->tex[side], O_RDONLY);
	if (fd == -1)
		bad_input("Error\nWall texture damaged or missing\n");
	close(fd);
}

void		grgb(char *line, unsigned char *rgb, int i, int flag)
{
	int temp;

	if (flag == 0)
	{
		temp = 0;
		temp = ft_atoilong(&line[i]);
		temp <= 255 && temp >= 0 ? *rgb = temp
				: bad_input(ERR_F);
	}
	else
	{
		temp = 0;
		temp = ft_atoilong(&line[i]);
		temp <= 255 && temp >= 0 ? *rgb = temp
				: bad_input(ERR_C);
	}
}
