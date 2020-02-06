#include "mlx.h"

int main()
{
	void *mlx_ptr;
	void *win_ptr;
	void *lls_ptr;
	
	mlx_ptr = mlx_init(); /*necesario para iniciar la conexión con el paqute */
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "PAJúo" ); /*win_ptr  hace que las funciones del loop se asocien especçificamente con esta ventana*/
	lls_ptr = _pixel_put ( mlx_ptr, win_ptr, 20, 20, 56 );
	mlx_loop(mlx_ptr); /* hace que se quede esperando a que hagas algo*/
	mlx_loop(lls_ptr); /* hace que se quede esperando a que hagas algo*/
	return (0);
}
