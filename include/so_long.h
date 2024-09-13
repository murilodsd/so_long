/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:03:02 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/12 17:35:38 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define SIZE 64
# define IMAGE_DIR "./images/"
# define FLOOR '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define ENEMY 'X'
# define STARTING_POSITION 'P'
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include "../lib/libft/include/libft.h"
# include "./structures.h"

void	check_mem(t_game *game, t_list **ptr_or_matrix_list, \
	void *ptr, char *error_msg);
void	get_map_info(t_game *game);
void	get_map_fd(t_game *game, char **argv);
void	check_map(t_game *game);
void	init_game_variables(t_game *game);
int		handle_key_input(int key, t_game *game);
int		loop_hook_animation(void *game);
void	*xpm_to_image(t_game *game, char *filename);
void	put_image(t_game *game, void *img_ptr, int x, int y);
void	put_image_player_position(t_game *game, void *img_ptr);
void	free_exit_error(t_mem_allocation *mem_allocation, \
	char *error_msg);
void	destroy_free_exit_error(t_game *game, char *error_msg);
int		close_game(void *game);
#endif