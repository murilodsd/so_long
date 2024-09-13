/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_components_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:56:36 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/13 17:36:14 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	check_if_mandatory_components_exist(t_game *game, int count_player, \
	int count_exit)
{
	if (!count_player)
		destroy_free_exit_error(game, "Must have one starting position!");
	if (!count_exit)
		destroy_free_exit_error(game, "Must have one exit!");
	if (!game->collectible)
		destroy_free_exit_error(game, "Must have at least one collectible!");
}

static void	is_invalid_component(t_game *game, char component)
{
	if (component != FLOOR && component != WALL
		&& component != STARTING_POSITION && component != COLLECTIBLE
		&& component != EXIT && component != ENEMY)
		destroy_free_exit_error(game, "Invalid map component");
}

void	check_map_components(t_game *game, char component, \
	size_t y, size_t x)
{
	static int	count_player;
	static int	count_exit;
	bool		is_last_component;

	is_last_component = (x == game->width - 1) && (y == game->height - 1);
	is_invalid_component(game, component);
	if (component == STARTING_POSITION)
	{
		count_player++;
		if (count_player > 1)
			destroy_free_exit_error(game, "More than one starting position!");
		game->player.x = x;
		game->player.y = y;
	}
	else if (component == COLLECTIBLE)
		game->collectible++;
	else if (component == EXIT)
	{
		count_exit++;
		if (count_exit > 1)
			destroy_free_exit_error(game, "Must have just one exit");
	}
	if (is_last_component)
		check_if_mandatory_components_exist(game, count_player, count_exit);
}
