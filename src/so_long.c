#include "../include/so_long.h"

void	init_images(t_game *game)
{
	game->img_grass = mlx_xpm_file_to_image(game->mlx_connection, "./images/grass.xpm", &game->size, &game->size);
	game->img_tree = mlx_xpm_file_to_image(game->mlx_connection, "./images/tree.xpm", &game->size, &game->size);
	game->img_exit = mlx_xpm_file_to_image(game->mlx_connection, "./images/exit.xpm", &game->size, &game->size);
	game->img_player_r = mlx_xpm_file_to_image(game->mlx_connection, "./images/player_r.xpm", &game->size, &game->size);
	game->img_player_l = mlx_xpm_file_to_image(game->mlx_connection, "./images/player_l.xpm", &game->size, &game->size);
	game->img_player_d = mlx_xpm_file_to_image(game->mlx_connection, "./images/player_d.xpm", &game->size, &game->size);
	game->img_player_u = mlx_xpm_file_to_image(game->mlx_connection, "./images/player_u.xpm", &game->size, &game->size);
	game->img_player_exit = mlx_xpm_file_to_image(game->mlx_connection, "./images/player_exit.xpm", &game->size, &game->size);
	game->img_dead = mlx_xpm_file_to_image(game->mlx_connection, "./images/dead.xpm", &game->size, &game->size);
	game->img_collectible = mlx_xpm_file_to_image(game->mlx_connection, "./images/collectible.xpm", &game->size, &game->size);
	game->img_enemy= mlx_xpm_file_to_image(game->mlx_connection, "./images/bat1.xpm", &game->size, &game->size);
	if (game->img_player_l == NULL || game->img_player_r == NULL || game->img_grass == NULL
		|| game->img_tree == NULL || game->img_exit == NULL || game->img_collectible == NULL
		|| game->img_player_d == NULL || game->img_player_u == NULL
		|| game->img_dead == NULL || game->img_enemy == NULL || game->img_player_exit == NULL)
		destroy_free_exit_error(game, "mlx_xpm_file_to_image() in init_images failed");
}

void	init_map(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map_matrix[y][x] == '1')
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_tree, x * SIZE, y * SIZE);
			else if (game->map_matrix[y][x] == '0')
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_grass, x * SIZE, y * SIZE);
			else if (game->map_matrix[y][x] == 'E')
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_exit, x * SIZE, y * SIZE);
			else if (game->map_matrix[y][x] == 'C')
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_collectible, x * SIZE, y * SIZE);
			else if (game->map_matrix[y][x] == 'P')
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_player_d, x * SIZE, y * SIZE);
			else if (game->map_matrix[y][x] == 'X')
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->img_enemy, x * SIZE, y * SIZE);
			x++;
		}
		y++;
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
	game->collectible = 0;
	game->count_movements = 0;
	game->exit.is_open = false;
	game->size = SIZE;
	game->mlx_connection = NULL;
	game->mlx_window = NULL;
	game->img_grass = NULL;
	game->img_tree = NULL;
	game->img_collectible = NULL;
	game->img_exit = NULL;
	game->img_player_l = NULL;
	game->img_player_r = NULL;
	game->img_player_d = NULL;
	game->img_player_u = NULL;
	game->img_player_exit = NULL;
	game->img_dead = NULL;
	game->img_enemy = NULL;
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
	game->mlx_window = mlx_new_window(game->mlx_connection, SIZE * game->width, SIZE * (game->height + 0.5), "Hello world!");
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
	ft_printf(1,"comecou\n");
	ft_printf(1,"errno = %d\n", errno);
	init_game(&game, argv);
	check_map(&game);
	ft_printf(1,"Checkmap\n");
	ft_printf(1,"errno = %d\n", errno);
	printf("Conectou\n");
	init_images(&game);
	init_map(&game);
	mlx_string_put(game.mlx_connection, game.mlx_window, 10, (game.height + 0.4) * SIZE, 0xFFFFFF, "Movements: 0");
	printf("criou janela\n");
	mlx_key_hook(game.mlx_window, handle_input, &game);
	mlx_loop(game.mlx_connection);
	return (0);
}
