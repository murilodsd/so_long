/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:03:51 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/02 20:40:22 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	check_map_components(t_game *game, char component, \
	size_t y, size_t x)
{
	static int	count_player;
	static int	count_exit;

	if (component == START_POSITION)
	{
		count_player++;
		if (count_player > 1)
			destroy_free_exit_error(game, "More than one starting position!");
		game->player.x = x;
		game->player.y = y;
	}
	else if (component == COLLECTIBLE)
		game->collectible++;
	else if (component == EXIT)
	{
		count_exit++;
		if (count_exit > 1)
			destroy_free_exit_error(game, "Must have just one exit");
	}
	if (!count_player && x == game->width - 1 && y == game->height - 1)
		destroy_free_exit_error(game, "Must have one starting position!");
	if (!count_exit && x == game->width - 1 && y == game->height - 1)
		destroy_free_exit_error(game, "Must have one exit!");
	if (!game->collectible && x == game->width - 1 && y == game->height - 1)
		destroy_free_exit_error(game, "Must have at least one collectible!");
}

static void	check_map_layout(t_game *game, char component, \
	size_t pos_y, size_t pos_x)
{
	int	is_firstorlast_row;
	int	is_firstorlast_col;

	is_firstorlast_row = pos_x == 0 || pos_x == game->width - 1;
	is_firstorlast_col = pos_y == 0 || pos_y == game->height - 1;
	if ((is_firstorlast_row || is_firstorlast_col) && component != WALL)
		destroy_free_exit_error(game, "The map must be surrounded by walls!");
	if (pos_x == 0 && ft_strlen(game->map_matrix[pos_y]) != game->width)
		destroy_free_exit_error(game, "The map must be rectangular");
}

static bool	check_path_components(t_game game, char **map, \
	t_point size, t_point point)
{
	static size_t	count_collectibles;
	static size_t	count_exit;

	if (point.x >= size.x || point.x < 0 || point.y >= size.y || point.y < 0)
		return (FALSE);
	if (map[point.y][point.x] == ENEMY || map[point.y][point.x] == WALL)
		return (FALSE);
	if (map[point.y][point.x] == COLLECTIBLE)
		count_collectibles++;
	if (map[point.y][point.x] == EXIT)
		count_exit++;
	map[point.y][point.x] = WALL;
	check_path_components(game, map, size, (t_point){point.x + 1, point.y});
	check_path_components(game, map, size, (t_point){point.x - 1, point.y});
	check_path_components(game, map, size, (t_point){point.x, point.y + 1});
	check_path_components(game, map, size, (t_point){point.x, point.y - 1});
	if (count_collectibles == game.collectible && count_exit == 1)
		return (TRUE);
	return (FALSE);
}

static void	check_path(t_game *game)
{
	char	**map_copy;

	map_copy = ft_mtxdup(game->map_matrix);
	check_mem(game, &(game->mem_allocation.matrix_mem_list), \
		map_copy, "ft_mtxdup failed");
	if (!check_path_components(*game, map_copy, \
		(t_point){game->width, game->height}, game->player))
		destroy_free_exit_error(game, \
			"Invalid path: No path to collectibles or exit!");
}

void	check_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map_matrix[y])
	{
		x = 0;
		while (game->map_matrix[y][x])
		{
			check_map_components(game, game->map_matrix[y][x], y, x);
			check_map_layout(game, game->map_matrix[y][x], y, x);
			x++;
		}
		y++;
	}
	check_path(game);
}

/* int main(int argc, char *argv[])
{
	t_game	game;

	(void)argc;
	ft_printf(1,"comecou\n");
	init_game_variables(&game, argv);
	ft_printf(1,"%s\n",game.map_file_name);
	get_map_fd(&game);
	get_map_info(&game);
	check_map(&game);
	if (game.mem_allocation.ptr_mem_list != NULL)	
		ft_lstclear(&(game.mem_allocation.ptr_mem_list),free);
	if (game.mem_allocation.matrix_mem_list != NULL)	
		ft_lstclear(&(game.mem_allocation.matrix_mem_list),ft_free_matrix);
	return 0;
} */