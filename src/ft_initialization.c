
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

void	ft_create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].nb = i + 1;
		data->philos[i].last_meal = data->sim_start;
		data->philos[i].times_eaten = 0;
		data->philos[i].data = data;
		if (pthread_create(&(data->philos[i].thread), NULL,
				&ft_routine, &(data->philos[i])) != 0)
			ft_error_message(E_THREAD);
		i++;
	}
}

void	ft_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return ;
		i++;
	}
}
