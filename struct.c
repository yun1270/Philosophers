#include "philo.h"

static void	init_philo(t_stat *s, int i)
{
	s->philos[i].pnum = i;
	s->philos[i].eat_cnt = 0;
	s->philos[i].philo_stat = PHILO_THINK;
	s->philos[i].stat = s;
	pthread_mutex_init(&(s->philos[i].use_mutex), NULL);
	pthread_mutex_init(&(s->philos[i].must_eat), NULL);
	pthread_mutex_lock(&(s->philos[i].must_eat));
	pthread_mutex_init(&(s->fork_mutex[i]), NULL);
}

int	init(t_stat *s, int	av[5])
{
	int	i;

	i = 0;
	s->num_philo = av[0];
	s->time_to_die = av[1];
	s->time_to_eat = av[2];
	s->time_to_sleep = av[3];
	s->must_eat_cnt = av[4];
	s->philos = (t_philo *)malloc(sizeof(t_philo) * s->num_philo);
	if (s->philos == NULL)
		return (ERROR);
	s->fork_mutex = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * s->num_philo);
	if (s->fork_mutex == NULL)
	{
		free(s->philos);
		return (ERROR);
	}
	i = -1;
	while (++i < s->num_philo)
		init_philo(s, i);
	pthread_mutex_init(&(s->print_mutex), NULL);
	pthread_mutex_init(&(s->die_mutex), NULL);
	pthread_mutex_lock(&(s->die_mutex));
	return (SUCCESE);
}

void	clear_stat(t_stat *s)
{
	int	i;

	i = -1;
	usleep(10000);
	while (++i < s->num_philo)
	{
		pthread_mutex_destroy(&(s->philos[i].use_mutex));
		pthread_mutex_destroy(&(s->philos[i].must_eat));
		pthread_mutex_destroy(s->fork_mutex);
	}
	pthread_mutex_destroy(&(s->print_mutex));
	pthread_mutex_destroy(&(s->die_mutex));
	free(s->philos);
	free(s->fork_mutex);
}
