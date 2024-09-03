/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:04:47 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/03 12:12:40 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include "./so_long.h"

typedef struct s_game
{
	t_mem_allocation	mem_allocation;
	void				*mlx;
	void				*window;
	void				*img_grass;
	void				*img_tree;
	void				*img_exit;
	void				*img_player_r;
	void				*img_player_l;
	void				*img_player_u;
	void				*img_player_d;
	void				*img_player_exit;
	void				*img_dead1;
	void				*img_dead2;
	void				*img_collectible;
	void				*img_enemy1;
	void				*img_enemy2;
	t_point				player;
	char				**map_matrix;
	int					map_fd;
	size_t				collectible;
	size_t				count_movements;
	int					size;
	size_t				width;
	size_t				height;
	bool				exit_open;
	bool				game_over;
}	t_game;

#endif