#include "so_long.h"
#include <stdbool.h>

void	init_images(t_game *game)
{
	game->img_grass = mlx_xpm_file_to_image(game->mlx_connection, "./images/grass.xpm", &game->size, &game->size);
	game->img_tree = mlx_xpm_file_to_image(game->mlx_connection, "./images/tree.xpm", &game->size, &game->size);
	game->img_exit = mlx_xpm_file_to_image(game->mlx_connection, "./images/exit.xpm", &game->size, &game->size);
	game->img_player_r = mlx_xpm_file_to_image(game->mlx_connection, "./images/spider_r.xpm", &game->size, &game->size);
	game->img_player_l = mlx_xpm_file_to_image(game->mlx_connection, "./images/spider_l.xpm", &game->size, &game->size);
	if (game->img_player_l == NULL || game->img_player_r == NULL || game->img_grass == NULL)
	{
		fprintf(stderr, "Error: mlx_xpm_file_to_image() in init_images failed\n");
		mlx_destroy_window(game->mlx_connection, game->mlx_window);
		mlx_destroy_display(game->mlx_connection);
		free(game->mlx_connection);
		exit(EXIT_FAILURE);
	}
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

/* int main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2)
	{
		errno = 0;
		game.ptr_mem_list = NULL;
		game.map_file_name = argv[1];
		game.map_matrix = ft_calloc(1, sizeof(char*));
		game.size = SIZE;
		game.exit.is_open = false;
		game.mlx_connection = mlx_init();
		game.width = 0;
		game.height = 0;
		game.map_matrix = ft_calloc(1, sizeof(char*));
		if (game.mlx_connection == NULL)
		{
			fprintf(stderr, "Error: mlx_init() failed\n");
			return (1);
		}
		printf("Conectou\n");
		game.mlx_window = mlx_new_window(game.mlx_connection, 768, 640, "Hello world!");
		if (game.mlx_window == NULL)
		{
			mlx_destroy_display(game.mlx_connection);
			free(game.mlx_connection); 
			fprintf(stderr, "Error: mlx_new_window() failed\n");
			return (1);
		}
		init_images(&game);
		init_map(&game);
		mlx_put_image_to_window(game.mlx_connection, game.mlx_window, game.img_player_r, game.player.x * SIZE, game.player.y * SIZE);
		printf("criou janela\n");
		mlx_key_hook(game.mlx_window, handle_input, &game);
		mlx_loop(game.mlx_connection);
		return (0);
	}
	else
	{
		printf("The program need one argument (map) and just that!");
		return (1);
	}
} */