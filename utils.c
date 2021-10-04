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
