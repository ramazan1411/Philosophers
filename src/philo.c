#include "../philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	if (philo->data->philo_count == 1)
	{
		ft_usleep(philo->data->time_to_die + 1);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_meal_time = get_time();
	philo->eat_count++;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!is_dead(philo->data))
	{
		philo_eat(philo);
		if (is_dead(philo->data))
			break ;
		philo_sleep(philo);
		philo_think(philo);
		if (philo->data->must_eat_count != -1 && 
			philo->eat_count >= philo->data->must_eat_count)
			break ;
	}
	return (NULL);
}

int	all_ate_enough(t_data *data, t_philo *philos)
{
	int	i;

	if (data->must_eat_count == -1)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		if (philos[i].eat_count < data->must_eat_count)
			return (0);
		i++;
	}
	return (1);
}