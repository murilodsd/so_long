/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:03:02 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/20 11:43:53 by mde-souz         ###   ########.fr       */
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
void	check_layout(t_game *game, char component, size_t pos_y, size_t pos_x);
void	save_pointer(t_mem_allocation *mem_allocation, t_list **ptr_or_matrix_list, void *ptr);

#endif