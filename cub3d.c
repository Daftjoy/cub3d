#include "mlx.h"
#include <unistd.h>

void 	ft_putchar (char c)
{
	write (1, &c, 1);
}

int deal_key(int key, void *param)
{
	if (key == 67)
		ft_putchar('c');
	ft_putchar('x');
	return (0);
}

int main()
{
	void *mlx_ptr;
	void *win_ptr;
	void *lls_ptr;
	
	mlx_ptr = mlx_init(); /*necesario para iniciar la conexión con el paqute */
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "PAJuo" ); /*win_ptr  hace que las funciones del loop se asocien especificamente con esta ventana*/
	mlx_pixel_put (mlx_ptr, win_ptr, 200, 200, 0xFFFFFF );
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr); /* hace que se quede esperando a que hagas algo*/
	return (0);
}
