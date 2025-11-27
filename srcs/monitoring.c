/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:03:31 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/27 12:09:25 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static time_t	get_last_meat(t_data *data, int index)
{
	time_t	return_value;

	pthread_mutex_lock(&data->philosophers[index].meat_mutex);
	return_value = data->philosophers[index].last_meat;
	pthread_mutex_unlock(&data->philosophers[index].meat_mutex);
	return (return_value);
}

static void	set_exit(t_data *data)
{
	pthread_mutex_lock(&data->exit_mutex);
	data->exit = 1;
	pthread_mutex_unlock(&data->exit_mutex);
}

static int	check_last_meal(t_data *data, int index)
{
	if ((get_time_in_ms() - data->start_time)
		- get_last_meat(data, index) > data->time_to_die)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("(%ld)[%d] -> %s\n", get_time_in_ms() - data->start_time,
			data->philosophers[index].id, "died");
		pthread_mutex_unlock(&data->print_mutex);
		set_exit(data);
		return (1);
	}
	return (0);
}

static void	increment_max_eat(t_data *data, int index, int *max_eat_reached)
{
	pthread_mutex_lock(&data->philosophers[index].meat_mutex);
	if (data->philosophers[index].total_meat
		>= data->minimum_eat && data->minimum_eat != -2)
		*max_eat_reached += 1;
	pthread_mutex_unlock(&data->philosophers[index].meat_mutex);
}

void	*monitoring(void *d)
{
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
			if (check_last_meal(data, index))
				return (NULL);
			increment_max_eat(data, index, &max_eat_reached);
			index ++;
		}
		if (max_eat_reached >= data->nb_of_philos && data->minimum_eat != -2)
		{
			monitoring_print(data, "All philosophers have enough to eat");
			set_exit(data);
			return (NULL);
		}
		usleep(1);
	}
	return (NULL);
}
