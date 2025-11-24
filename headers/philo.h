/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:56:51 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/24 18:09:28 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include "stdio.h"
# include "unistd.h"
# include "pthread.h"
# include "limits.h"

typedef struct s_data t_data;

typedef struct s_philosopher
{
	t_data	*data;
	long	last_meat;
	int		id;
}	t_philosopher;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	t_philosopher	*philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_of_philos;
	long			max_eat;
}	t_data;

int	init_philosophers(char *argv[], int argc, t_data *data);
void	clean_philosophers(t_data *data);
void	*routine(void *data);

#endif