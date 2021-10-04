#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	print_philo_stat(t_philo *p, int stat)
{
	if (stat == END_EAT)
		printf("Must eat count reached\n");
	else
	{
		printf("%d\t %d ", (int)(get_time() - p->stat->start_time), p->pnum + 1);
		if (stat == PHILO_THINK)
			printf("is thinking\n");
		else if (stat == PHILO_EAT)
			printf("is eating\n");
		else if (stat == PHILO_SLEEP)
			printf("is sleeping\n");
		else if (stat == PHILO_FORK)
			printf("has taken a fork\n");
		else
			printf("died\n");
	}
}

void	print_message(t_philo *p, int stat)
{
	int	end;

	end = 0;
	pthread_mutex_lock(&(p->stat->print_mutex));
	if (end == 0)
	{
		print_philo_stat(p, stat);
		if (stat == END_EAT || stat == PHILO_DIE)
			end = 1;
	}
	if (end == 0)
		pthread_mutex_unlock(&(p->stat->print_mutex));
}
