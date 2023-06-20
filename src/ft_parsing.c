
#include "../includes/philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

bool	ft_check_is_nb(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!(ft_isnum(argv[i])))
		{
			ft_error_message(E_TYPE);
			return (FALSE);
		}
		i++;
	}
	i = 1;
	while (argv[i])
	{
		if ((ft_strlen(argv[i]) > 10) || (ft_strlen(argv[i]) == 10
				&& ft_strcmp(argv[i], "2147483647") >= 1))
		{
			ft_error_message(E_NUMB);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/* if there is sixth no argument (must eat x times), we set nb_must_eat to -1
it will tell the program in ft_philo_full that the philosopher 
is never full */
bool	ft_parsing(int argc, char **argv, t_data *data)
{
	if (!ft_check_is_nb(argv))
		return (FALSE);
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->nb_philo > 200 || data->nb_philo == 0)
	{
		ft_error_message(E_NBPHIL);
		return (FALSE);
	}
	data->nb_must_eat = -1;
	if (argc == 6)
	{
		data->nb_must_eat = ft_atoi(argv[5]);
		if (data->nb_must_eat < 0)
		{
			ft_error_message(E_TYPE);
			return (FALSE);
		}
	}
	return (TRUE);
}
