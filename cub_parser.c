/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 11:56:20 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/09 21:07:36 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_floor(char *line, t_data *data, int i)
{
	int temp;

	temp = 0;
	while (ft_whitespace(line[i]))
		i++;
	ft_isdigit(line[i]) ? temp = ft_atoilong(&line[i]) : bad_input(ERR_F);
	temp <= 255 && temp >= 0 ? data->floor.t_rgb.r = temp
			: bad_input(ERR_F);
	while (ft_isdigit(line[i]))
		i++;
	line[i] != ',' ? bad_input(ERR_F) : i++;
	ft_isdigit(line[i]) ? temp = ft_atoilong(&line[i]) :
			bad_input(ERR_F);
	temp <= 255 && temp >= 0 ? data->floor.t_rgb.g = temp :
			bad_input(ERR_F);
	while (ft_isdigit(line[i]))
		i++;
	line[i] != ',' ? bad_input(ERR_F) : i++;
	temp = ft_atoilong(&line[i]);
	temp <= 255 && temp >= 0 ? data->floor.t_rgb.b = temp :
			bad_input(ERR_F);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] != '\0')
		ft_whitespace(line[i]) ? i++ : bad_input(ERR_F);
}

void		get_ceiling(char *line, t_data *data, int i)
{
	int temp;

	temp = 0;
	while (ft_whitespace(line[i]))
		i++;
	ft_isdigit(line[i]) ? temp = ft_atoilong(&line[i]) : bad_input(ERR_C);
	temp <= 255 && temp >= 0 ? data->ceiling.t_rgb.r = temp
			: bad_input(ERR_C);
	while (ft_isdigit(line[i]))
		i++;
	line[i] != ',' ? bad_input(ERR_C) : i++;
	ft_isdigit(line[i]) ? temp = ft_atoilong(&line[i]) : bad_input(ERR_C);
	temp <= 255 && temp >= 0 ? data->ceiling.t_rgb.g = temp :
			bad_input(ERR_C);
	while (ft_isdigit(line[i]))
		i++;
	line[i] != ',' ? bad_input(ERR_C) : i++;
	temp = ft_atoilong(&line[i]);
	temp <= 255 && temp >= 0 ? data->ceiling.t_rgb.b = temp :
			bad_input(ERR_C);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] != '\0')
		ft_whitespace(line[i]) ? i++ : bad_input(ERR_C);
}

void		get_configs(t_data *data, char *line, int i)
{
	if (line[i] == 'R')
		get_res(line, data, i + 1);
	if (line[i] == 'F')
		get_floor(line, data, i + 1);
	if (line[i] == 'C')
		get_ceiling(line, data, i + 1);
	if (line[i] == 'N' && line[i + 1] == 'O')
		get_texture(line, data, i + 2, 0);
	if (line[i] == 'E' && line[i + 1] == 'A')
		get_texture(line, data, i + 2, 1);
	if (line[i] == 'S' && line[i + 1] == 'O')
		get_texture(line, data, i + 2, 2);
	if (line[i] == 'W' && line[i + 1] == 'E')
		get_texture(line, data, i + 2, 3);
	if (line[i] == 'S' && line[i + 1] != 'O')
		get_sprite(line, data, i + 1);
	if (data->parse[8] == 1)
		get_map(line, data);
	free(line);
	line = NULL;
}

void		count_configs(t_data *data, char *line, int i)
{
	if (line[i] == 'R')
		data->parse[0] == 0 ? data->parse[0] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'F')
		data->parse[1] == 0 ? data->parse[1] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'C')
		data->parse[2] == 0 ? data->parse[2] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'N' && line[i + 1] == 'O')
		data->parse[3] == 0 ? data->parse[3] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'E' && line[i + 1] == 'A')
		data->parse[4] == 0 ? data->parse[4] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'S' && line[i + 1] == 'O')
		data->parse[5] == 0 ? data->parse[5] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'W' && line[i + 1] == 'E')
		data->parse[6] == 0 ? data->parse[6] = 1 : bad_input(ERR_ELEM);
	if (line[i] == 'S' && line[i + 1] != 'O')
		data->parse[7] == 0 ? data->parse[7] = 1 : bad_input(ERR_ELEM);
	if (!findchar(line[i], "RFCNESW120\n\0 ") && !ft_whitespace(line[i]))
	{
		printf("what the fuck then [%s]\n", line);
		bad_input("Error\nUnknown element\n");
	}
	if (elem_check(data, i))
		data->parse[8] = 1;
}

int			prs_wrld(t_data *data, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(fd, &line))
	{
		count_configs(data, line, i);
		get_configs(data, line, i);
	}
	count_configs(data, line, i);
	get_configs(data, line, i);
	if (data->parse[8] == 0)
		bad_input(ERR_ELEM);
	if (data->maptemp == NULL)
		bad_input(ERR_MAP);
	data->maparr = ft_split_extra(data->maptemp, '\n');
	map_check(data);
	sprites_init(data);
	free(data->maptemp);
	return (0);
}
