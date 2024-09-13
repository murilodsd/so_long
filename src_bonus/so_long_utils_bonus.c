/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:03:57 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/12 17:31:39 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	put_image(t_game *game, void *img_ptr, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, img_ptr, \
		x * SIZE, y * SIZE);
}

void	put_image_player_position(t_game *game, void *img_ptr)
{
	mlx_put_image_to_window(game->mlx, game->window, img_ptr, \
		game->player.x * SIZE, game->player.y * SIZE);
}

void	*xpm_to_image(t_game *game, char *filename)
{
	void	*ptr_img;
	int		*ptr_width;
	int		*ptr_heigth;

	ptr_width = ft_calloc(1, sizeof(int));
	if (!ptr_width)
		destroy_free_exit_error(game, "ft_calloc failed");
	ptr_heigth = ft_calloc(1, sizeof(int));
	if (!ptr_width)
	{
		free(ptr_width);
		destroy_free_exit_error(game, "ft_calloc failed");
	}
	ptr_img = mlx_xpm_file_to_image(game->mlx, filename, \
		ptr_width, ptr_heigth);
	if (*ptr_width != SIZE || *ptr_heigth != SIZE)
	{
		free (ptr_width);
		free(ptr_heigth);
		mlx_destroy_image(game->mlx, ptr_img);
		destroy_free_exit_error(game, "The size of the img must be 64x64");
	}
	free (ptr_width);
	free(ptr_heigth);
	return (ptr_img);
}

void	free_exit_error(t_mem_allocation *mem_allocation, \
	char *error_msg)
{
	if (errno != 0 && errno != 11)
		ft_printf(2, "Error\n%s: %s\n", error_msg, strerror(errno));
	else
		ft_printf(2, "Error\n%s\n", error_msg);
	if (mem_allocation->ptr_mem_list != NULL)
		ft_lstclear(&(mem_allocation->ptr_mem_list), free);
	if (mem_allocation->matrix_mem_list != NULL)
		ft_lstclear(&(mem_allocation->matrix_mem_list), ft_free_matrix);
	exit(EXIT_FAILURE);
}
