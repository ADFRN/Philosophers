/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:13:26 by afournie          #+#    #+#             */
/*   Updated: 2026/02/10 10:14:39 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_settings
{
	long			start_timestamp;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat_by_philo;
	int				nb_philo_eaten_all;
	int				philo_died;
	bool			philo_eat_all;
	bool			start_routine;

	pthread_mutex_t	nb_philo_eaten_all_mutex;
	pthread_mutex_t	philo_died_mutex;
	pthread_mutex_t	philo_eat_all_mutex;
	pthread_mutex_t	print_mutex;
}					t_settings;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				nb_eaten;
	long			last_meal;
	pthread_mutex_t	meal_mutex;
	t_settings		*settings;
	t_fork			*left_fork;
	t_fork			*right_fork;
}					t_philo;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}					t_fork;

int					ft_atoi(const char *str);
long				current_time_ms(void);

#endif
