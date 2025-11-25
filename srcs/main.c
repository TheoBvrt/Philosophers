/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:05:10 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/25 23:23:12 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		ft_printf("Usage : ./philo nb_of_philos t_to_die t_to_eat "
			"t_to_sleep max_eat(optional)\n");
		return (1);
	}
	if (!init_philosophers(argv, argc, &data))
		return (1);
	launch_threads(&data);
	clean_philosophers(&data);
	return (0);
}
