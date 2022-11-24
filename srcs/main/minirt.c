# include "../../include/minirt.h"

static void		parse(t_rt *rt, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
	    if (line && *line != '#' && *line != '\n')
        {
            	parse_current_line(line, rt);
        }
        else if (!line)
        {
            free_memmory(&line);
            break ;
        }
		free(line);
	}
	
	free(line);
	add_ambient_to_lights(rt);
		
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
		errormsg("not enough arguments");
	else if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			errormsg("error opening file");
	}
	else
		errormsg("too many arguments");
	parse(&rt, fd);
	render(&rt, &mlx);
	mlx_hook(mlx.win, 33, 1L << 17, close_program, 0);
	mlx_loop(mlx.mlx);
	return (0);
}