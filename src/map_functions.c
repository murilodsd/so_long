/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:03:51 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/26 16:25:51 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	get_map_fd(t_game *game)
{
	ft_printf(1,"%s\n",game->map_file_name);
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
	//CONFERIR AS CONDICOES DO NULL; TEM QUE TER CHECK NO CASO DE SER NULL? 
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
		game->exit.x = pos_x;
		game->exit.y = pos_y;
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