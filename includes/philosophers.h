
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include "error.h"

# define TRUE 1
# define FALSE 0

typedef enum	e_state
{
	THINK 	= 0,
	EAT 	= 1,
	SLEEP	= 2
}				t_state;

typedef struct	s_philo
{
	pthread_t		thread;
	time_t			last_meal;
	int				nb;
	struct s_data	*data;
	int				times_eaten;
	t_state			state;
}					t_philo;

typedef struct	s_data
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_must_eat;
	struct s_philo		philos[200];
	time_t				sim_start;
	bool				forks[200];
	pthread_mutex_t		forks_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		dead_mutex;
	bool				sim_end;
}						t_data;

//parsing
bool	ft_parsing(int argc, char **argv, t_data *data);
int		ft_isnum(char *str);
bool	ft_check_is_nb(char **argv);
size_t	ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);

//philosophers
void	ft_create_philos(t_data *data);
bool	ft_philo_dead(t_philo *philo);
bool	ft_philo_full(t_philo *philo);
void	*ft_routine(void *arg);

//initialization
void	ft_init_mutex(t_data *data);
void	ft_destroy_mutexes(t_data *data);
void	ft_init_forks(t_data *data);

//routine
bool	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);

//utils
time_t	ft_timestamp(void);
void	ft_putstr_fd(char *s, int fd);
void	ft_error_message(char *err);
int		ft_atoi(const char *str);
int		ft_isspace(char c);
void	ft_suspend_process(t_data *data, time_t time);

#endif