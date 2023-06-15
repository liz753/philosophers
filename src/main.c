
#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	if (argc >= 5 && argc <= 6)
	{
		ft_parsing(argc, argv, &data);
		ft_init_mutex(&data);
		pthread_mutex_lock(&(data.dead_mutex));
		data.dead_philo = FALSE;
		pthread_mutex_unlock(&(data.dead_mutex));
		ft_init_forks(&data);
		data.sim_start = ft_timestamp();
		ft_create_philos(&data);
		ft_destroy_mutexes(&data);
	}
	else
		ft_error_message(E_ARG);
	return (0);
}
