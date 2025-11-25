/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:03:23 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/25 23:13:34 by theo             ###   ########.fr       */
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

static int	setup_each_philo(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_of_philos)
	{
		data->philosophers[index].data = data;
		data->philosophers[index].id = index + 1;
		data->philosophers[index].last_meat = 0;
		pthread_mutex_init(&data->forks[index], NULL);
		index ++;
	}
	return (1);
}

void	launch_threads(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_of_philos)
	{
		data->philosophers[index].last_meat = get_time_in_ms() - data->start_time;
		pthread_create(&data->threads[index], NULL, routine,
			&data->philosophers[index]);
		index ++;
	}
	index = 0;
	pthread_create(&data->monitor, NULL, monitoring, data);
	pthread_join(data->monitor, NULL);
	while (index < data->nb_of_philos)
		pthread_join(data->threads[index ++], NULL);
}

int	init_philosophers(char *argv[], int argc, t_data *data)
{
	data->exit = 0;
	data->start_time = get_time_in_ms();
	if (!parse_args(argv, argc, data))
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philos);
	if (!data->forks)
		return (0);
	data->threads = malloc(sizeof(pthread_t) * data->nb_of_philos);
	if (!data->threads)
		return (free(data->forks), 0);
	data->philosophers = malloc(sizeof(t_philosopher) * data->nb_of_philos);
	if (!data->philosophers)
		return (free(data->forks), free(data->threads), 0);
	if (!setup_each_philo(data))
		return (free(data->forks), free(data->threads),
			free(data->philosophers), 0);
	return (1);
}
