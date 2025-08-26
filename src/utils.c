/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raktas <raktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:59:33 by raktas            #+#    #+#             */
/*   Updated: 2025/08/26 11:33:40 by raktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int time)
{
	long	start;
	long	current;

	start = get_time();
	while (1)
	{
		current = get_time();
		if (current - start >= time)
			break ;
		usleep(100);
	}
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->death_flag)
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	check_death(t_philo *philo)
{
	long	current_time;
	long	last_meal;
	int		time_to_die;

	current_time = get_time();
	time_to_die = philo->data->time_to_die;
	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (current_time - last_meal > time_to_die)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->death_flag = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	return (0);
}

int	dead_flag_control(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_mutex);
	result = data->death_flag;
	pthread_mutex_unlock(&data->death_mutex);
	return (result);
}
