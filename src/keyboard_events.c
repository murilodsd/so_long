/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:10:50 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/01 17:39:02 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	clean_string_displayed(t_game *game)
{
	char	*string_to_put;
	char	*str_count_movements;

	str_count_movements = ft_itoa(game->count_movements);
	if (!str_count_movements)
		destroy_free_exit_error(game, "ft_itoa failed");
	string_to_put = ft_strjoin("Movements: ", str_count_movements);
	if (!string_to_put)
	{
		free(str_count_movements);
		str_count_movements = NULL;
		destroy_free_exit_error(game, "ft_strjoin failed");
	}
	mlx_string_put(game->mlx, game->window, 10, \
		(game->height + 0.4) * SIZE, 0x000000, string_to_put);
	free(string_to_put);
	string_to_put = NULL;
	free(str_count_movements);
	str_count_movements = NULL;
}

void	handle_count_movements(t_game *game)
{
	char	*string_to_put;
	char	*str_count_movements;
	
	clean_string_displayed(game);
	game->count_movements++;
	str_count_movements = ft_itoa(game->count_movements);
	if (!str_count_movements)
		destroy_free_exit_error(game, "ft_itoa failed");
	string_to_put = ft_strjoin("Movements: ", str_count_movements);
	if (!string_to_put)
	{
		free(str_count_movements);
		str_count_movements = NULL;
		destroy_free_exit_error(game, "ft_strjoin failed");
	}
	ft_printf(1, "%s\n", string_to_put);
	mlx_string_put(game->mlx, game->window, 10, \
		(game->height + 0.4) * SIZE, 0xFFFFFF, string_to_put);
	free(string_to_put);
	string_to_put = NULL;
	free(str_count_movements);
	str_count_movements = NULL;
}

void	execute_movement(t_game *game, int key)
{
	int	pos_x;
	int	pos_y;
	
	pos_x = game->player.x;
	pos_y = game->player.y;
	if (game->map_matrix[pos_y][pos_x] == 'E')
		mlx_put_image_to_window(game->mlx, game->window, game->img_exit, pos_x * SIZE, pos_y * SIZE);	
	else
		mlx_put_image_to_window(game->mlx, game->window, game->img_grass, pos_x * SIZE, pos_y * SIZE);	
	game->player.y = game->player.y + (key == XK_s) - (key == XK_w);
	game->player.x = game->player.x + (key == XK_d) - (key == XK_a);
	handle_count_movements(game);
	if (game->map_matrix[game->player.y][game->player.x] == 'E')
		mlx_put_image_to_window(game->mlx, game->window, game->img_player_exit, game->player.x * SIZE, game->player.y * SIZE);
	else if (game->map_matrix[game->player.y][game->player.x] == 'X')
		mlx_put_image_to_window(game->mlx, game->window, game->img_dead1, game->player.x * SIZE, game->player.y * SIZE);
	else if (key == XK_d)
		mlx_put_image_to_window(game->mlx, game->window, game->img_player_r, game->player.x * SIZE, game->player.y * SIZE);
	else if (key == XK_a)
		mlx_put_image_to_window(game->mlx, game->window, game->img_player_l, game->player.x * SIZE, game->player.y * SIZE);
	else if (key == XK_w)
		mlx_put_image_to_window(game->mlx, game->window, game->img_player_u, game->player.x * SIZE, game->player.y * SIZE);
	else if (key == XK_s)
		mlx_put_image_to_window(game->mlx, game->window, game->img_player_d, game->player.x * SIZE, game->player.y * SIZE);
}

int	close_game(void *game)
{
	printf("You left the game\n");
	finish_game((t_game *)game);
	exit(EXIT_SUCCESS);
}

int	handle_input(int key, t_game *game)
{
	int	pos_x;
	int	pos_y;
	
	pos_x = game->player.x;
	pos_y = game->player.y;

	if (key == XK_Escape)
		close_game(game);
	else if (game->game_over == false)
	{
		if (key == XK_s && game->map_matrix[pos_y + 1][pos_x] != '1')
			execute_movement(game, key);
		else if (key == XK_w && game->map_matrix[pos_y - 1][pos_x] != '1')
			execute_movement(game, key);
		else if (key == XK_d && game->map_matrix[pos_y][pos_x + 1] != '1')
			execute_movement(game, key);
		else if (key == XK_a && game->map_matrix[pos_y][pos_x - 1] != '1')
			execute_movement(game, key);
		if (game->map_matrix[game->player.y][game->player.x] == 'C')
		{
			game->collectible--;
			if (game->collectible == 0)
				game->exit_open = true;
			game->map_matrix[game->player.y][game->player.x] = '0';
		}
		else if (game->map_matrix[game->player.y][game->player.x] == 'E' && game->collectible == 0)
		{
			printf("YOU WON\n");
			game->game_over = true;
			mlx_string_put(game->mlx, game->window, (game->width - 1) * SIZE, (game->height + 0.4) * SIZE, 0xFFFFFF, "YOU WON");
		}
		else if (game->map_matrix[game->player.y][game->player.x] == 'X')
		{
			printf("YOU LOST\n");
			game->game_over = true;
			mlx_string_put(game->mlx, game->window, (game->width - 1) * SIZE, (game->height + 0.4) * SIZE, 0xFFFFFF, "YOU LOST");
		}
	}
     return (0);
}
