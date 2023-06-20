
#include "../includes/philosophers.h"

/* TRUE = fork is available;
check if second fork is available with modulo: philosopher at index 0 gets fork 
0 and 1, last philosopher gets last fork and first fork;
usleep is programmed in microseconds, we do * 1000 to get the milliseconds */
bool	ft_eat(t_philo *philo)
{
	int fork1;
	int fork2;

	fork1 = philo->nb - 1;
	fork2 = philo->nb % philo->data->nb_philo;
	pthread_mutex_lock(&(philo->data->forks_mutex[fork1]));
	pthread_mutex_lock(&(philo->data->forks_mutex[fork2]));
	if (philo->data->forks[fork1] == TRUE 
			&& philo->data->forks[fork2] == TRUE && fork1 != fork2)
	{
		philo->data->forks[philo->nb - 1] = FALSE; 
		philo->data->forks[philo->nb % philo->data->nb_philo] = FALSE;
		pthread_mutex_unlock(&(philo->data->forks_mutex[fork1]));
		pthread_mutex_unlock(&(philo->data->forks_mutex[fork2]));
		pthread_mutex_lock(&(philo->data->print_mutex));
		printf("%ld Philosopher %d has taken a fork\n", ft_timestamp(), philo->nb);
		printf("%ld Philosopher %d has taken a fork\n", ft_timestamp(), philo->nb);
		printf("%ld Philosopher %d is eating\n", ft_timestamp(), philo->nb);
		pthread_mutex_unlock(&(philo->data->print_mutex));
		philo->state = EAT;
		philo->last_meal = ft_timestamp();
		ft_suspend_process(philo->data, philo->data->time_to_eat);
		philo->times_eaten += 1;
		pthread_mutex_lock(&(philo->data->forks_mutex[fork1]));
		pthread_mutex_lock(&(philo->data->forks_mutex[fork2]));
		philo->data->forks[philo->nb - 1] = TRUE;
		philo->data->forks[philo->nb % philo->data->nb_philo] = TRUE;
		pthread_mutex_unlock(&(philo->data->forks_mutex[fork1]));
		pthread_mutex_unlock(&(philo->data->forks_mutex[fork2]));
		
		return (TRUE);
	}
	else
	{
		pthread_mutex_unlock(&(philo->data->forks_mutex[fork1]));
		pthread_mutex_unlock(&(philo->data->forks_mutex[fork2]));
		return (FALSE);
	}
}

void	ft_sleep(t_philo *philo)
{
	time_t	now;

	pthread_mutex_lock(&(philo->data->dead_mutex));
	if (philo->data->sim_end == TRUE)
	{
		pthread_mutex_unlock(&(philo->data->dead_mutex));
		return ;
	}
	pthread_mutex_unlock(&(philo->data->dead_mutex));
	now = ft_timestamp();
	if (philo->state != SLEEP)
	{
		pthread_mutex_lock(&(philo->data->print_mutex));
		printf("%ld Philosopher %d is sleeping\n", now, philo->nb);
		pthread_mutex_unlock(&(philo->data->print_mutex));
	}
	philo->state = SLEEP;
	ft_suspend_process(philo->data, philo->data->time_to_sleep);
}

// think: penser à un calcul qui laisse la chance aux autres 
void	ft_think(t_philo *philo)
{
	time_t	now;

	now = ft_timestamp();
	if (philo->state != THINK)
	{
		pthread_mutex_lock(&(philo->data->print_mutex));
		printf("%ld Philosopher %d is thinking\n", now, philo->nb);
		pthread_mutex_unlock(&(philo->data->print_mutex));
	}
	philo->state = THINK;
}