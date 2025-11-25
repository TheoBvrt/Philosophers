/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:08:52 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/25 15:04:52 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	while (philo->data->exit == 0)
	{
		printf("(%ld)[%d] -> ping\n", get_time_in_ms() - philo->data->start_time, philo->id);
		usleep(50000);
	}
}
