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

typedef struct	s_philo
{
	int				pnum;			/* 철학자 위치 */
	int				philo_stat;		/* 철학자 상태 */
	int				eat_cnt;		/* 먹은 횟수 */
	uint64_t		limit;			/* 철학자가 죽는 시간 */
	pthread_mutex_t	use_mutex;		/* 죽었는지 확인하는 동안 혹은 먹는 동안 다른 동작을 실행하지 못하게하는 mutex */
									/* 먹는 동안은 죽을 수 없고, 죽었는데 먹을 수 없으니까*/
	struct s_stat	*stat;			/*  */
}				t_philo;

typedef struct	s_stat
{
	int				num_philo;		/* 철학자 수 */
	uint64_t		time_to_die;	/* 죽을때까지 시간 */
	uint64_t		time_to_eat;	/* 먹는 시간 */
	uint64_t		time_to_sleep;	/* 자는 시간 */
	uint64_t		start_time;		/* 시작 시간 */
	int				must_eat_cnt;	/* 먹어야하는 횟수 */
	t_philo			*philos;		/* 철학자 구조체 */
	pthread_mutex_t	*fork_mutex;	/* 포크 사용중인지 확인하는 mutex */
	pthread_mutex_t	die_mutex;		/* 철학자 죽었는지 확인하는 mutex */
}				t_stat;
/*
	fork 해줄때 mutex가 없으면 동시에 fork 하여 포크를
	잡았는지를 확인하지 못하고, 한쪽 포크를 잡아 교착상태가 될 수 있음

	- fork_mutex
	철학자가 포크를 사용중이면 다른 철학자가 포크를 사용하지 못하도록
	mutex를 사용해 포크를 사용중인지 확인
	- die_mutex
	한명이라도 철학자가 죽으면 모든 쓰레드를 종료시켜야하므로
	mutex를 사용해 죽은 철학자가 있는지 확인
	- eat_mutex ???
	철학자가 식사중인지 확인하는 mutex?
*/

#endif