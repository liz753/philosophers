
#include "../includes/philosophers.h"

void	ft_check_alive(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (ft_tstamp() - data->philos[i].last_meal
			> data->time_to_die)
		{
			ft_print_dead("died", &(data->philos[i]));
			pthread_mutex_lock(&(data->dead_mutex));
			data->sim_end = TRUE;
			pthread_mutex_unlock(&(data->dead_mutex));
			return ;
		}
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
