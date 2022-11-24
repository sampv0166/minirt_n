# include "../../include/minirt.h"

static void		parse(t_rt *rt, int fd, t_mlx *mlx)
{
	char	*line;

	while (get_next_line(fd, &line) == 1)
	{
		rt_identify(line, rt, mlx);
		
		free(line);
	}
	rt_identify(line, rt, mlx);
	free(line);
	add_ambient_to_lights(rt);
		
	if (rt->reso.width == 0 || rt->reso.height == 0)
		errormsg(52);
	// if (rt->qts.cam == 0)
	// 	ft_putstr_fd(
	// 	"You didn't set up any cameras. I can't render anything!\n", 1);

}


int				main(int argc, char **argv)
{
	int		fd;
	t_rt	rt;
	t_mlx	mlx;

	init_rt(&rt);
	mlx.mlx = mlx_init();
	if (argc == 1)
		errormsg(0);
	else if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			errormsg(51);
	}
	else
		errormsg(1);
	parse(&rt, fd, &mlx);
	canvas(&rt, &mlx);
	mlx_hook(mlx.win, 33, 1L << 17, close_program, 0);
	mlx_loop(mlx.mlx);
	return (0);
}