#include "philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		printf("Usage: ./philo nb_philo time_die time_eat time_sleep [must_eat]\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]) || ft_atoi(argv[i]) <= 0)
		{
			printf("Error: Invalid argument: %s\n", argv[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_args(char **argv, t_data *data)
{
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (!validate_args(argc, argv))
		return (1);
	if (!parse_args(argv, &data))
		return (1);
	if (!init_data(&data))
		return (1);
	philos = allocate_philos(&data);
	if (!philos)
		return (1);
	init_philosophers(&data, philos);
	if (!create_threads(&data, philos))
		return (1);
	monitor_philos(&data, philos);
	join_threads(&data, philos);
	cleanup_mutexes(&data);
	free(philos);
	return (0);
}