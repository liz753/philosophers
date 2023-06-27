/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrank <lfrank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:58:06 by lfrank            #+#    #+#             */
/*   Updated: 2023/06/27 16:27:06 by lfrank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	pthread_mutex_init(&(data->last_meal_mutex), NULL);
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
	pthread_mutex_destroy(&(data->last_meal_mutex));
}

void	ft_create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].data = data;
		data->philos[i].nb = i + 1;
		pthread_mutex_lock(&data->last_meal_mutex);
		data->philos[i].last_meal = data->sim_start;
		pthread_mutex_unlock(&data->last_meal_mutex);
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

void	ft_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->last_meal_mutex));
	philo->last_meal = ft_tstamp();
	pthread_mutex_unlock(&(philo->data->last_meal_mutex));
}
