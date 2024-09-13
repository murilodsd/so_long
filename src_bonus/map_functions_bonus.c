/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:03:51 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/13 19:58:22 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	check_map_file_extension(t_game *game, char *file_name)
{
	if (ft_strcmp(file_name + (ft_strlen(file_name) - 4), ".ber"))
		destroy_free_exit_error(game, "Map with invalid file type");
}

void	get_map_fd(t_game *game, char **argv)
{
	char	*map_file_name;

	map_file_name = argv[1];
	check_map_file_extension(game, map_file_name);
	game->map_fd = open(map_file_name, O_RDONLY);
	if (game->map_fd == -1)
		destroy_free_exit_error(game, "Error opening file");
}

void	check_get_next_line_error(t_game *game, char *line)
{
	if (line == NULL && errno > 0)
		destroy_free_exit_error(game, "get_next_line failed");
	else if (line != NULL)
	{
		if (*line == '\n')
		{
			free(line);
			destroy_free_exit_error(game, "Map with empty line");
		}
	}
}

void	get_map_info(t_game *game)
{
	char	*concat_lines;
	char	*line;

	concat_lines = ft_calloc(1, sizeof(char));
	check_mem(game, &(game->mem_allocation.ptr_mem_list), \
		concat_lines, "ft_calloc failed");
	line = get_next_line(game->map_fd);
	check_get_next_line_error(game, line);
	if (line == NULL && errno == 0)
		destroy_free_exit_error(game, "Empty map");
	while (line)
	{
		game->height++;
		concat_lines = ft_strjoin(concat_lines, line);
		free(line);
		check_mem(game, &(game->mem_allocation.ptr_mem_list), \
			concat_lines, "ft_strjoin failed");
		line = get_next_line(game->map_fd);
		check_get_next_line_error(game, line);
	}
	game->map_matrix = ft_split(concat_lines, '\n');
	game->width = ft_strlen(game->map_matrix[0]);
	check_mem(game, &(game->mem_allocation.matrix_mem_list), \
		game->map_matrix, "ft_split failed");
}

/* int main(int argc, char *argv[])
{
	t_game	game;

	(void)argc;
	ft_printf(1,"comecou\n");
	init_game_variables(&game, argv);
	ft_printf(1,"%s\n",game.map_file_name);
	get_map_fd(&game, argv);
	get_map_info(&game);
	check_map(&game);
	if (game.mem_allocation.ptr_mem_list != NULL)	
		ft_lstclear(&(game.mem_allocation.ptr_mem_list),free);
	if (game.mem_allocation.matrix_mem_list != NULL)	
		ft_lstclear(&(game.mem_allocation.matrix_mem_list),ft_free_matrix);
	return 0;
} */