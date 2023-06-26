
#include "../includes/philosophers.h"

time_t	ft_tstamp(void)
{
	struct timeval	time_of_day;

	gettimeofday (&time_of_day, NULL);
	return ((time_of_day.tv_sec * 1000) + (time_of_day.tv_usec / 1000));
}

void	ft_suspend_process(t_philo *philo, time_t time)
{
	time_t			alarm_clock;
	long			slept_for;
	struct timeval	before_usleep;
	struct timeval	after_usleep;

	alarm_clock = ft_tstamp() + time;
	slept_for = 0;
	while (!ft_suspend_dead(philo) && ft_tstamp() < alarm_clock)
	{
		gettimeofday(&before_usleep, NULL);
		usleep(100);
		gettimeofday(&after_usleep, NULL);
		slept_for += ((after_usleep.tv_sec - before_usleep.tv_sec) * 1000000)
			+ (after_usleep.tv_usec - before_usleep.tv_usec);
		if (slept_for >= time * 1000)
			break ;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	else
	{
		return (0);
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str == NULL)
		return (0);
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}
