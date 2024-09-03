/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:10:50 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/03 10:19:45 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	clean_string_displayed(t_game *game)
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

static void	handle_count_movements(t_game *game)
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

static void	handle_movement(t_game *game)
{
	if (game->map_matrix[game->player.y][game->player.x] == COLLECTIBLE)
	{
		game->collectible--;
		if (game->collectible == 0)
			game->exit_open = true;
		game->map_matrix[game->player.y][game->player.x] = FLOOR;
	}
	else if (game->map_matrix[game->player.y][game->player.x] == EXIT
		&& game->collectible == 0)
	{
		printf("YOU WON\n");
		game->game_over = true;
		mlx_string_put(game->mlx, game->window, (game->width - 1) * SIZE, \
			(game->height + 0.4) * SIZE, 0xFFFFFF, "YOU WON");
	}
	else if (game->map_matrix[game->player.y][game->player.x] == ENEMY)
	{
		printf("YOU LOST\n");
		game->game_over = true;
		mlx_string_put(game->mlx, game->window, (game->width - 1) * SIZE, \
			(game->height + 0.4) * SIZE, 0xFFFFFF, "YOU LOST");
	}
}

static void	execute_movement(t_game *game, int key)
{
	char	**map;

	map = game->map_matrix;
	if (map[game->player.y][game->player.x] == EXIT)
		put_image_player_position(game, game->img_exit);
	else
		put_image_player_position(game, game->img_grass);
	game->player.y = game->player.y + (key == XK_s) - (key == XK_w);
	game->player.x = game->player.x + (key == XK_d) - (key == XK_a);
	if (map[game->player.y][game->player.x] == EXIT)
		put_image_player_position(game, game->img_player_exit);
	else if (map[game->player.y][game->player.x] == ENEMY)
		put_image_player_position(game, game->img_dead1);
	else if (key == XK_d)
		put_image_player_position(game, game->img_player_r);
	else if (key == XK_a)
		put_image_player_position(game, game->img_player_l);
	else if (key == XK_w)
		put_image_player_position(game, game->img_player_u);
	else if (key == XK_s)
		put_image_player_position(game, game->img_player_d);
	handle_count_movements(game);
	handle_movement(game);
}

int	handle_key_input(int key, t_game *game)
{
	int	pos_x;
	int	pos_y;

	pos_x = game->player.x;
	pos_y = game->player.y;
	if (key == XK_Escape)
		close_game(game);
	else if (game->game_over == false)
	{
		if (key == XK_s && game->map_matrix[pos_y + 1][pos_x] != WALL)
			execute_movement(game, key);
		else if (key == XK_w && game->map_matrix[pos_y - 1][pos_x] != WALL)
			execute_movement(game, key);
		else if (key == XK_d && game->map_matrix[pos_y][pos_x + 1] != WALL)
			execute_movement(game, key);
		else if (key == XK_a && game->map_matrix[pos_y][pos_x - 1] != WALL)
			execute_movement(game, key);
	}
	return (0);
}
