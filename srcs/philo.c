/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:08:52 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/27 00:06:35 by theo             ###   ########.fr       */
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

static void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

static void	single_philo(t_philosopher	*philo)
{
	locked_print(philo, "is thinking");
	pthread_mutex_lock(&philo->data->forks[0]);
	smart_sleep(philo, philo->data->time_to_die);
	pthread_mutex_unlock(&philo->data->forks[0]);
}

void	*routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	if (philo->data->nb_of_philos == 1)
		return (single_philo(philo), NULL);
	while (!check_exit(philo))
	{
		locked_print(philo, "is thinking");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		if (check_exit(philo))
			return (release_forks(philo), NULL);
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
	return (NULL);
}
