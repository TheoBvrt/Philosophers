/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:22:20 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/27 13:45:32 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	locked_print(t_philosopher *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->exit_mutex);
	if (philo->data->exit)
	{
		pthread_mutex_unlock(&philo->data->exit_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->exit_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("(%ld)[%d] -> %s\n", get_time_in_ms() - philo->data->start_time,
		philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	monitoring_print(t_data *data, char *msg)
{
	usleep(2000);
	pthread_mutex_lock(&data->print_mutex);
	printf("%s\n", msg);
	pthread_mutex_unlock(&data->print_mutex);
}

int	check_exit(t_philosopher *philo)
{
	int	return_value;

	return_value = 0;
	pthread_mutex_lock(&philo->data->exit_mutex);
	if (philo->data->exit == 1)
		return_value = 1;
	pthread_mutex_unlock(&philo->data->exit_mutex);
	return (return_value);
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
