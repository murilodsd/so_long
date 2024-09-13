/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:14:34 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/12 17:33:08 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	if_not_null_destroy(t_game *game, void *img_ptr)
{
	if (img_ptr != NULL)
		mlx_destroy_image(game->mlx, img_ptr);
}

static void	call_destroy_functions(t_game *game)
{
	if_not_null_destroy(game, game->img_grass);
	if_not_null_destroy(game, game->img_tree);
	if_not_null_destroy(game, game->img_exit);
	if_not_null_destroy(game, game->img_player_r);
	if_not_null_destroy(game, game->img_player_l);
	if_not_null_destroy(game, game->img_player_u);
	if_not_null_destroy(game, game->img_player_d);
	if_not_null_destroy(game, game->img_player_exit);
	if_not_null_destroy(game, game->img_dead1);
	if_not_null_destroy(game, game->img_dead2);
	if_not_null_destroy(game, game->img_enemy1);
	if_not_null_destroy(game, game->img_enemy2);
	if_not_null_destroy(game, game->img_collectible);
	if (game->window != NULL)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx != NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map_fd != -1000)
		close(game->map_fd);
}

static void	finish_game(t_game *game)
{
	if (game->mem_allocation.ptr_mem_list != NULL)
		ft_lstclear(&(game->mem_allocation.ptr_mem_list), free);
	if (game->mem_allocation.matrix_mem_list != NULL)
		ft_lstclear(&(game->mem_allocation.matrix_mem_list), ft_free_matrix);
	call_destroy_functions(game);
}

void	destroy_free_exit_error(t_game *game, char *error_msg)
{
	call_destroy_functions(game);
	get_next_line(-1);
	free_exit_error(&(game->mem_allocation), error_msg);
}

int	close_game(void *game)
{
	printf("You left the game\n");
	finish_game((t_game *)game);
	exit(EXIT_SUCCESS);
}
