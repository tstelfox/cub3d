/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 13:30:00 by tmullan       #+#    #+#                 */
/*   Updated: 2020/07/01 19:35:56 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "./libft/libft.h"

typedef union		u_colour
{
	unsigned int	colour;
	struct			s_rgb
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;
		unsigned char a;
	}				t_rgb;
}					t_colour;

typedef	struct		s_map
{
	int				width;
	int				height;
}					t_map;

typedef	struct		s_player
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
}					t_player;

typedef struct		s_mlx
{
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				bpp;
	int				linelen;
	int				endian;
}					t_mlx;

typedef struct		s_ray
{
	int				mapx;
	int				mapy;
	double			camx;
	double			raydirx;
	double			raydiry;
	double			sidedx;
	double			sidedy;
	double			deltadx;
	double			deltady;
	double			walldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
}					t_ray;

typedef struct		s_data
{
	int				resx;
	int				resy;
	char			*maptemp;
	char			**maparr;
	t_colour		floor;
	t_colour		ceiling;
	t_map			mapsize;
	t_player		player;
	t_mlx			mlx;
	t_ray			ray;
}					t_data;


int					prs_wrld(t_data *data, int argc, char *argv[]);
void				data_init(t_data *data);
int					get_next_line(int fd, char **line);
char				*ft_strjoinnl(char const *s1, char const *s2);
void				mlx_start(t_data *data);
#endif
