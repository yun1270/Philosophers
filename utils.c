#include "philo.h"

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
				return (-1);
			result *= 10;
			result += (*str - '0');
		}
		str++;
	}
	if (result == 0)
		return (-1);
	return (result);
}

void	ft_usleep(uint64_t time)
{
	unsigned long long	start;
	unsigned long long	end;

	start = get_time();
	end = start + (unsigned long long)time;
	while (get_time() < end)
		usleep(10);
}

int	check_must_eat(t_stat *s, int *cnt)
{
	int		i;
	int		n;

	i = -1;
	n = 0;
	while (++i < s->num_philo)
	{
		if (cnt[i] != 0)
			n++;
		if (cnt[i] == 0 && s->philos[i].eat_cnt >= s->must_eat_cnt)
		{
			pthread_mutex_lock(&(s->philos[i].use_mutex));
			s->philos[i].philo_stat = END_EAT;
			cnt[i] = 1;
		}
	}
	if (n == s->num_philo)
	{
		print_message(&(s->philos[0]), END_EAT);
		pthread_mutex_unlock(&(s->die_mutex));
		return (SUCCESE);
	}
	return (ERROR);
}
