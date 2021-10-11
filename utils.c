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
