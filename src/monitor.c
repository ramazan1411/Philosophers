/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raktas <raktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:59:21 by raktas            #+#    #+#             */
/*   Updated: 2025/08/26 11:48:56 by raktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	announce_death(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_time() - philo->data->start_time;
	printf("%ld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	check_all_deaths(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (check_death(&philos[i]))
		{
			announce_death(&philos[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	monitor_philos(t_data *data, t_philo *philos)
{
	while (!dead_flag_control(data))
	{
		if (check_all_deaths(data, philos))
			break ;
		if (all_ate_enough(data, philos))
		{
			pthread_mutex_lock(&data->death_mutex);
			data->death_flag = 1;
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		usleep(1000);
	}
}

int	create_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philosopher_routine, &philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	join_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (1);
}
