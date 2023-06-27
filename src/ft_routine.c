#include "../includes/philosophers.h"

void	ft_assign_forks(t_philo *philo, int *fork1, int *fork2)
{
	if (philo->nb % 2 == 0)
	{
		*fork1 = philo->nb - 1;
		*fork2 = philo->nb % philo->data->nb_philo;
	}
	else
	{
		*fork1 = philo->nb % philo->data->nb_philo;
		*fork2 = philo->nb - 1;
	}
}

/* TRUE = fork is available;
check if second fork is available with modulo: philosopher at index 0 gets fork 
0 and 1, last philosopher gets last fork and first fork;
usleep is programmed in microseconds, we do * 1000 to get the milliseconds */
bool	ft_eat(t_philo *philo)
{
	int	fork1;
	int	fork2;

	ft_assign_forks(philo, &fork1, &fork2);
	if (ft_philo_dead(philo) == TRUE)
		return (FALSE);
	ft_take_fork(fork1, philo);
	if (fork1 != fork2)
	{
		ft_take_fork(fork2, philo);
		ft_print("is eating", philo);
		philo->state = EAT;
		pthread_mutex_lock(&(philo->data->last_meal_mutex));
		philo->last_meal = ft_tstamp();
		pthread_mutex_unlock(&(philo->data->last_meal_mutex));
		ft_suspend_process(philo, philo->data->time_to_eat);
		philo->times_eaten += 1;
		pthread_mutex_unlock(&(philo->data->forks_mutex[fork1]));
		pthread_mutex_unlock(&(philo->data->forks_mutex[fork2]));
		return (TRUE);
	}
	else
	{
		pthread_mutex_unlock(&(philo->data->forks_mutex[fork1]));
		ft_suspend_process(philo, philo->data->time_to_die);
		return (FALSE);
	}
}

bool	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->dead_mutex));
	if (philo->data->sim_end == TRUE)
	{
		pthread_mutex_unlock(&(philo->data->dead_mutex));
		return (FALSE);
	}
	pthread_mutex_unlock(&(philo->data->dead_mutex));
	ft_print("is sleeping", philo);
	philo->state = SLEEP;
	ft_suspend_process(philo, philo->data->time_to_sleep);
	return (TRUE);
}

void	ft_think(t_philo *philo)
{
	time_t	now;

	now = ft_tstamp();
	pthread_mutex_lock(&(philo->data->dead_mutex));
	if (philo->data->sim_end == TRUE)
	{
		pthread_mutex_unlock(&(philo->data->dead_mutex));
		return ;
	}
	pthread_mutex_unlock(&(philo->data->dead_mutex));
	if (philo->state != THINK)
		ft_print("is thinking", philo);
	philo->state = THINK;
}

void	ft_take_fork(int fork_index, t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->forks_mutex[fork_index]));
	ft_print("has taken a fork", philo);
}
