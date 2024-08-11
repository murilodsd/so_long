#include <mlx.h>
#include <stdio.h>
/* #include <X11/keysym.h>
#include <stdlib.h>

int handle_input(int key, void *param)
{
     // Handle the input based on the keycode.
     if (key == XK_Escape)
	printf("Foi pressionada a tecla %d\n", key);
     return (0);
} */

int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;

	mlx_connection = mlx_init();
	if (mlx_connection == NULL)
	{
		fprintf(stderr, "Error: mlx_init() failed\n");
		return (1);
	}
/*
	mlx_window = mlx_new_window(mlx_connection, 800, 600, "Hello world!");
	if (mlx_window == NULL)
	{
 		mlx_destroy_display(mlx_connection);
		free(mlx_connection); 
		fprintf(stderr, "Error: mlx_new_window() failed\n");
		return (1);
	}
	//mlx_key_hook(mlx_window, handle_input, NULL);
	mlx_loop(mlx_window);
	//mlx_destroy_display(mlx_connection);
	*/
	return (0);
}