#include "philo.h"

void	philo_take_fork(t_philo *p)
{
	pthread_mutex_lock(&(p->stat->fork_mutex[
			(p->pnum - 1 + p->stat->num_philo) % p->stat->num_philo]));
	p->philo_stat = PHILO_FORK;
	pthread_mutex_lock(&(p->stat->fork_mutex[p->pnum]));
	print_message(p);
}

void	philo_eat(t_philo *p)
{
	pthread_mutex_lock(&(p->use_mutex));
	p->philo_stat = PHILO_EAT;
	print_message(p);
	p->limit = get_time() + p->stat->time_to_die;
	usleep(1000 * p->stat->time_to_eat);
	pthread_mutex_unlock(&(p->use_mutex));
	p->eat_cnt++;
}

void	philo_sleep_think(t_philo *p)
{
	pthread_mutex_unlock(&(p->stat->fork_mutex[
			(p->pnum - 1 + p->stat->num_philo) % p->stat->num_philo]));
	pthread_mutex_unlock(&(p->stat->fork_mutex[p->pnum]));
	p->philo_stat = PHILO_SLEEP;
	print_message(p);
	usleep(1000 * p->stat->time_to_sleep);
	p->philo_stat = PHILO_THINK;
	print_message(p);
}

void	run_philo(t_philo *p)
{
	philo_take_fork(p);
	philo_eat(p);
	philo_sleep_think(p);
}
