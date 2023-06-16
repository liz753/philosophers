
#include "../includes/philosophers.h"

/* TRUE = fork is available;
check if second fork is available with modulo: philosopher at index 0 gets fork 
0 and 1, last philosopher gets last fork and first fork;
usleep is programmed in microseconds, we do * 1000 to get the milliseconds */
bool	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->forks_mutex));
	if (philo->data->forks[philo->nb - 1] == TRUE 
			&& philo->data->forks[philo->nb % philo->data->nb_philo] == TRUE)
	{
		philo->data->forks[philo->nb - 1] = FALSE; 
		philo->data->forks[philo->nb % philo->data->nb_philo] = FALSE;
		pthread_mutex_unlock(&(philo->data->forks_mutex));
		pthread_mutex_lock(&(philo->data->print_mutex));
		printf("%ld Philosopher %d has taken a fork\n", philo->last_meal, philo->nb);
		printf("%ld Philosopher %d has taken a fork\n", philo->last_meal, philo->nb);
		pthread_mutex_unlock(&(philo->data->print_mutex));
		pthread_mutex_lock(&(philo->data->print_mutex));
		printf("%ld Philosopher %d is eating\n", philo->last_meal, philo->nb);
		pthread_mutex_unlock(&(philo->data->print_mutex));
		philo->state = EAT;
		philo->last_meal = ft_timestamp();
		usleep(philo->data->time_to_eat * 1000);
		philo->times_eaten += 1;
		pthread_mutex_lock(&(philo->data->forks_mutex));
		philo->data->forks[philo->nb - 1] = TRUE;
		philo->data->forks[philo->nb % philo->data->nb_philo] = TRUE;
		pthread_mutex_unlock(&(philo->data->forks_mutex));
		return (TRUE);
	}
	else
	{
		pthread_mutex_unlock(&(philo->data->forks_mutex));
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
	usleep(philo->data->time_to_sleep * 1000);
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