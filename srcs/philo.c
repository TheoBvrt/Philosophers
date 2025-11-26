/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:08:52 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/26 17:03:43 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philosopher *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("(%ld)[%d] -> %s\n", get_time_in_ms() - philo->data->start_time,
			philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	check_exit(t_philosopher *philo)
{
	int	return_value;

	return_value = 0;
	pthread_mutex_lock(&philo->data->exit_mutex);
	if (philo->data->exit == 1)
		return_value = 1;
	pthread_mutex_unlock(&philo->data->exit_mutex);
	return(return_value);
}

void	smart_sleep(t_philosopher *philo, time_t ms)
{
	time_t	start;

	start = get_time_in_ms();
	while (!check_exit(philo))
	{
		if (get_time_in_ms() - start >= ms)
			break ;
		usleep(100);
	}
}

void	*routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	while (!check_exit(philo))
	{
		philo_print(philo, "is thinking");
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->nb_of_philos]);
			pthread_mutex_lock(&philo->data->forks[(philo->id - 1) % philo->data->nb_of_philos]);
			if (check_exit(philo))
			{
				pthread_mutex_unlock(&philo->data->forks[(philo->id - 1) % philo->data->nb_of_philos]);
				pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nb_of_philos]);
				return (NULL);
			}
			philo_print(philo, "is eating");
			
			pthread_mutex_lock(&philo->meat_mutex);
			philo->total_meat ++;
			pthread_mutex_unlock(&philo->meat_mutex);

			if (philo->total_meat == philo->data->max_eat)
				philo_print(philo, "max eat");
			
			pthread_mutex_lock(&philo->meat_mutex);
			philo->last_meat = get_time_in_ms() - philo->data->start_time;
			pthread_mutex_unlock(&philo->meat_mutex);
			
			smart_sleep(philo, philo->data->time_to_eat);

			pthread_mutex_unlock(&philo->data->forks[(philo->id - 1) % philo->data->nb_of_philos]);
			pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nb_of_philos]);
		}
		else
		{
			pthread_mutex_lock(&philo->data->forks[(philo->id - 1) % philo->data->nb_of_philos]);
			pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->nb_of_philos]);
			if (check_exit(philo))
			{
				pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nb_of_philos]);
				pthread_mutex_unlock(&philo->data->forks[(philo->id - 1) % philo->data->nb_of_philos]);
				return (NULL);
			}
			philo_print(philo, "is eating");

			pthread_mutex_lock(&philo->meat_mutex);
			philo->total_meat ++;
			pthread_mutex_unlock(&philo->meat_mutex);

			if (philo->total_meat == philo->data->max_eat)
				philo_print(philo, "max eat");

			pthread_mutex_lock(&philo->meat_mutex);
			philo->last_meat = get_time_in_ms() - philo->data->start_time;
			pthread_mutex_unlock(&philo->meat_mutex);
			
			smart_sleep(philo, philo->data->time_to_eat);
	
			pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nb_of_philos]);
			pthread_mutex_unlock(&philo->data->forks[(philo->id - 1) % philo->data->nb_of_philos]);
		}
		if (check_exit(philo))
			return (NULL);
		philo_print(philo, "is sleeping");
		smart_sleep(philo, philo->data->time_to_sleep);
	}
}

