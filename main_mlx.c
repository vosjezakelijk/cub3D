/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:50:07 by hsamatha          #+#    #+#             */
/*   Updated: 2021/05/12 13:40:34 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	start_hook(t_param *param)
{
	if (!param->act.screen)
		movement(param);
	render(param, 0, 0);
	if (param->act.screen)
		make_screenshot(param, "cub3D.bmp");
	mlx_put_image_to_window(param->mlx.ptr, param->mlx.win, param->mlx.img, 0, 0);
	mlx_do_sync(param->mlx.ptr);
	return (0);
}

static int	key_pressed(int key, t_param *param)
{
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_W)
		param->act.w = 1;
	if (key == KEY_A)
		param->act.a = 1;
	if (key == KEY_S)
		param->act.s = 1;
	if (key == KEY_D)
		param->act.d = 1;
	if (key == KEY_RIGHT)
		param->act.right = 1;
	if (key == KEY_LEFT)
		param->act.left = 1;
	return (0);
}

static int	key_released(int key, t_param *param)
{
	if (key == KEY_W)
		param->act.w = 0;
	if (key == KEY_A)
		param->act.a = 0;
	if (key == KEY_S)
		param->act.s = 0;
	if (key == KEY_D)
		param->act.d = 0;
	if (key == KEY_RIGHT)
		param->act.right = 0;
	if (key == KEY_LEFT)
		param->act.left = 0;
	return (0);
}

static int	exit_game(void)
{
	exit(0);
}

void	start_mlx(t_param *param)
{
	param->mlx.win = mlx_new_window(param->mlx.ptr,
			param->map.scr_w, param->map.scr_h, "Cub3d");
	param->mlx.img = mlx_new_image(param->mlx.ptr,
			param->map.scr_w, param->map.scr_h);
	param->mlx.addr = mlx_get_data_addr(param->mlx.img,
			&param->mlx.bpp, &param->mlx.line_len,
			&param->mlx.endian);
	if (param->act.screen)
	{
		printf("%sMaking screenshot\n%sin progress...\n%s...\n", GRN, BLU, GRN);
		start_hook(param);
	}
	mlx_loop_hook(param->mlx.ptr, start_hook, param);
	mlx_hook(param->mlx.win, 2, 1L << 0, &key_pressed, param);
	mlx_hook(param->mlx.win, 3, 1L << 1, &key_released, param);
	mlx_hook(param->mlx.win, 17, 0, &exit_game, param);
	mlx_loop(param->mlx.ptr);
}
