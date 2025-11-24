/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:03:23 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/24 17:36:14 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	parse_number(char *str)
{
	int		index;
	
	index = 0;
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (-1);
		index ++;
	}
	return (ft_atoi(str));
}

static int	parse_args(char *argv[], int argc, t_data *data)
{
	data->time_to_die = parse_number(argv[2]);
	data->time_to_eat = parse_number(argv[3]);
	data->time_to_sleep = parse_number(argv[4]);
	data->nb_of_philos = parse_number(argv[1]);
	data->max_eat = -2;
	if (argc == 6)
		data->max_eat = parse_number(argv[5]);
	if (data->time_to_die == -1
			|| data->time_to_eat == -1
			|| data->time_to_die == -1
			|| data->nb_of_philos == -1
			|| data->max_eat == -1)
	{
		ft_printf("Erreur d'arguments\n");
		return (0);
	}
	return (1);
}

int	init_philosophers(char *argv[], int argc, t_data *data)
{
	if (!parse_args(argc, argc, data))
		return (0);
	return (1);
}
