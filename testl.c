/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testl.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 11:56:07 by tmullan       #+#    #+#                 */
/*   Updated: 2020/05/28 12:54:57 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

typedef struct	s_data 
{
	void		*mlx;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx_win;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = colour;
}

int		print(int keycode, t_data *img)
{
	printf("You pushed key no. %d\n", keycode);
	return (0);
}

// Try making the moveable fucking square then
int		square_move(int keycode, t_data *img)
{
	printf("You are indeed pressing a key such as %d\n", keycode);
	// mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	if (keycode == 2) //this is the 'd' key 
	{
		printf("Please no segfault\n");
		my_mlx_pixel_put(&img, 10, 10, 0x000000FF);
		// img.img = mlx_new_image(mlx, 600, 600);
	}
	return (0);
}

int		render_next_frame(t_data *img)
{
	mlx_key_hook(img->mlx_win, square_move, &img);
	return (0);
}

int		main(void)
{
	t_data	img;
	int		offset;

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 600, 600, "mumyer");
	
	img.img = mlx_new_image(img.mlx, 600, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	// my_mlx_pixel_put(&img, 5, 5, 0x000000FF);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_loop_hook(img.mlx, render_next_frame, &img);
	mlx_loop(img.mlx);
}
