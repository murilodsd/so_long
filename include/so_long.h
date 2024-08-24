/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:03:02 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/24 15:03:35 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define SIZE 64
# define HEIGHT 10*SIZE
# define WIDTH 12*SIZE
# define IMAGE_DIR "./images/"
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include "../lib/libft/include/libft.h"
# include "structures.h"

int	handle_input(int key, t_game *game);
void	check_map(t_game *game);
void	check_map_layout(t_game *game, char component, size_t pos_y, size_t pos_x);
void	check_map_components(t_game *game, char component, size_t pos_y, size_t pos_x);
void	get_map_info(t_game *game);
void	get_map_fd(t_game *game);
void	check_mem(t_game *game, t_list **ptr_or_matrix_list, void *ptr, char *error_msg);
void	init_game_variables(t_game *game, char **argv);
void	call_destroy_functions(t_game *game);
void	destroy_free_exit_error(t_game *game, char *error_msg);
void	finish_game(t_game *game);
#endif