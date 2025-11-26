/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:03:31 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/26 16:13:31 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_last_meat(t_data *data, int index)
{
	time_t	return_value;

	pthread_mutex_lock(&data->philosophers[index].meat_mutex);
	return_value = data->philosophers[index].last_meat;
	pthread_mutex_unlock(&data->philosophers[index].meat_mutex);
	return(return_value);
}

void	*monitoring(void *d)
{
	int	counter = 0;
	t_data	*data;
	int		index;
	int		max_eat_reached;

	data = (t_data *)d;
	while (data->exit == 0)
	{
		index = 0;
		max_eat_reached = 0;
		while (index < data->nb_of_philos)
		{
			if ((get_time_in_ms() - data->start_time) - get_last_meat(data, index) > data->time_to_die)
			{
				pthread_mutex_lock(&data->print_mutex);
				printf("(%ld)[%d] -> %s\n", get_time_in_ms() - data->start_time,
					data->philosophers[index].id, "died");
				pthread_mutex_unlock(&data->print_mutex);
				pthread_mutex_lock(&data->exit_mutex);
				data->exit = 1;
				pthread_mutex_unlock(&data->exit_mutex);
				return (NULL);
			}
			pthread_mutex_lock(&data->philosophers[index].meat_mutex);
			if (data->philosophers[index].total_meat == data->max_eat)
				max_eat_reached ++;
			pthread_mutex_unlock(&data->philosophers[index].meat_mutex);
			index ++;
		}
		if (max_eat_reached == data->nb_of_philos)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("total max eat reached %d\n", max_eat_reached);
			pthread_mutex_unlock(&data->print_mutex);
			
			pthread_mutex_lock(&data->exit_mutex);
			data->exit = 1;
			pthread_mutex_unlock(&data->exit_mutex);
			return (NULL);
		}
		counter ++;
		usleep(1);
	}

}
