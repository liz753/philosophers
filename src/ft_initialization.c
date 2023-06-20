
#include "../includes/philosophers.h"

void	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&(data->forks_mutex[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(data->print_mutex), NULL);
	pthread_mutex_init(&(data->dead_mutex), NULL);
}

void	ft_destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&(data->forks_mutex[i]));
		i++;
	}
	pthread_mutex_destroy(&(data->print_mutex));
	pthread_mutex_destroy(&(data->dead_mutex));
}

void	ft_init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < 200)
	{
		data->forks[i] = TRUE;
		i++;
	}
}
