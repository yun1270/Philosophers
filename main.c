#include "philo.h"

static int	print_error(char *error)
{
	printf("Philosopher: error: %s\n", error);
	return (ERROR);
}

static int	check_arg(int argc, char *argv[], int (*av)[5])
{
	int		i;

	if (argc < 5 || argc > 6)
		return (print_error("Wrong Argument count"));
	i = 0;
	while (++i < argc)
	{
		(*av)[i - 1] = philo_atoi(argv[i]);
		if ((*av)[i - 1] == -1)
			return (print_error("Wrong Argument"));
	}
	if (i == 5)
		(*av)[i - 1] = -1;
	if ((*av)[0] < 2)
		return (print_error("Need at least 2 Philosopher"));
	return (SUCCESE);
}

int	main(int argc, char *argv[])
{
	int		av[5];
	t_stat	stat;

	if (check_arg(argc, argv, &av) == ERROR)
		return (ERROR);
	if (init(&stat, av) == ERROR)
		return (print_error("During init"));
	if (start_philo(&stat) == ERROR)
		return (print_error("During start_philo"));
	pthread_mutex_lock(&(stat.die_mutex));
	pthread_mutex_unlock(&(stat.die_mutex));
	usleep(100000);
	clear_stat(&stat);
}
