/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:08:52 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/26 00:15:30 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philosopher *philo, char *msg)
{
	printf("(%ld)[%d] -> %s\n", get_time_in_ms() - philo->data->start_time,
			philo->id, msg);
}

int	smart_sleep(time_t ms, t_philosopher *philo)
{
	long	index;

	index = 0;
	while (index < ms)
	{
		if (philo->data->exit == 1)
			return (0);
		usleep(1000);
		index ++;
	}
	return (1);
}

void	*routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	while (philo->data->exit == 0)
	{
		philo_print(philo, "is thinking");
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->nb_of_philos]);
			pthread_mutex_lock(&philo->data->forks[(philo->id - 1) % philo->data->nb_of_philos]);
			philo_print(philo, "is eating");
			philo->last_meat = get_time_in_ms() - philo->data->start_time;
			if (!smart_sleep(ms_to_microseconds(philo->data->time_to_eat), philo))
				return (NULL);
			pthread_mutex_unlock(&philo->data->forks[(philo->id - 1) % philo->data->nb_of_philos]);
			pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nb_of_philos]);
		}
		else
		{
			pthread_mutex_lock(&philo->data->forks[(philo->id - 1) % philo->data->nb_of_philos]);
			pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->nb_of_philos]);

			philo_print(philo, "is eating");
			philo->last_meat = get_time_in_ms() - philo->data->start_time;
			if (!smart_sleep(ms_to_microseconds(philo->data->time_to_eat), philo))
				return (NULL);

			pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nb_of_philos]);
			pthread_mutex_unlock(&philo->data->forks[(philo->id - 1) % philo->data->nb_of_philos]);
		}
		philo_print(philo, "is sleeping");
		if (!smart_sleep(ms_to_microseconds(philo->data->time_to_sleep), philo))
			return (NULL);
	}
}
