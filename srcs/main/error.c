#include "../../include/minirt.h"

void		errormsg2(int num)
{
	// (void) (num);
	// char	*filename;
	// char	*errstring;
	// int		fd;
	// int		i;

	// filename = "srcs/main/error.txt";
	// fd = open(filename, O_RDONLY);
	// i = 0;
	// while ((get_next_line(fd, &errstring) == 1))
	// {

	// 	if (i == errornum)
	// 		break ;
	// 	free(errstring);
	// 	i++;
	// }
	// if (errstring)
	// 	ft_putstr_fd(errstring, 2);
	// else
		// ft_putstr_fd("wrong inputtt", 2);
		ft_putnbr_fd(num, 2);
	// write(1, "\n", 2);
	// close(fd);
	exit(0);
}

void		errormsg(char *msg)
{

	// char	*filename;
	// char	*errstring;
	// int		fd;
	// int		i;

	// filename = "srcs/main/error.txt";
	// fd = open(filename, O_RDONLY);
	// i = 0;
	// while ((get_next_line(fd, &errstring) == 1))
	// {

	// 	if (i == errornum)
	// 		break ;
	// 	free(errstring);
	// 	i++;
	// }
	// if (errstring)
	// 	ft_putstr_fd(errstring, 2);
	// else
		ft_putstr_fd(msg, 2);
	// write(1, "\n", 2);
	// close(fd);
	exit(0);
}

void		*ec_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		errormsg("malloc error");
	return (ptr);
}
void		*ec_calloc(size_t n, size_t size)
{
	void *ptr;

	ptr = ft_calloc(n, size);
	if (ptr == NULL)
		errormsg("malloc error");
	return (ptr);
}


void		free_intersecs(t_intersec *intersec)
{
	t_intersec	*tmp_intersec;
	t_intersec	*current;

	current = intersec;
	while (current)
	{
		tmp_intersec = current;
		if (tmp_intersec->count != 0)
		{
			tmp_intersec->poly.obj_type == SPHERE ?
				free(tmp_intersec->poly.sphere) : NULL;
			tmp_intersec->poly.obj_type == PLANE ?
				free(tmp_intersec->poly.plane) : NULL;
			tmp_intersec->poly.obj_type == CYLINDER ?
				free(tmp_intersec->poly.cylinder) : NULL;
		}
		current = current->next;
		free(tmp_intersec);
	}
}
