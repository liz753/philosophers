
#include "../includes/philosophers.h"

bool	ft_suspend_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->dead_mutex));
	if (philo->data->sim_end == TRUE)
	{
		pthread_mutex_unlock(&(philo->data->dead_mutex));
		return (TRUE);
	}
	if ((ft_tstamp() - philo->last_meal) >= philo->data->time_to_die)
	{
		philo->data->sim_end = TRUE;
		pthread_mutex_unlock(&(philo->data->dead_mutex));
		return (TRUE);
	}
	pthread_mutex_unlock(&(philo->data->dead_mutex));
	return (FALSE);
}

bool	ft_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->dead_mutex));
	if (philo->data->sim_end == TRUE)
	{
		pthread_mutex_unlock(&(philo->data->dead_mutex));
		return (TRUE);
	}
	if ((ft_tstamp() - philo->last_meal) >= philo->data->time_to_die)
	{
		ft_print_dead("died", philo);	
		philo->data->sim_end = TRUE;
		pthread_mutex_unlock(&(philo->data->dead_mutex));
		return (TRUE);
	}
	pthread_mutex_unlock(&(philo->data->dead_mutex));
	return (FALSE);
}

bool	ft_philo_full(t_philo *philo)
{
	if (philo->times_eaten >= philo->data->nb_must_eat
		&& philo->data->nb_must_eat >= 0)
	{
		return (TRUE);
	}
	return (FALSE);
}

void	*ft_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *) arg;
	if(philo->nb % 2 != 0)
		usleep(philo->data->time_to_eat / 2);
	while (ft_philo_dead(philo) == FALSE && ft_philo_full(philo) == FALSE)
	{
		if (ft_eat(philo) == TRUE)
		{
			if(ft_sleep(philo) == TRUE)
				ft_think(philo);
		}
	}
	return (NULL);
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
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return ;
		i++;
	}
}
