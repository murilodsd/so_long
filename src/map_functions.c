/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:03:51 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/20 19:36:56 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_matrix(void	*matrix_address_void)
{
	char	**matrix_address;
	int		i;

	matrix_address = (char **)matrix_address_void;
	if (!matrix_address)
		return ;
	i = 0;
	while (matrix_address[i])
	{
		free(matrix_address[i]);
		matrix_address[i] = NULL;
		i++;
	}
	free(matrix_address);
}

void	exit_error_free(t_mem_allocation *mem_allocation, char *error_msg)
{
	if (errno)
		ft_printf(2,"Error\n%s: %s\n", error_msg, strerror(errno));
	else
		ft_printf(2, "Error\n%s\n", error_msg);
	get_next_line(-1);
	if (mem_allocation->ptr_mem_list != NULL)	
		ft_lstclear(&(mem_allocation->ptr_mem_list),free);
	if (mem_allocation->matrix_mem_list != NULL)	
		ft_lstclear(&(mem_allocation->matrix_mem_list),ft_free_matrix);
	exit(EXIT_FAILURE);
}

void	save_pointer(t_mem_allocation *mem_allocation, t_list **ptr_or_matrix_list, void *ptr)
{
	t_list	*new_node;
/* 	int		i;

	if (ptr_type == TYPE_POINTER)
	{
		i = 0;
		while(((void **)ptr)[i])
		{
			new_node = ft_lstnew(ptr);
			if (!new_node)
				exit_error_free(ptr_mem_list, "Failed to allocate mem for a node");
			ft_lstadd_back(ptr_mem_list, new_node);
			free(new_node);
			i++;
		} 
	} */
	new_node = ft_lstnew(ptr);
	if (!new_node)
		exit_error_free(mem_allocation, "Failed to allocate mem for a node");
	ft_lstadd_back(ptr_or_matrix_list, new_node);
}
void	check_mem_alloc(t_mem_allocation *mem_allocation, t_list **ptr_or_matrix_list, void *ptr, char *error_msg)
{
	if (!ptr)
		exit_error_free(mem_allocation, error_msg);
	else
		save_pointer(mem_allocation, ptr_or_matrix_list, ptr);
}

void	get_map_fd(t_game *game)
{
	game->map_fd = open(game->map_file_name, O_RDONLY);
	if (game->map_fd == -1)
		exit_error_free(&(game->mem_allocation), "Error opening file");
}

void	get_map_info(t_game *game)
{
	char	*concat_lines;
	char	*line;

	concat_lines = ft_calloc(1,sizeof(char));
	check_mem_alloc(&(game->mem_allocation), &(game->mem_allocation.ptr_mem_list), concat_lines, "ft_calloc failed");
	line = get_next_line(game->map_fd);
	if (line == NULL && errno > 0)
		check_mem_alloc(&(game->mem_allocation), &(game->mem_allocation.ptr_mem_list), line, "get_next_line failed");
	else if (line == NULL && errno == 0)
		exit_error_free(&(game->mem_allocation), "Empty map");
	game->width = ft_strlen(line) - 1;
	while (line)
	{
		concat_lines = ft_strjoin(concat_lines, line);
		free(line);
		check_mem_alloc(&(game->mem_allocation), &(game->mem_allocation.ptr_mem_list), concat_lines, "ft_strjoin failed");
		line = get_next_line(game->map_fd);
		if (line == NULL && errno > 0)
			check_mem_alloc(&(game->mem_allocation), &(game->mem_allocation.ptr_mem_list), line, "get_next_line failed");
		game->height++;
	}
	free(line);
	game->map_matrix = ft_split(concat_lines, '\n');
	check_mem_alloc(&(game->mem_allocation), &(game->mem_allocation.matrix_mem_list), game->map_matrix, "ft_split failed");
}

void	check_components(t_game *game, char component, size_t pos_y, size_t pos_x)
{
	static int count_player;
	static int count_exit;
	
	if (component == 'P')
	{
		count_player++;
		if (count_player > 1)
			exit_error_free(&(game->mem_allocation), "Must have just one player!");
		game->player.x = pos_x;
		game->player.y = pos_y;
	}
	if (component == 'C')
		game->collectible++;
	if (component == 'E')
	{
		count_exit++;
		if (count_exit > 1)
			exit_error_free(&(game->mem_allocation), "Must have just one exit");
		game->exit.x = pos_x;
		game->exit.y = pos_y;
	}
	if (!count_player && pos_x == game->width -1 && pos_y == game->height -1)
		exit_error_free(&(game->mem_allocation), "Must have one player!");
	if (!count_exit && pos_x == game->width -1 && pos_y == game->height -1)
		exit_error_free(&(game->mem_allocation), "Must have one exit!");
}

void	check_layout(t_game *game, char component, size_t pos_y, size_t pos_x)
{
	int	is_firstorlast_row;
	int	is_firstorlast_col;

	is_firstorlast_row = pos_x == 0 || pos_x == game->width -1;
	is_firstorlast_col = pos_y == 0 || pos_y == game->height -1;
	if ((is_firstorlast_row || is_firstorlast_col) && component != '1')
		exit_error_free(&(game->mem_allocation), "The map must be surrounded by walls!");
	if (pos_x == 0 && ft_strlen(game->map_matrix[pos_y]) != game->width)
		exit_error_free(&(game->mem_allocation), "The map must be rectangular");
}

int main(int argc, char *argv[])
{
	t_game	game;
	int		x,y;

	(void)argc;
	errno = 0;
	game.mem_allocation.ptr_mem_list = NULL;
	game.mem_allocation.matrix_mem_list= NULL;
	ft_printf(1,"comecou\n");
	game.map_file_name = argv[1];
	ft_printf(1,"%s\n",game.map_file_name);
	game.width = 0;
	game.height = 0;
	
	get_map_fd(&game);
	ft_printf(1,"%d\n",game.map_fd);
	get_map_info(&game);
/* 	ft_printf(1,"%s\n",game.map_matrix[0]);
	ft_printf(1,"%s\n",game.map_matrix[1]);
	ft_printf(1,"%s\n",game.map_matrix[2]);
	ft_printf(1,"%s\n",game.map_matrix[3]);
	ft_printf(1,"%s\n",game.map_matrix[4]);
	ft_printf(1,"%s\n",game.map_matrix[5]); */
	
	y = 0;
	while(game.map_matrix[y])
	{
		x = 0;
		while(game.map_matrix[y][x])
		{
			ft_printf(1,"%c",game.map_matrix[y][x]);
			check_components(&game, game.map_matrix[y][x], y, x);
			check_layout(&game, game.map_matrix[y][x], y, x);
			x++;
		}
		ft_printf(1,"%c",'\n');
		y++;
	}
	return 0;
}
