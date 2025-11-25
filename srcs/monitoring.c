/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:03:31 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/26 00:16:09 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *d)
{
	int	counter = 0;
	t_data	*data;
	int		index;

	data = (t_data *)d;
	index = 0;
	while (data->exit == 0)
	{
		index = 0;
		while (index < data->nb_of_philos)
		{
			if ((get_time_in_ms() - data->start_time) - data->philosophers[index].last_meat >= data->time_to_die)
			{
				printf("------DIE------\n");
				printf("[%d] -> last_meal : %ld, diff: %ld\n", data->philosophers[index].id, data->philosophers[index].last_meat, (get_time_in_ms() - data->start_time) - data->philosophers[index].last_meat);
				data->exit = 1;
				return (NULL);
			}
			index ++;
		}
		counter ++;
		usleep(1000);
	}

}
