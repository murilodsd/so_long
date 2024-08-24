/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:10:50 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/24 00:04:53 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_input(int key, t_game *game)
{
	static int	last_movement;

	if (key == XK_Escape)
	{
		printf("Foi pressionada a tecla %d\n", key);
		finish_game(game);
		exit(EXIT_SUCCESS);
	}
	else if (key == XK_s && game->player.y < (HEIGHT / SIZE) - 1)
	{
		mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_grass, game->player.x * SIZE, game->player.y * SIZE);	
		game->player.y++;
		if (last_movement == XK_a)
			mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_player_l, game->player.x * SIZE, game->player.y * SIZE);
		else
			mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_player_r, game->player.x * SIZE, game->player.y * SIZE);
	}
	else if (key == XK_w && game->player.y > 0)
	{
		mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_grass, game->player.x * SIZE, game->player.y * SIZE);	
		game->player.y--;
		if (last_movement == XK_a)
			mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_player_l, game->player.x * SIZE, game->player.y * SIZE);	
		else
			mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_player_r, game->player.x * SIZE, game->player.y * SIZE);	
	}
	else if (key == XK_d && game->player.x < (WIDTH / SIZE) - 1)
	{
		mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_grass, game->player.x * SIZE, game->player.y * SIZE);	
		game->player.x++;
		mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_player_r, game->player.x * SIZE, game->player.y * SIZE);	
		last_movement = XK_d;
	}
	else if (key == XK_a && game->player.x > 0)
	{
		mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_grass, game->player.x * SIZE, game->player.y * SIZE);	
		game->player.x--;
		mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_player_l, game->player.x * SIZE, game->player.y * SIZE);	
		last_movement = XK_a;
	}
     return (0);
}