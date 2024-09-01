/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:03:51 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/30 11:57:53 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	get_map_fd(t_game *game)
{
	ft_printf(1,"dentro do get map  o map file name é %s\n",game->map_file_name);
	game->map_fd = open(game->map_file_name, O_RDONLY);
	if (game->map_fd == -1)
		destroy_free_exit_error(game, "Error opening file");
}

void	get_map_info(t_game *game)
{
	char	*concat_lines;
	char	*line;

	concat_lines = ft_calloc(1,sizeof(char));
	check_mem(game, &(game->mem_allocation.ptr_mem_list), concat_lines, "ft_calloc failed");
	line = get_next_line(game->map_fd);
	if (line == NULL && errno > 0)
		destroy_free_exit_error(game, "get_next_line failed");
	else if (line == NULL && errno == 0)
		destroy_free_exit_error(game, "Empty map");
	game->width = ft_strlen(line) - 1;
	while (line)
	{
		game->height++;
		concat_lines = ft_strjoin(concat_lines, line);
		free(line);
		check_mem(game, &(game->mem_allocation.ptr_mem_list), concat_lines, "ft_strjoin failed");
		line = get_next_line(game->map_fd);
		if (line == NULL && errno > 0)
			destroy_free_exit_error(game, concat_lines);
	}
	game->map_matrix = ft_split(concat_lines, '\n');
	check_mem(game, &(game->mem_allocation.matrix_mem_list), game->map_matrix, "ft_split failed");
}

void	check_map_components(t_game *game, char component, size_t pos_y, size_t pos_x)
{
	static int count_player;
	static int count_exit;
	
	if (component == 'P')
	{
		count_player++;
		if (count_player > 1)
			destroy_free_exit_error(game, "Must have just one starting position!");
		game->player.x = pos_x;
		game->player.y = pos_y;
	}
	else if (component == 'C')
		game->collectible++;
	else if (component == 'E')
	{
		count_exit++;
		if (count_exit > 1)
			destroy_free_exit_error(game, "Must have just one exit");
	}
	if (!count_player && pos_x == game->width -1 && pos_y == game->height -1)
		destroy_free_exit_error(game, "Must have one starting position!");
	if (!count_exit && pos_x == game->width -1 && pos_y == game->height -1)
		destroy_free_exit_error(game, "Must have one exit!");
	if (!game->collectible && pos_x == game->width -1 && pos_y == game->height -1)
		destroy_free_exit_error(game, "Must have at least one collectible!");
}

void	check_map_layout(t_game *game, char component, size_t pos_y, size_t pos_x)
{
	int	is_firstorlast_row;
	int	is_firstorlast_col;

	is_firstorlast_row = pos_x == 0 || pos_x == game->width -1;
	is_firstorlast_col = pos_y == 0 || pos_y == game->height -1;
	if ((is_firstorlast_row || is_firstorlast_col) && component != '1')
		destroy_free_exit_error(game, "The map must be surrounded by walls!");
	if (pos_x == 0 && ft_strlen(game->map_matrix[pos_y]) != game->width)
		destroy_free_exit_error(game, "The map must be rectangular");
}

void	check_map(t_game *game)
{
	int	x;
	int	y;
	
	y = 0;
	while(game->map_matrix[y])
	{
		x = 0;
		while(game->map_matrix[y][x])
		{
			ft_printf(1,"%c",game->map_matrix[y][x]);
			check_map_components(game, game->map_matrix[y][x], y, x);
			check_map_layout(game, game->map_matrix[y][x], y, x);
			x++;
		}
		ft_printf(1,"%c",'\n');
		y++;
	}
	check_path(game);
}

bool	check_path_components(t_game game, char** map, t_point size, t_point point)
{
	static size_t	count_collectibles;
	static size_t	count_exit;
	
	if (point.x >= size.x || point.x < 0 || point.y >= size.y || point.y < 0)
		return (FALSE);
	if (map[point.y][point.x] == 'X' || map[point.y][point.x] == '1' )
		return (FALSE);
	if (map[point.y][point.x] == 'C')
	{
		ft_printf(1, "achamos um collectible em y = %d e x = %d", point.y, point.x);
		count_collectibles++;
	}
	if (map[point.y][point.x] == 'E')
	{
		ft_printf(1, "achamos a saida em y = %d e x = %d", point.y, point.x);
		count_exit++;
	}
	map[point.y][point.x] = '1';	
	check_path_components(game, map, size, (t_point){point.x + 1, point.y});
	check_path_components(game, map, size, (t_point){point.x -1, point.y});
	check_path_components(game, map, size, (t_point){point.x, point.y + 1});
	check_path_components(game, map, size, (t_point){point.x, point.y - 1});
	if (count_collectibles == game.collectible && count_exit == 1)
		return (TRUE);
	return (FALSE);
}

void	check_path(t_game *game)
{
	char	**map_copy;
	
	map_copy = ft_mtxdup(game->map_matrix);
	check_mem(game, &(game->mem_allocation.matrix_mem_list), \
		map_copy, "ft_mtxdup failed");
	if (!check_path_components(*game, map_copy, (t_point){game->width, game->height}, \
		(t_point){game->player.x, game->player.y}))
		destroy_free_exit_error(game, "Invalid path: No path to collectibles or exit!");
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