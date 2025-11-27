/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:05:10 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/27 14:26:59 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_philosophers(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_of_philos)
	{
		pthread_mutex_destroy(&data->philosophers[index].meat_mutex);
		pthread_mutex_destroy(&data->forks[index ++]);
	}
	pthread_mutex_destroy(&data->exit_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free (data->forks);
	free (data->philosophers);
	free (data->threads);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Usage : ./philo nb_of_philos t_to_die t_to_eat "
			"t_to_sleep max_eat(optional)\n");
		return (1);
	}
	if (!init_philosophers(argv, argc, &data))
		return (1);
	launch_threads(&data);
	clean_philosophers(&data);
	return (0);
}
