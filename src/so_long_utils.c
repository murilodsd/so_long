/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:03:57 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/26 17:06:57 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void 	if_not_null_destroy(t_game *game, void *img_ptr)
{
	if (img_ptr != NULL)
		mlx_destroy_image(game->mlx_connection, img_ptr);
}

void	call_destroy_functions(t_game *game)
{
	if_not_null_destroy(game, game->img_grass);
	if_not_null_destroy(game, game->img_tree);
	if_not_null_destroy(game, game->img_exit);
	if_not_null_destroy(game, game->img_player_r);
	if_not_null_destroy(game, game->img_player_l);
	if_not_null_destroy(game, game->img_player_u);
	if_not_null_destroy(game, game->img_player_d);
	if_not_null_destroy(game, game->img_player_exit);
	if_not_null_destroy(game, game->img_dead);
	if_not_null_destroy(game, game->img_enemy);
	if_not_null_destroy(game, game->img_collectible);
	if (game->mlx_window != NULL)
		mlx_destroy_window(game->mlx_connection, game->mlx_window);
	if (game->mlx_connection != NULL)
	{
		mlx_destroy_display(game->mlx_connection);
		free(game->mlx_connection);
	}
	if (game->map_fd != -1000)
		close(game->map_fd);
}

void	finish_game(t_game *game)
{
	if (game->mem_allocation.ptr_mem_list != NULL)	
		ft_lstclear(&(game->mem_allocation.ptr_mem_list),free);
	if (game->mem_allocation.matrix_mem_list != NULL)	
		ft_lstclear(&(game->mem_allocation.matrix_mem_list),ft_free_matrix);
	call_destroy_functions(game);
}

void	destroy_free_exit_error(t_game *game, char *error_msg)
{
	call_destroy_functions(game);
	get_next_line(-1);
	ft_free_exit_error(&(game->mem_allocation), error_msg);
}

void	check_mem(t_game *game, t_list **ptr_or_matrix_list, void *ptr, char *error_msg)
{
	if (!ptr)
		destroy_free_exit_error(game, error_msg);
	else
		ft_save_pointer(&(game->mem_allocation), ptr_or_matrix_list, ptr);
}