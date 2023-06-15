
#include "../includes/philosophers.h"

/* if there is sixth no argument (must eat x times), we set nb_must_eat to -1
it will tell the program in ft_philo_full that the philosopher 
is never full */
void	ft_parsing(int argc, char **argv, t_data *data)
{
	data->nb_philo = ft_atoi(argv[1]);
	if (data->nb_philo <= 0)
		ft_error_message(E_NEG);
	if (data->nb_philo > 200)
		ft_error_message(E_NBPHIL);
	data->time_to_die = ft_atoi(argv[2]);
	if (data->time_to_die < 0)
		ft_error_message(E_NEG);
	data->time_to_eat = ft_atoi(argv[3]);
	if (data->time_to_eat < 0)
		ft_error_message(E_NEG);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep < 0)
		ft_error_message(E_NEG);
	data->nb_must_eat = -1;
	if (argc == 6)
	{
		data->nb_must_eat = ft_atoi(argv[5]);
		if (data->nb_must_eat < 0)
			ft_error_message(E_NEG);
	}
}