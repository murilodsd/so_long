/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:04:47 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/20 11:04:42 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include "so_long.h"

typedef struct s_point {
	size_t	x;
	size_t	y;
}	t_point;

typedef struct s_player {
	size_t	x;
	size_t	y;
}	t_player;

typedef struct s_exit {
	bool	is_open;
	size_t	x;
	size_t	y;
}	t_exit;

typedef struct s_sprite {
	int			px_w;
	int			px_h;
	void		*img;
}				t_sprite;

typedef struct s_game
	{
	t_mem_allocation	mem_allocation;
	void	*mlx_connection;
	void	*mlx_window;
	void	*img_grass;
	void	*img_tree;
	void	*img_exit;
	void	*img_player_r;
	void	*img_player_l;
	t_player	player;
	t_exit	exit;
	char	*map_file_name;
	char	**map_matrix;
	int	map_fd;
	size_t	collectible;
	size_t	count_movements;
	int	size;
	size_t 	width;
	size_t 	height;
	}	t_game;

#endif