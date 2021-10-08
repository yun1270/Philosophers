# Philosophers

#### # 과제 설명

###### 1. 조건

 - 철학자는 2명 이상이다.
 - 철학자는 정해진 시간 안에 먹지 않으면 죽는다.
 - 철학자 한 명이 죽으면 프로그램을 종료한다.
 - 철학자는 먹기위해 포크 2개를 잡아야한다.
 - 철학자는 먹고 - 자고 - 생각하는 것을 반복한다.
 - 실행인자는 5개 혹은 6개 이다.

![philo](https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png)

- [사진 출처 : wiki](https://upload.wikimedia.org/wikipedia/commons/7/7bAn_illustration_of_the_dining_philosophers_problem.png)



###### 2. 실행

`./philo number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat] ` 을 사용해 실행한다. (단, 마지막 인자는 반드시 먹어야하는 횟수로 입력하지않으면 1번씩 먹는 것으로 실행)

출력문구는 아래와 같이 출력함

- `timestamp_in_ms X has taken a fork` : 철학자가 포크를 집었을때

- `timestamp_in_ms X is eating` : 철학자가 식사 중일때

- `timestamp_in_ms X is sleeping` : 철학자가 잠을 자는 중일때

- `timestamp_in_ms X is thinking` : 철학자가 생각 중일때

- `timestamp_in_ms X died` : 철학자가 죽음
- `Must eat count reached` : 철학자가 죽지않았지만 마지막 인자인 반드시 먹어야하는 횟수를 만족하여 종료될 때

`X` : 철학자의 번호

`timestamp_in_ms` :  아래와 같은 함수를 사용해 구한 시간

```c
uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}
```

--------

#### # 구현

###### 1. 개념

 `Process`  : 실행중인 프로그램을 이야기한다. 프로세스는 프로그램에서 사용하는 데이터, 메모리와 같은 자원과 쓰레드로 이루어진다.

`Thread` : 쓰레드는 프로세스 내에서 실제로 작업을 실행하는 주체로 프로세스의 실행 단위이다. 각 프로세스는 1개 이상의 쓰레드를 가질 수 있다.

[프로세스와 쓰레드에 대해서]( https://gmlwjd9405.github.io/2018/09/14/process-vs-thread.html )

`동기화문제` : 멀티쓰레드의 경우 동기화로 인해서 자원공유 문제가 생긴다.

동기화문제를 해결하기위해 `mutex` 를 사용해야한다.

`mutex` : 여러 쓰레드에서 동시에 사용할 수 없는 객체이다. 뮤텍스는 `pthread_mutex_lock`, `pthread_mutex_unlock` 함수를 사용해 뮤텍스의 상태를 설정할 수 있다.

[동기화 문제를 해결하기위한 뮤텍스](https://aronglife.tistory.com/entry/NetworkThread-%EB%A9%80%ED%8B%B0%EC%8A%A4%EB%A0%88%EB%93%9C4%EC%8A%A4%EB%A0%88%EB%93%9C-%EB%8F%99%EA%B8%B0%ED%99%94Mutex-SemaphoreLinux)



###### 2. 구조체

```c
typedef struct s_philo
{
	int				pnum;			/* 철학자 위치 */
	int				philo_stat;		/* 철학자 상태 */
	int				eat_cnt;		/* 먹은 횟수 */
	uint64_t		limit;			/* 철학자가 죽는 시간 */
	pthread_mutex_t	use_mutex;		/* 먹는 동안 죽지않도록 다른 동작을 실행하지 못하게하는 mutex */
	struct s_stat	*stat;
}	t_philo;

typedef struct s_stat
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
	pthread_mutex_t	print_mutex;	/* 문구 출력 중 */
}	t_stat;
```

--------

#### # 평가 준비

- `./philo 4 410 200 200` 을 사용하면 철학자가 죽지않고 영원히 실행되어야한다.

`usleep` 함수를 사용하여 먹는 시간과 자는 시간등을 맞는 시간만큼 지나가게 해줬는데 확실한 시간을 구해주는 함수가 아니라 오차가 생겨 그 오차가 10보다 커지면 철학자가 죽어서 종료됨.

```c
void	ft_usleep(uint64_t time)
{
	unsigned long long	start;
	unsigned long long	end;

	start = get_time();
	end = start + (unsigned long long)time;
	while (get_time() < end)
		usleep(10);
}
```

위와 같은 함수를 만들어 usleep을 사용하여도 오차가 생기지않도록 수정함.

