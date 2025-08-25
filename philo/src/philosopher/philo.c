/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raktas <raktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:59:29 by raktas            #+#    #+#             */
/*   Updated: 2025/08/25 19:00:46 by raktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	select_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	print_status(philo, "has taken a fork");
	if (handle_single_philo(philo, first_fork))
		return ;
	do_eat(philo, first_fork, second_fork);
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
		usleep(200);
	while (!dead_flag_control(philo->data))
	{
		philo_eat(philo);
		if (dead_flag_control(philo->data))
			break ;
		philo_sleep(philo);
		philo_think(philo);
		if (philo->data->must_eat_count != -1
			&& philo->eat_count >= philo->data->must_eat_count)
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
		if (!philo_ate_enough(&philos[i], data->must_eat_count))
			return (0);
		i++;
	}
	return (1);
}
