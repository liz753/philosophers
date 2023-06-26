
#include "../includes/philosophers.h"

void	ft_error_message(char *err)
{
	ft_putstr_fd(err, 2);
}

bool	ft_dead_for_print(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->dead_mutex));
	if (philo->data->sim_end == TRUE)
	{
		pthread_mutex_unlock(&(philo->data->dead_mutex));
		return (TRUE);
	}
	pthread_mutex_unlock(&(philo->data->dead_mutex));
	return (FALSE);
}

void	ft_print(char *message, t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print_mutex));
	if (ft_dead_for_print(philo) == FALSE)
	{
		printf("%ld %d %s\n", (ft_tstamp() - philo->data->sim_start),
			philo->nb, message);
	}
	pthread_mutex_unlock(&(philo->data->print_mutex));
}

void	ft_print_dead(char *message, t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print_mutex));
	printf("%ld %d %s\n", (ft_tstamp() - philo->data->sim_start),
		philo->nb, message);
	pthread_mutex_unlock(&(philo->data->print_mutex));
}
