#include "philo.h"

/* utils.c */
int	philo_atoi(char *str)
{
	int	result;

	result = 0;
	while (*str)
	{
		if (*str != ' ' || *str != '\t' || *str != '\n'
			|| *str != '\v' || *str != '\f' || *str != '\r')
		{
			if (*str < '0' || *str > '9')
				return (ERROR);
			result *= 10;
			result += (*str - '0');
		}
		str++;
	}
	if (result == 0)
		return (ERROR);
	return (result);
}

/* struct.c */
static void	init_philo(t_stat *s, int i)
{
	s->philos[i].pnum = i;
	s->philos[i].eat_cnt = 0;
	s->philos[i].philo_stat = PHILO_THINK;
	s->philos[i].stat = s;
	pthread_mutex_init(&(s->philos[i].eat_mutex), NULL);
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
	pthread_mutex_init(&(s->die_mutex), NULL);
	pthread_mutex_lock(&(s->die_mutex));
	return (SUCCESE);
}

void	clear_stat(t_stat *s)
{
	int	i;

	i = -1;
	usleep(100000);
	while (++i < s->num_philo)
	{
		pthread_mutex_destroy(&(s->philos[i].eat_mutex));
		pthread_mutex_destroy(s->fork_mutex);
	}
	pthread_mutex_destroy(&(s->die_mutex));
	free(s->philos);
	free(s->fork_mutex);
}

/* print_message.c */
uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	print_message(t_philo *p)
{
	if (p->philo_stat == END_EAT)
		printf("Must eat count reached\n");
	else
	{
		printf("%llu\t %d ", get_time() - p->stat->start_time, p->pnum + 1);
		if (p->philo_stat == PHILO_THINK)
			printf("is thinking\n");
		else if (p->philo_stat == PHILO_EAT)
			printf("is eating\n");
		else if (p->philo_stat == PHILO_SLEEP)
			printf("is sleeping\n");
		else if (p->philo_stat == PHILO_FORK)
			printf("has taken a fork\n");
		else
			printf("died\n");
	}
}

/* run_philo.c */
/* 철학자가 먹은 횟수를 확인 */
void	must_monitor(void *stat_void)
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
				s->philo[i].philo_stat = END_EAT;
				cnt++;
			}
		}
	}
	print_message(s->philo[0]);
	pthread_mutex_unlock(&(s->die_mutex));
	return ((void*)0)
}

/* 철학자가 죽었는지 확인 */
void	philo_monitor(void *philo_void)
{
	t_philo *p;

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
		}
		pthread_mutex_unlock(&(p->use_mutex));
		usleep(1000);
	}
}

void	philo_work()
{
	t_philo		*p;
	pthread_t	tid;

	p = (t_philo *)philo_void;
	p->limit = get_time() + p->stat->time_to_die;
	if (pthread_create(&tid, NULL, &philo_monitor, philo_void) != SUCCESE)
		return ((void*)ERROR);
	pthread_detach(tid);
	while (1)
	{
		/* 철학자 행동 */
	}
	return ((void*)0);
}

/* 철학자의 수만큼 쓰레드 생성 */
int	make_philo(t_stat *stat)
{
	int			i;
	pthread_t	tid;

	i = 0;
	while (i < stat->num_philo)
	{
		if (pthread_create(&tid, NULL, &philo_work, (void*)stat) != SUCCESE)
			return (ERROR);
		pthread_detach(tid);
		usleep(100);
		// usleep(500 * stat->eat_time);
		i += 2;
	}
	i = 1;
	while (i < stat->num_philo)
	{
		if (pthread_create(&tid, NULL, &philo_work, (void*)stat) != SUCCESE)
			return (ERROR);
		pthread_detach(tid);
		usleep(100);
		i += 2;
	}
}

/* 반드시 먹어야하는 휫수를 입력한 경우 먹은 횟수를 확인하는 쓰레드 생성 */
int	run_philo(t_stat *stat)
{
	int			i;
	pthread_t	tid;

	s->start_time = get_time();
	if (s->must_eat_cnt != -1)
	{
		if (pthread_create(&tid, NULL, &must_monitor, (void*)stat) != SUCCESE)
			return (ERROR);
		pthread_detach(tid);
	}
	if (make_philo(stat) == ERROR)
		return (ERROR);
	return (SUCCESE);
}

/* main.c */
static int	print_error(char *error)
{
	printf("[ERROR] %s\n", error);
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
		if ((*av)[i - 1] == ERROR)
			return (print_error("Wrong Argument"));
	}
	if (i == 5)
		(*av)[i - 1] = -1;
	if ((*av)[0] == 1)
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
	if (run_philo(&stat) == ERROR)
		return (print_error("During run_philo"));
	pthread_mutex_lock(&(stat.die_mutex));
	pthread_mutex_unlock(&(stat.die_mutex));
	clear_stat(&stat);
}
