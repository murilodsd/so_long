/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:03:57 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/02 11:17:34 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	put_image(t_game *game, void *img_ptr)
{
	mlx_put_image_to_window(game->mlx, game->window, img_ptr, \
		game->player.x * SIZE, game->player.y * SIZE);
}