/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:56:51 by thbouver          #+#    #+#             */
/*   Updated: 2025/11/26 18:18:48 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include "stdio.h"
# include "unistd.h"
# include "pthread.h"
# include "limits.h"
# include <sys/time.h>

typedef struct s_data t_data;
typedef struct s_philosopher t_philosopher;

typedef struct s_philosopher
{
	t_data	*data;
	time_t	last_meat;
	pthread_mutex_t	meat_mutex;
	int		right_fork;
	int		left_fork;
	int		total_meat;
	int		id;
}	t_philosopher;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t exit_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		*threads;
	pthread_t		monitor;
	t_philosopher	*philosophers;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			nb_of_philos;
	time_t			max_eat;
	int				start;
	int				exit;
}	t_data;

int	init_philosophers(char *argv[], int argc, t_data *data);
void	launch_threads(t_data *data);
void	clean_philosophers(t_data *data);
void	*routine(void *d);
void	*monitoring(void *d);
void	locked_print(t_philosopher *philo, char *msg);
void	monitoring_print(t_data *data, char *msg);
void	smart_sleep(t_philosopher *philo, time_t ms);
int		check_exit(t_philosopher *philo);
time_t	get_time_in_ms(void);
time_t	ms_to_microseconds(time_t ms);

#endif