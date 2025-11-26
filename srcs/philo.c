/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:08:52 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/26 18:20:26 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	increment_total_meat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meat_mutex);
	philo->total_meat ++;
	pthread_mutex_unlock(&philo->meat_mutex);
}

static void	set_last_meal(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meat_mutex);
	philo->last_meat = get_time_in_ms() - philo->data->start_time;
	pthread_mutex_unlock(&philo->meat_mutex);
}

void	*routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	while (!check_exit(philo))
	{
		locked_print(philo, "is thinking");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		if (check_exit(philo))
		{
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
			return (NULL);
		}
		locked_print(philo, "is eating");
		increment_total_meat(philo);
		set_last_meal(philo);
		smart_sleep(philo, philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		if (check_exit(philo))
			return (NULL);
		locked_print(philo, "is sleeping");
		smart_sleep(philo, philo->data->time_to_sleep);
	}
}
