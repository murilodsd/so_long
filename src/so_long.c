#include "../include/so_long.h"
#include <stdbool.h>

void	call_destroy_functions(t_game *game)
{
	if (game->img_grass != NULL)
		mlx_destroy_image(game->mlx_connection, game->img_grass);
	if (game->img_tree != NULL)
		mlx_destroy_image(game->mlx_connection, game->img_tree);
	if (game->img_exit != NULL)
		mlx_destroy_image(game->mlx_connection, game->img_exit);
	if (game->img_player_r != NULL)
		mlx_destroy_image(game->mlx_connection, game->img_player_r);
	if (game->img_player_l != NULL)
		mlx_destroy_image(game->mlx_connection, game->img_player_l);
	if (game->img_collectable != NULL)
		mlx_destroy_image(game->mlx_connection, game->img_collectable);
	if (game->mlx_window != NULL)
		mlx_destroy_window(game->mlx_connection, game->mlx_window);
	if (game->mlx_connection != NULL)
	{
		mlx_destroy_display(game->mlx_connection);
		free(game->mlx_connection);
	}
	if (game->map_fd != -1000)
		close(game->map_fd);
}

void	finish_game(t_game *game)
{
	if (game->mem_allocation.ptr_mem_list != NULL)	
		ft_lstclear(&(game->mem_allocation.ptr_mem_list),free);
	if (game->mem_allocation.matrix_mem_list != NULL)	
		ft_lstclear(&(game->mem_allocation.matrix_mem_list),ft_free_matrix);
	call_destroy_functions(game);
}

void	init_images(t_game *game)
{
	game->img_grass = mlx_xpm_file_to_image(game->mlx_connection, "./images/grass.xpm", &game->size, &game->size);
	game->img_tree = mlx_xpm_file_to_image(game->mlx_connection, "./images/tree.xpm", &game->size, &game->size);
	game->img_exit = mlx_xpm_file_to_image(game->mlx_connection, "./images/exit.xpm", &game->size, &game->size);
	game->img_player_r = mlx_xpm_file_to_image(game->mlx_connection, "./images/spider_r.xpm", &game->size, &game->size);
	game->img_player_l = mlx_xpm_file_to_image(game->mlx_connection, "./images/spider_l.xpm", &game->size, &game->size);
	if (game->img_player_l == NULL || game->img_player_r == NULL || game->img_grass == NULL || game->img_tree == NULL || game->img_exit == NULL)
		destroy_free_exit_error(game, "mlx_xpm_file_to_image() in init_images failed");
}

void	init_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < (WIDTH / SIZE))
	{
		y = 0;
		while (y < (HEIGHT / SIZE))
		{
			if (x == 0 || y == 0 || x == (WIDTH / SIZE) - 1 || y == (HEIGHT / SIZE) -1)
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_tree, x * SIZE, y * SIZE);
			else if (x == 8 && y == 10)
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_exit, x * SIZE, y * SIZE);
			else if (x != y)
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_grass, x * SIZE, y * SIZE);
			else
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_tree, x * SIZE, y * SIZE);
			y++;
		}
		x++;
	}
}
void	change_player_img(t_game *game)
{
	mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_player_r, game->player.x * SIZE, game->player.y * SIZE);
}

void	init_game_variables(t_game *game, char **argv)
{
	errno = 0;
	game->mem_allocation.ptr_mem_list = NULL;
	game->mem_allocation.matrix_mem_list= NULL;
	game->map_file_name = argv[1];
	game->width = 0;
	game->height = 0;
	game->exit.is_open = false;
	game->size = SIZE;
	game->mlx_connection = NULL;
	game->mlx_window = NULL;
	game->img_grass = NULL;
	game->img_tree = NULL;
	game->img_collectable = NULL;
	game->img_exit = NULL;
	game->img_player_l = NULL;
	game->img_player_r = NULL;
	game->map_fd = -1000;
}

void	init_game(t_game *game, char **argv)
{
	init_game_variables(game, argv);
	ft_printf(1,"%s\n",game->map_file_name);
	ft_printf(1,"game variables\n");
	ft_printf(1,"errno = %d\n", errno);
	get_map_fd(game);
	ft_printf(1,"map_fd\n");
	ft_printf(1,"errno = %d\n", errno);
	ft_printf(1,"%d\n",game->map_fd);
	get_map_info(game);
	game->mlx_connection = mlx_init();
	if (game->mlx_connection == NULL)
		destroy_free_exit_error(game, "mlx_init() failed");
	game->mlx_window = mlx_new_window(game->mlx_connection, 768, 640, "Hello world!");
	if (game->mlx_window == NULL)
		destroy_free_exit_error(game, "mlx_new_window() failed");
}

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("The program need one argument (map) and just that!");
		return (1);
	}
	(void)argc;
	ft_printf(1,"comecou\n");
	ft_printf(1,"errno = %d\n", errno);
	init_game(&game, argv);
	check_map(&game);
	ft_printf(1,"Checkmap\n");
	ft_printf(1,"errno = %d\n", errno);
	printf("Conectou\n");
	init_images(&game);
	init_map(&game);
	mlx_put_image_to_window(game.mlx_connection, game.mlx_window, game.img_player_r, game.player.x * SIZE, game.player.y * SIZE);
	printf("criou janela\n");
	mlx_key_hook(game.mlx_window, handle_input, &game);
	mlx_loop(game.mlx_connection);
	return (0);
}
