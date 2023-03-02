/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:04:57 by mortins-          #+#    #+#             */
/*   Updated: 2023/03/01 16:38:46 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define WIN_WIDTH 1408
#define WIN_HEIGHT 896

int	destruct(t_game *var)
{
	mlx_destroy_image(var->mlx, var->sprite.coin);
	mlx_destroy_image(var->mlx, var->sprite.wall);
	mlx_destroy_image(var->mlx, var->sprite.floor);
	mlx_destroy_image(var->mlx, var->sprite.player_up);
	mlx_destroy_image(var->mlx, var->sprite.player_left);
	mlx_destroy_image(var->mlx, var->sprite.player_down);
	mlx_destroy_image(var->mlx, var->sprite.player_right);
	mlx_destroy_image(var->mlx, var->player.img);
	mlx_clear_window(var->mlx, var->win);
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
	exit (0);
	return (0);
}

int put_error(int n, t_game *var)
{
	if (n == 1)
		ft_printf("Error\nFailed to initiate mlx.");
	if (n == 2)
		ft_printf("Error\nFailed to create a new window.");
	destruct(var);
	return (0);
}

int	render_frame(t_game *var)
{
	mlx_put_image_to_window(var->mlx, var->win, var->player.img, var->player.x, var->player.y);
	return (0);
}

int	keypress(int key, t_game *var)
{
	if (key == KEY_ESC)
		destruct(var);
	if ((key == KEY_W || key == KEY_UP) && (var->player.y - SPRITE_SIZE >= 0))
	{
		var->player.y -= SPRITE_SIZE;
		var->player.img = var->sprite.player_up;
	}
	if ((key == KEY_A || key == KEY_LEFT) && (var->player.x - SPRITE_SIZE >= 0))
	{
		var->player.x -= SPRITE_SIZE;
		var->player.img = var->sprite.player_left;
	}
	if ((key == KEY_S || key == KEY_DOWN) && (var->player.y + (SPRITE_SIZE * 2) <= WIN_HEIGHT))
	{
		var->player.y += SPRITE_SIZE;
		var->player.img = var->sprite.player_down;

	}
	if ((key == KEY_D || key == KEY_RIGHT) && (var->player.x + (SPRITE_SIZE * 2) <= WIN_WIDTH))
	{
		var->player.x += SPRITE_SIZE;
		var->player.img = var->sprite.player_right;
	}
	return (0);
}

void	img_init(t_game *var)
{
	int	i = SPRITE_SIZE;

	var->sprite.wall = mlx_xpm_file_to_image(var->mlx, PATH_WALL, &i, &i);
	var->sprite.floor = mlx_xpm_file_to_image(var->mlx, PATH_FLOOR, &i, &i);
	var->sprite.player_up = mlx_xpm_file_to_image(var->mlx, PATH_PLAYER_U, &i, &i);
	var->sprite.player_left = mlx_xpm_file_to_image(var->mlx, PATH_PLAYER_L, &i, &i);
	var->sprite.player_down = mlx_xpm_file_to_image(var->mlx, PATH_PLAYER_D, &i, &i);
	var->sprite.player_right = mlx_xpm_file_to_image(var->mlx, PATH_PLAYER_R, &i, &i);
	var->sprite.coin = mlx_xpm_file_to_image(var->mlx, PATH_COIN, &i, &i);
	var->player.img = var->sprite.player_down;
	var.player.x = 0;
	var.player.y = 0;
}

int	main(void)
{
	t_game	var;

	var.mlx = mlx_init();
	if (var.mlx == NULL)
		return (put_error(1, &var));
	var.win = mlx_new_window(var.mlx, WIN_WIDTH, WIN_HEIGHT, "Pokemon Rip-Off");
	if (var.win == NULL)
	{
		free(var.win);
		return (put_error(2, &var));
	}
	img_init(&var);;
	mlx_hook(var.win, 17, 0L, destruct, &var);
	mlx_hook(var.win, 2, 1L<<0, keypress, &var);
	mlx_loop_hook(var.mlx, render_frame, &var);
	mlx_loop(var.mlx);
}