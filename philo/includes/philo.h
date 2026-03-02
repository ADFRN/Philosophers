/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:13:26 by afournie          #+#    #+#             */
/*   Updated: 2026/03/02 17:17:23 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_settings
{
	size_t			start_timestamp;
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

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				nb_eaten;
	long			last_meal;
	pthread_t		thread;
	t_settings		*settings;
	t_fork			*left_fork;
	t_fork			*right_fork;

	pthread_mutex_t	meal_mutex;
}					t_philo;

int					ft_atoi(const char *str);
size_t				get_current_time(void);
bool				is_simulation_over(t_settings *settings);
bool				init_philo(t_philo **philo, t_fork *fork,
						t_settings *settings);
bool				init_philo_forks(t_settings *settings, t_fork **forks);
void				jarvis(t_settings *settings, t_philo *philo);
void				take_fork(t_philo *philo);
void				eat(t_philo *philo);
void				sleepy(t_philo *philo);
void				think(t_philo *philo);
void				release_fork(t_philo *philo);
void				secure_print(t_philo *p, const char *status);
bool				start_routine(t_philo *philo);
void				destroy_exit(int exit_code, int nb_mutex, ...);
void				destroy_mutex(t_philo **philo, int i_philo, t_fork **forks,
						int i_fork);

#endif
