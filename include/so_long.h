/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:03:02 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/21 18:30:55 by mde-souz         ###   ########.fr       */
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
# include <libft.h>
# include "structures.h"

int	handle_input(int key, t_game *game);
void	check_map(t_game *game);
void	check_map_layout(t_game *game, char component, size_t pos_y, size_t pos_x);
void	check_map_components(t_game *game, char component, size_t pos_y, size_t pos_x);
void	get_map_info(t_game *game);
void	get_map_fd(t_game *game);
void	ft_free_matrix(void	*matrix_address_void);
void	exit_error_free(t_mem_allocation *mem_allocation, char *error_msg);
void	check_mem_alloc(t_mem_allocation *mem_allocation, t_list **ptr_or_matrix_list, void *ptr, char *error_msg);
void	save_pointer(t_mem_allocation *mem_allocation, t_list **ptr_or_matrix_list, void *ptr);

#endif