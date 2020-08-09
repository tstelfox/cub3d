/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 13:30:00 by tmullan       #+#    #+#                 */
/*   Updated: 2020/08/09 18:41:30 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include "./libft/libft.h"

# define ERR_RES "Error\nResolution misconfigured\n"
# define ERR_F "Error\nFloor misconfigured\n"
# define ERR_C "Error\nCeiling misconfigured\n"
# define ERR_ELEM "Error\nIncorrect amount of configuration elements\n"
# define ERR_MAP "Error\nYer map is a dose of shite\n"
# define ERR_MLX "Error\nMlx malfunction\n"

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

typedef struct		s_xpm
{
	void			*img;
	int				height;
	int				width;
	int				bpp;
	int				linelen;
	int				endian;
}					t_xpm;

typedef struct		s_thijs
{
	double			x;
	double			y;
	double			dist;
}					t_thijs;

typedef struct		s_cast
{
	double			spritex;
	double			spritey;
	double			invdet;
	double			tranx;
	double			trany;
	int				screenx;
	int				spriteh;
	int				spritew;
	int				dstarty;
	int				dendy;
	int				dstartx;
	int				dendx;
	double			*zbuffer;
}					t_cast;

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
	double			mspeed;
	double			rotspeed;
	int				key[6];
	int				compass;
	double			step;
}					t_ray;

typedef struct		s_data
{
	int				bmp;
	int				save;
	int				parse[9];
	long			resx;
	long			resy;
	int				maplength;
	int				spritenum;
	char			*maptemp;
	char			**maparr;
	t_colour		floor;
	t_colour		ceiling;
	t_colour		texcol;
	t_player		player;
	t_mlx			mlx;
	t_ray			ray;
	t_xpm			walls[4];
	char			*tex[4];
	t_xpm			spt;
	char			*sprite_addr;
	t_thijs			*sprite;
	t_cast			casts;
}					t_data;

int					prs_wrld(t_data *data, int fd);
void				data_init(t_data *data);
int					get_next_line(int fd, char **line);
char				*ft_strjoinnl(char *s1, char *s2, int i, int k);
void				mlx_start(t_data *data);
void				my_mlx_pixel_put(t_data *data, int x, int y, int colour);
unsigned int		colour_getter(t_data *data, int x, int y, int compass);
int					raycaster(t_data *data);
int					frame_update(t_data *data);
int					movement(t_data *data);
void				sprites_init(t_data *data);
void				sprite_order(t_data *data);
void				sprite_render(t_data *data);
void				screenshotter(t_data *data);
int					ft_strcmp(const char *s1, const char *s2);
void				validator(t_data *data, int argc, char *argv[]);
void				bad_input(char *error);
int					quit(void);
int					ft_whitespace(char c);
int					keypressed(int keycode, t_data *data);
int					keyreleased(int keycode, t_data *data);
int					frames(t_data *data);
void				drawer(t_data *data, int x, double textx);
void				drawing(t_data *data, int x, double texpos, double textx);
int					calc_drawline(t_data *data);
void				map_check(t_data *data);
void				player(t_data *data);
long int			ft_atoilong(const char *str);
char				**ft_split_extra(char const *s, char c);
int					elem_check(t_data *data, int i);
void				get_sprite(char *line, t_data *data, int i);
void				get_texture(char *line, t_data *data, int i, int side);
void				get_map(char *line, t_data *data);
void				get_res(char *line, t_data *data, int i);
#endif
