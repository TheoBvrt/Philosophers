/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:08:52 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/25 16:13:10 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philosopher *philo, char *msg)
{
	printf("(%ld)[%d] -> %s\n", get_time_in_ms() - philo->data->start_time,
			philo->id, msg);
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
			pthread_mutex_lock(&philo->data->forks[philo->id]);
			philo_print(philo, "take right fork");
			pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
			philo_print(philo, "take left fork");
			philo_print(philo, "is eating");

			pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
			philo_print(philo, "release left fork");
			pthread_mutex_unlock(&philo->data->forks[philo->id]);
			philo_print(philo, "release right fork");
		}
		else
		{
			pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
			philo_print(philo, "take left fork");
			pthread_mutex_lock(&philo->data->forks[philo->id]);
			philo_print(philo, "take right fork");
			philo_print(philo, "is eating");

			pthread_mutex_unlock(&philo->data->forks[philo->id]);
			philo_print(philo, "release right fork");
			pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
			philo_print(philo, "release left fork");
		}
		philo_print(philo, "is sleeping");
		usleep(ms_to_microseconds(philo->data->time_to_sleep));
	}
}
