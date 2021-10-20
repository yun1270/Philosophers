#include "philo.h"

int	check(char ch, unsigned long long ans, int sign)
{
	if (ch != '\0' && ('0' > ch || ch > '9'))
		return (0);
	if (ans > 9223372036854775807)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (ans * sign);
}

int	ft_atoi(const char *str)
{
	unsigned long long	ans;
	int					sign;

	if (*str == 0)
		return (0);
	ans = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ('0' <= *str && *str <= '9'))
	{
		ans = ans * 10 + (*str - '0');
		str++;
	}
	return (check(*str, ans, sign));
}

int	philo_atoi(char *str)
{
	int	result;

	result = ft_atoi(str);
	if (result == 0 || result < 0)
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
