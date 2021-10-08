#include "philo.h"

void	*must_monitor(void *stat_void)
{
	int		i;
	t_stat	*s;
	int		*cnt;

	s = (t_stat *)stat_void;
	cnt = (int *)malloc(sizeof(int) * s->num_philo);
	if (cnt == NULL)
		return ((void *)ERROR);
	i = -1;
	while (cnt[++i])
		cnt[i] = 0;
	while (1)
	{
		if (check_must_eat(s, cnt) == SUCCESE)
		{
			free(cnt);
			return ((void *)SUCCESE);
		}
	}
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
			print_message(p, PHILO_DIE);
			pthread_mutex_unlock(&(p->stat->die_mutex));
			pthread_mutex_unlock(&(p->use_mutex));
			return ((void *)SUCCESE);
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
	return ((void *)SUCCESE);
}

int	make_philo(t_stat *stat, int i)
{
	void		*p;
	pthread_t	tid1;

	while (i < stat->num_philo)
	{
		p = (void *)(&(stat->philos[i]));
		if (pthread_create(&tid1, NULL, &philo_work, p) != 0)
			return (ERROR);
		pthread_detach(tid1);
		i += 2;
	}
	if (i % 2 == 0)
		ft_usleep(stat->num_philo);
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
	if (make_philo(stat, 0) == ERROR || make_philo(stat, 1) == ERROR)
		return (ERROR);
	return (SUCCESE);
}
