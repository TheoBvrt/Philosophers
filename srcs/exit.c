/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:43:54 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/26 15:54:34 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_philosophers(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_of_philos)
		pthread_mutex_destroy(&data->forks[index ++]);
	pthread_mutex_destroy(&data->exit_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meat_mutex);
	free (data->forks);
	free (data->philosophers);
	free (data->threads);
}
