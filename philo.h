#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR 1
# define SUCCESE 0

# define PHILO_THINK 0
# define PHILO_FORK 1
# define PHILO_EAT 2
# define PHILO_SLEEP 3
# define PHILO_DIE 4
# define END_EAT 5

typedef struct s_philo
{
	int				pnum;
	int				philo_stat;
	int				eat_cnt;
	uint64_t		limit;
	pthread_mutex_t	use_mutex;
	pthread_mutex_t	must_eat;
	struct s_stat	*stat;
}	t_philo;

typedef struct s_stat
{
	int				num_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		start_time;
	int				must_eat_cnt;
	t_philo			*philos;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	print_mutex;
}	t_stat;

uint64_t	get_time(void);
void		ft_usleep(uint64_t time);
int			philo_atoi(char *str);
void		print_message(t_philo *p, int stat);
int			start_philo(t_stat *stat);
int			init(t_stat *s, int	av[5]);
void		clear_stat(t_stat *s);
int			check_must_eat(t_stat *s, int *cnt);
void		run_philo(t_philo *p);

#endif