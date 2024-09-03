/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:20:46 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/02 20:36:05 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	change_enemy_img(t_game *game, int *counter, \
	int pos_y, int pos_x)
{
	int	is_player_position_too;

	is_player_position_too = game->player.x == pos_x && game->player.y == pos_y;
	if (*counter == 100)
	{
		if (!is_player_position_too)
			mlx_put_image_to_window(game->mlx, game->window, \
				game->img_enemy2, pos_x * SIZE, pos_y * SIZE);
		else
			mlx_put_image_to_window(game->mlx, game->window, \
				game->img_dead2, pos_x * SIZE, pos_y * SIZE);
	}
	else if (*counter == 200)
	{
		if (!is_player_position_too)
			mlx_put_image_to_window(game->mlx, game->window, \
				game->img_enemy1, pos_x * SIZE, pos_y * SIZE);
		else
			mlx_put_image_to_window(game->mlx, game->window, \
				game->img_dead1, pos_x * SIZE, pos_y * SIZE);
	}
}

int	loop_hook_animation(void *game)
{
	static int	counter;
	size_t		x;
	size_t		y;

	counter++;
	if (counter % 100 == 0)
	{
		y = 0;
		while (y < ((t_game *)game)->height)
		{
			x = 0;
			while (x < ((t_game *)game)->width)
			{
				if (((t_game *)game)->map_matrix[y][x] == 'X')
					change_enemy_img(((t_game *)game), &counter, y, x);
				x++;
			}
			y++;
		}
	}
	if (counter % 200 == 0)
		counter = 0;
	usleep(5000);
	return (0);
}
