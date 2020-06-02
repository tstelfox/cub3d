/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   htest.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/22 11:10:22 by tmullan       #+#    #+#                 */
/*   Updated: 2020/05/22 14:47:59 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_vars {
	void        *mlx;
    void        *win;
}               t_vars;

int             print(int keycode, t_vars *vars)
{
    printf("You pressed the key: %d\n", keycode);
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int				printm(int button, int x, int y, t_vars *vars)
{
	printf("button be %d\n", button);
	printf("Da mouse be at %d %d\n", x, y);
	return (0);
}

int				enter(int button, int x, int y, t_vars *vars)
{
	printf("Hello u dick\n");
	return (0);
}

int				leave(int button, int x, int y, t_vars *vars)
{
	printf("Bye wankstain\n");
	return (0);
}

int             main(void)
{
    t_vars      vars;
	int			keycode;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 600, 600, "Hello world!");

	//God fucking knows why these two hooks do nothing
	mlx_hook(vars.win, 7, 1L<<4, enter, &vars);
	mlx_hook(vars.win, 8, 1L<<5, leave, &vars);

    mlx_key_hook(vars.win, print, &vars);
	mlx_mouse_hook(vars.win, printm, &vars);
    mlx_loop(vars.mlx);

	return (0);
}
