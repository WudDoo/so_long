/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:16:32 by mortins-          #+#    #+#             */
/*   Updated: 2023/03/08 18:06:17 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	keypress(int key, t_game *var)
{
	if (key == KEY_ESC)
		destruct(var);
	if ((key == KEY_W || key == KEY_UP) && var->run == 1)
	{
		var->player.img = var->sprite.player_up;
		move(var, 0, -1);
	}
	if ((key == KEY_A || key == KEY_LEFT) && var->run == 1)
	{
		var->player.img = var->sprite.player_left;
		move(var, -1, 0);
	}
	if ((key == KEY_S || key == KEY_DOWN) && var->run == 1)
	{
		var->player.img = var->sprite.player_down;
		move(var, 0, 1);
	}
	if ((key == KEY_D || key == KEY_RIGHT) && var->run == 1)
	{
		var->player.img = var->sprite.player_right;
		move(var, 1, 0);
	}
	return (0);
}

int	destruct(t_game *var)
{
	mlx_destroy_image(var->mlx, var->sprite.coin.img);
	mlx_destroy_image(var->mlx, var->sprite.unlock.img);
	mlx_destroy_image(var->mlx, var->sprite.lock.img);
	mlx_destroy_image(var->mlx, var->sprite.wall.img);
	mlx_destroy_image(var->mlx, var->sprite.floor.img);
	mlx_destroy_image(var->mlx, var->sprite.player_up.img);
	mlx_destroy_image(var->mlx, var->sprite.player_left.img);
	mlx_destroy_image(var->mlx, var->sprite.player_down.img);
	mlx_destroy_image(var->mlx, var->sprite.player_right.img);
	mlx_clear_window(var->mlx, var->win);
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	while (var->map.y)
		free(var->map.map[--var->map.y]);
	free(var->map.map);
	free(var->mlx);
	exit (0);
	return (0);
}

void	move(t_game *var, int x, int y)
{
	put_tile(var, &var->sprite.floor, var->player.x, var->player.y);
	if ((var->map.map[(var->player.y + (y * IMG_SIZE)) / IMG_SIZE] \
		[(var->player.x + (x * IMG_SIZE)) / IMG_SIZE] != '1'))
	{
		if (!(var->map.map[(var->player.y + (y * IMG_SIZE)) / IMG_SIZE] \
			[(var->player.x + (x * IMG_SIZE)) / IMG_SIZE] == 'E' && \
			var->map.coin_count != 0))
		{
			var->player.x += x * IMG_SIZE;
			var->player.y += y * IMG_SIZE;
			if ((var->map.map[var->player.y / IMG_SIZE] \
				[var->player.x / IMG_SIZE] == 'C'))
			{
				coins(var);
			}
			if ((var->map.map[var->player.y / IMG_SIZE] \
				[var->player.x / IMG_SIZE] == 'E'))
			{
				end_game(var);
			}
			ft_printf("Number of moves: %i\n", ++var->player.moves);
		}
	}
	put_tile(var, &var->player.img, var->player.x, var->player.y);
}

void	coins(t_game *var)
{
	put_tile(var, &var->sprite.floor, var->player.x, var->player.y);
	var->map.coin_count--;
	var->map.map[var->player.y / IMG_SIZE][var->player.x / IMG_SIZE] = '0';
	if (var->map.coin_count == 0)
	{
		put_tile(var, &var->sprite.floor, var->map.exit_x, var->map.exit_y);
		put_tile(var, &var->sprite.unlock, var->map.exit_x, var->map.exit_y);
	}
}
