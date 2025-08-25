/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raktas <raktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:59:50 by raktas            #+#    #+#             */
/*   Updated: 2025/08/25 17:51:10 by raktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				death_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
}	t_philo;

int		ft_atoi(const char *str);
int		is_valid_number(const char *str);
int		validate_args(int argc, char **argv);
int		parse_args(char **argv, t_data *data);
long	get_time(void);
void	ft_usleep(int time);
void	print_status(t_philo *philo, char *status);
int		check_death(t_philo *philo);
int		dead_flag_control(t_data *data);
int		init_mutexes(t_data *data);
void	init_philosophers(t_data *data, t_philo *philos);
int		init_data(t_data *data);
void	cleanup_mutexes(t_data *data, t_philo *philos);
t_philo	*allocate_philos(t_data *data);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	*philosopher_routine(void *arg);
int		all_ate_enough(t_data *data, t_philo *philos);
void	announce_death(t_philo *philo);
int		check_all_deaths(t_data *data, t_philo *philos);
void	monitor_philos(t_data *data, t_philo *philos);
int		create_threads(t_data *data, t_philo *philos);
int		join_threads(t_data *data, t_philo *philos);
void	select_forks(t_philo *philo,
			pthread_mutex_t **first,
			pthread_mutex_t **second);
int		handle_single_philo(t_philo *philo, pthread_mutex_t *first_fork);
void	update_meal(t_philo *philo);
void	do_eat(t_philo *philo,
			pthread_mutex_t *first_fork,
			pthread_mutex_t *second_fork);
int		philo_ate_enough(t_philo *p, int must);

#endif