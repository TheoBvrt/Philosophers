/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:43:54 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/24 17:46:19 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_philosophers(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_of_philos)
		pthread_mutex_destroy(&data->forks[index ++]);
	free (data->forks);
	free (data->philosophers);
	free (data->threads);
}
