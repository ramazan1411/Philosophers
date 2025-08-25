/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raktas <raktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:59:42 by raktas            #+#    #+#             */
/*   Updated: 2025/08/25 17:43:46 by raktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	cleanup_mutexes(&data, philos);
	free(philos);
	return (0);
}
