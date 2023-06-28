/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrank <lfrank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:58:39 by lfrank            #+#    #+#             */
/*   Updated: 2023/06/27 16:53:50 by lfrank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	ft_suspend_dead(t_philo *philo)
{
	time_t	time_since_lastmeal;

	time_since_lastmeal = ft_tstamp() - philo->last_meal;
	pthread_mutex_lock(&(philo->data->dead_mutex));
	if (philo->data->sim_end == TRUE)
	{
		pthread_mutex_unlock(&(philo->data->dead_mutex));
		return (TRUE);
	}
	if (time_since_lastmeal >= philo->data->time_to_die)
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
	time_t	time_since_lastmeal;

	time_since_lastmeal = ft_tstamp() - philo->last_meal;
	pthread_mutex_lock(&(philo->data->dead_mutex));
	if (philo->data->sim_end == TRUE)
	{
		pthread_mutex_unlock(&(philo->data->dead_mutex));
		return (TRUE);
	}
	if (time_since_lastmeal >= philo->data->time_to_die)
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
	pthread_mutex_lock(&(philo->data->last_meal_mutex));
	if (philo->data->nb_must_eat >= 0
		&& philo->times_eaten >= philo->data->nb_must_eat)
	{
		pthread_mutex_unlock(&(philo->data->last_meal_mutex));
		return (TRUE);
	}
	pthread_mutex_unlock(&(philo->data->last_meal_mutex));
	return (FALSE);
}

void	*ft_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *) arg;
	if (philo->nb % 2 != 0)
		usleep(philo->data->time_to_eat / 2);
	while (ft_philo_dead(philo) == FALSE && ft_philo_full(philo) == FALSE)
	{
		if (ft_eat(philo) == TRUE)
		{
			if (ft_sleep(philo) == TRUE)
				ft_think(philo);
		}
	}
	return (NULL);
}

void	ft_update_times_eaten(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->last_meal_mutex));
	philo->times_eaten += 1;
	pthread_mutex_unlock(&(philo->data->last_meal_mutex));
}
