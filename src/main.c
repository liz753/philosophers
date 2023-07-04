/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrank <lfrank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:59:00 by lfrank            #+#    #+#             */
/*   Updated: 2023/07/04 10:24:50 by lfrank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_check_alive(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (ft_philo_full(&(data->philos[i])))
			return ;
		pthread_mutex_lock(&(data->last_meal_mutex));
		if (ft_tstamp() - data->philos[i].last_meal
			> data->time_to_die)
		{
			pthread_mutex_unlock(&(data->last_meal_mutex));
			pthread_mutex_lock(&(data->dead_mutex));
			data->sim_end = TRUE;
			pthread_mutex_unlock(&(data->dead_mutex));
			ft_print_dead("died", &(data->philos[i]));
			return ;
		}
		pthread_mutex_unlock(&(data->last_meal_mutex));
		i++;
		if (i == data->nb_philo)
			i = 0;
		usleep(200);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc >= 5 && argc <= 6)
	{
		if (!ft_parsing(argc, argv, &data))
			return (0);
		ft_init_mutex(&data);
		pthread_mutex_lock(&(data.dead_mutex));
		data.sim_end = FALSE;
		pthread_mutex_unlock(&(data.dead_mutex));
		data.sim_start = ft_tstamp();
		ft_create_philos(&data);
		ft_check_alive(&data);
		ft_join_threads(&data);
		ft_destroy_mutexes(&data);
	}
	else
		ft_error_message(E_ARG);
	return (0);
}
