/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:17:12 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/12 17:37:28 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_images(t_game *game)
{
	game->img_grass = xpm_to_image(game, "./images/grass.xpm");
	game->img_tree = xpm_to_image(game, "./images/tree.xpm");
	game->img_exit = xpm_to_image(game, "./images/exit.xpm");
	game->img_player_r = xpm_to_image(game, "./images/player_r.xpm");
	game->img_player_l = xpm_to_image(game, "./images/player_l.xpm");
	game->img_player_d = xpm_to_image(game, "./images/player_d.xpm");
	game->img_player_u = xpm_to_image(game, "./images/player_u.xpm");
	game->img_player_exit = xpm_to_image(game, "./images/player_exit.xpm");
	game->img_dead1 = xpm_to_image(game, "./images/dead1.xpm");
	game->img_dead2 = xpm_to_image(game, "./images/dead2.xpm");
	game->img_collectible = xpm_to_image(game, "./images/collectible.xpm");
	game->img_enemy1 = xpm_to_image(game, "./images/bat1.xpm");
	game->img_enemy2 = xpm_to_image(game, "./images/bat2.xpm");
	if (game->img_player_l == NULL || game->img_player_r == NULL
		|| game->img_grass == NULL || game->img_tree == NULL
		|| game->img_collectible == NULL || game->img_player_d == NULL
		|| game->img_player_u == NULL || game->img_dead1 == NULL
		|| game->img_dead2 == NULL || game->img_enemy1 == NULL
		|| game->img_enemy2 == NULL || game->img_player_exit == NULL
		|| game->img_exit == NULL)
		destroy_free_exit_error(game, \
			"mlx_xpm_file_to_image() in init_images failed");
}

void	init_map(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map_matrix[y][x] == WALL)
				put_image(game, game->img_tree, x, y);
			else if (game->map_matrix[y][x] == FLOOR)
				put_image(game, game->img_grass, x, y);
			else if (game->map_matrix[y][x] == EXIT)
				put_image(game, game->img_exit, x, y);
			else if (game->map_matrix[y][x] == COLLECTIBLE)
				put_image(game, game->img_collectible, x, y);
			else if (game->map_matrix[y][x] == STARTING_POSITION)
				put_image(game, game->img_player_d, x, y);
			else if (game->map_matrix[y][x] == ENEMY)
				put_image(game, game->img_enemy1, x, y);
			x++;
		}
		y++;
	}
}

void	init_game_variables(t_game *game)
{
	errno = 0;
	game->mem_allocation.ptr_mem_list = NULL;
	game->mem_allocation.matrix_mem_list = NULL;
	game->height = 0;
	game->width = 0;
	game->collectible = 0;
	game->count_movements = 0;
	game->game_over = false;
	game->exit_open = false;
	game->mlx = NULL;
	game->window = NULL;
	game->img_grass = NULL;
	game->img_tree = NULL;
	game->img_collectible = NULL;
	game->img_exit = NULL;
	game->img_player_l = NULL;
	game->img_player_r = NULL;
	game->img_player_d = NULL;
	game->img_player_u = NULL;
	game->img_player_exit = NULL;
	game->img_dead1 = NULL;
	game->img_dead2 = NULL;
	game->img_enemy1 = NULL;
	game->img_enemy2 = NULL;
	game->map_fd = -1000;
}

static void	init_game(t_game *game, char **argv)
{
	init_game_variables(game);
	get_map_fd(game, argv);
	get_map_info(game);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		destroy_free_exit_error(game, "mlx_init() failed");
	errno = 0;
	game->window = mlx_new_window(game->mlx, SIZE * game->width, \
		SIZE * (game->height + 0.5), "Hello world!");
	if (game->window == NULL)
		destroy_free_exit_error(game, "mlx_new_window() failed");
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf(2, "The program need one argument (map) and just that!");
		return (1);
	}
	init_game(&game, argv);
	check_map(&game);
	init_images(&game);
	init_map(&game);
	mlx_string_put(game.mlx, game.window, 10, (game.height + 0.4) * SIZE, \
		0xFFFFFF, "Movements: 0");
	mlx_key_hook(game.window, handle_key_input, &game);
	mlx_hook(game.window, 17, (1L << 2), close_game, &game);
	mlx_loop_hook(game.mlx, loop_hook_animation, &game);
	mlx_loop(game.mlx);
	return (0);
}
