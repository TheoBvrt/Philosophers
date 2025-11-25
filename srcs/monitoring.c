/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:03:31 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/25 14:03:40 by thbouver         ###   ########.fr       */
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
			index ++;
		}
		if (counter == 3)
			data->exit = 1;
		counter ++;
		sleep(2);
	}
	printf("END\n");
}
