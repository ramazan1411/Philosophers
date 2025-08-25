/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raktas <raktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:33:15 by raktas            #+#    #+#             */
/*   Updated: 2025/08/25 17:14:53 by raktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	select_forks(t_philo *philo,
						pthread_mutex_t **first,
						pthread_mutex_t **second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

int	handle_single_philo(t_philo *philo, pthread_mutex_t *first_fork)
{
	if (philo->data->philo_count != 1)
		return (0);
	ft_usleep(philo->data->time_to_die + 1);
	pthread_mutex_unlock(first_fork);
	return (1);
}

void	update_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	do_eat(t_philo *philo,
					pthread_mutex_t *first_fork,
					pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(second_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	update_meal(philo);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

int	philo_ate_enough(t_philo *philo, int must)
{
	int	ate_enough;

	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->eat_count >= must)
		ate_enough = 1;
	else
		ate_enough = 0;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (ate_enough);
}
