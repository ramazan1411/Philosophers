#include "../philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (0);
	return (1);
}

void	init_philosophers(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].last_meal_time = data->start_time;
		philos[i].data = data;
		philos[i].left_fork = &data->forks[i];
		if (i == data->philo_count - 1)
			philos[i].right_fork = &data->forks[0];
		else
			philos[i].right_fork = &data->forks[i + 1];
		i++;
	}
}

int	init_data(t_data *data)
{
	data->start_time = get_time();
	data->death_flag = 0;
	if (!init_mutexes(data))
		return (0);
	return (1);
}

void	cleanup_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
}

t_philo	*allocate_philos(t_data *data)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!philos)
		return (NULL);
	return (philos);
}