#include "../include/so_long.h"

void	init_images(t_game *game)
{
	game->img_grass = mlx_xpm_file_to_image(game->mlx, "./images/grass.xpm", &game->size, &game->size);
	game->img_tree = mlx_xpm_file_to_image(game->mlx, "./images/tree.xpm", &game->size, &game->size);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, "./images/exit.xpm", &game->size, &game->size);
	game->img_player_r = mlx_xpm_file_to_image(game->mlx, "./images/player_r.xpm", &game->size, &game->size);
	game->img_player_l = mlx_xpm_file_to_image(game->mlx, "./images/player_l.xpm", &game->size, &game->size);
	game->img_player_d = mlx_xpm_file_to_image(game->mlx, "./images/player_d.xpm", &game->size, &game->size);
	game->img_player_u = mlx_xpm_file_to_image(game->mlx, "./images/player_u.xpm", &game->size, &game->size);
	game->img_player_exit = mlx_xpm_file_to_image(game->mlx, "./images/player_exit.xpm", &game->size, &game->size);
	game->img_dead1 = mlx_xpm_file_to_image(game->mlx, "./images/dead1.xpm", &game->size, &game->size);
	game->img_dead2 = mlx_xpm_file_to_image(game->mlx, "./images/dead2.xpm", &game->size, &game->size);
	game->img_collectible = mlx_xpm_file_to_image(game->mlx, "./images/collectible.xpm", &game->size, &game->size);
	game->img_enemy1= mlx_xpm_file_to_image(game->mlx, "./images/bat1.xpm", &game->size, &game->size);
	game->img_enemy2= mlx_xpm_file_to_image(game->mlx, "./images/bat2.xpm", &game->size, &game->size);
	if (game->img_player_l == NULL || game->img_player_r == NULL || game->img_grass == NULL
		|| game->img_tree == NULL || game->img_exit == NULL || game->img_collectible == NULL
		|| game->img_player_d == NULL || game->img_player_u == NULL
		|| game->img_dead1 == NULL || game->img_dead2 == NULL || game->img_enemy1 == NULL
		|| game->img_enemy2 == NULL || game->img_player_exit == NULL)
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
				mlx_put_image_to_window(game->mlx, game->window, game->img_tree, x * SIZE, y * SIZE);
			else if (game->map_matrix[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->window, game->img_grass, x * SIZE, y * SIZE);
			else if (game->map_matrix[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->window, game->img_exit, x * SIZE, y * SIZE);
			else if (game->map_matrix[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->window, game->img_collectible, x * SIZE, y * SIZE);
			else if (game->map_matrix[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->window, game->img_player_d, x * SIZE, y * SIZE);
			else if (game->map_matrix[y][x] == 'X')
				mlx_put_image_to_window(game->mlx, game->window, game->img_enemy1, x * SIZE, y * SIZE);
			x++;
		}
		y++;
	}
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
	game->game_over = false;
	game->exit_open = false;
	game->size = SIZE;
	game->mlx = NULL;
	game->window = NULL;
	game->img_grass = NULL;
	game->img_tree = NULL;
	game->img_collectible = NULL;
	game->img_exit = NULL;
	game->img_player_l = NULL;
	game->img_player_r = NULL;
	game->img_player_d = NULL;
	game->img_player_u = NULL;
	game->img_player_exit = NULL;
	game->img_dead1 = NULL;
	game->img_dead2 = NULL;
	game->img_enemy1 = NULL;
	game->img_enemy2 = NULL;
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
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		destroy_free_exit_error(game, "mlx_init() failed");
	game->window = mlx_new_window(game->mlx, SIZE * game->width, SIZE * (game->height + 0.5), "Hello world!");
	if (game->window == NULL)
		destroy_free_exit_error(game, "mlx_new_window() failed");
}
void	change_enemy_img(t_game *game, int *counter, size_t pos_y, size_t pos_x)
{
	int	is_player_position_too;

	is_player_position_too = game->player.x == pos_x && game->player.y == pos_y;
	
	if (*counter == 100)
		if (!is_player_position_too)
		mlx_put_image_to_window(game->mlx, game->window, \
			game->img_enemy2, pos_x * SIZE, pos_y * SIZE);
		else
		mlx_put_image_to_window(game->mlx, game->window, \
			game->img_dead2, pos_x * SIZE, pos_y * SIZE);
	else if (*counter == 200)
		{
			if (!is_player_position_too)
			mlx_put_image_to_window(game->mlx, game->window, \
				game->img_enemy1, pos_x * SIZE, pos_y * SIZE);
			else
			mlx_put_image_to_window(game->mlx, game->window, \
				game->img_dead1, pos_x * SIZE, pos_y * SIZE);
		}
}

int loop_hook_animation(void *game)
{
	static int counter;
	size_t	x;
	size_t	y;

	counter++;
	if (counter % 100 == 0)
	{	
		y = 0;
		while (y < ((t_game *)game)->height)
		{
			x = 0;
			while (x < ((t_game *)game)->width)
			{
				if (((t_game *)game)->map_matrix[y][x] == 'X')
					change_enemy_img(((t_game *)game), &counter, y, x);
				x++;
			}
			y++;
		}
	}
	if (counter % 200 == 0)
		counter = 0;
	usleep(5000);
	return (0);
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
	mlx_string_put(game.mlx, game.window, 10, (game.height + 0.4) * SIZE, 0xFFFFFF, "Movements: 0");
	printf("criou janela\n");
	mlx_key_hook(game.window, handle_input, &game);
	mlx_hook(game.window, 17, (1L << 2), close_game, &game);
	mlx_loop_hook(game.mlx, loop_hook_animation, &game);
	mlx_loop(game.mlx);
	return (0);
}
