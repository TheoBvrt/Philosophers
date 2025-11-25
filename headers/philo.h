/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:56:51 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/25 13:35:00 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include "stdio.h"
# include "unistd.h"
# include "pthread.h"
# include "limits.h"
 #include <sys/time.h>

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
	pthread_t		monitor;
	t_philosopher	*philosophers;
	int				exit;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_of_philos;
	long			max_eat;
}	t_data;

int	init_philosophers(char *argv[], int argc, t_data *data);
void	clean_philosophers(t_data *data);
void	*routine(void *d);
void	*monitoring(void *d);

#endif