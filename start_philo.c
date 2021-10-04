#include "philo.h"

void	*must_monitor(void *stat_void)
{
	int		i;
	int		cnt;
	t_stat	*s;

	s = (t_stat *)stat_void;
	cnt = 0;
	while (cnt < s->must_eat_cnt)
	{
		i = -1;
		while (++i < s->num_philo)
		{
			if (s->philos[i].eat_cnt >= s->must_eat_cnt)
			{
				s->philos[i].philo_stat = END_EAT;
				cnt++;
			}
		}
	}
	print_message(&(s->philos[0]));
	pthread_mutex_unlock(&(s->die_mutex));
	return ((void *)0);
}

void	*philo_monitor(void *philo_void)
{
	t_philo	*p;

	p = (t_philo *)philo_void;
	while (1)
	{
		pthread_mutex_lock(&(p->use_mutex));
		if (get_time() > p->limit)
		{
			p->philo_stat = PHILO_DIE;
			print_message(p);
			pthread_mutex_unlock(&(p->stat->die_mutex));
			pthread_mutex_unlock(&(p->use_mutex));
			return ((void *)0);
		}
		pthread_mutex_unlock(&(p->use_mutex));
		usleep(1000);
	}
}

void	*philo_work(void *philo_void)
{
	t_philo		*p;
	pthread_t	tid;

	p = (t_philo *)philo_void;
	p->limit = get_time() + p->stat->time_to_die;
	if (pthread_create(&tid, NULL, &philo_monitor, philo_void) != SUCCESE)
		return ((void *)ERROR);
	pthread_detach(tid);
	while (1)
		run_philo(p);
	return ((void *)0);
}

int	make_philo(t_stat *stat)
{
	int			i;
	void		*p;
	pthread_t	tid;

	i = 0;
	while (i < stat->num_philo)
	{
		p = (void *)(&(stat->philos[i]));
		if (pthread_create(&tid, NULL, &philo_work, p) != SUCCESE)
			return (ERROR);
		pthread_detach(tid);
		i += 2;
	}
	usleep(10000);
	i = 1;
	while (i < stat->num_philo)
	{
		p = (void *)(&(stat->philos[i]));
		if (pthread_create(&tid, NULL, &philo_work, p) != SUCCESE)
			return (ERROR);
		pthread_detach(tid);
		i += 2;
	}
	return (SUCCESE);
}

int	start_philo(t_stat *stat)
{
	pthread_t	tid;

	stat->start_time = get_time();
	if (stat->must_eat_cnt != -1)
	{
		if (pthread_create(&tid, NULL, &must_monitor, (void *)stat) != SUCCESE)
			return (ERROR);
		pthread_detach(tid);
	}
	if (make_philo(stat) == ERROR)
		return (ERROR);
	return (SUCCESE);
}
