/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:13:26 by afournie          #+#    #+#             */
/*   Updated: 2026/03/04 13:34:43 by afournie         ###   ########.fr       */
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
	int				nb_philo;
	int				nb_max_eat;
	int				philo_died;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	bool			philo_eat_all;
	bool			start_routine;
	size_t			start_timestamp;
	int				need_to_check_meal;
	int				nb_philo_eaten_all;

	pthread_mutex_t	nb_philo_eaten_all_mutex;
	pthread_mutex_t	philo_eat_all_mutex;
	pthread_mutex_t	philo_died_mutex;
	pthread_mutex_t	print_mutex;

}					t_settings;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				nb_eaten;
	long			last_meal;
	t_settings		*settings;
	t_fork			*left_fork;
	t_fork			*right_fork;

	pthread_mutex_t	meal_mutex;
}					t_philo;

int					check_args(int ac);
void				eat(t_philo *philo);
void				think(t_philo *philo);
void				sleepy(t_philo *philo);
size_t				get_current_time(void);
int					ft_atoi(const char *str);
void				*philo_routine(void *arg);
void				take_fork(t_philo *philo);
void				release_fork(t_philo *philo);
bool				start_routine(t_philo *philo);
void				mutex_init(t_settings *settings);
void				*philo_routine_for_three(void *arg);
void				free_settings(t_settings *settings);
bool				is_simulation_over(t_settings *settings);
void				jarvis(t_settings *settings, t_philo *philo);
void				secure_print(t_philo *p, const char *status);
bool				exit_philo_routine(t_philo *p, int nb_philo);
void				destroy_exit(int exit_code, int nb_mutex, ...);
void				ft_u_sleep(size_t timeTo, t_settings *settings);
void				free_forks(t_fork *forks, t_settings *settings);
void				init_settings(char **argv, t_settings *settings);
void				free_philos(t_philo *philo, t_settings *settings);
void				check_total_meal(t_philo *p, t_settings *settings);
bool				init_philo_forks(t_settings *settings, t_fork **forks);
void				check_death(t_philo *p, t_settings *p_set, long timestamp);

bool				init_philo(t_philo **philo, t_fork *fork,
						t_settings *settings);
void				destroy_mutex(t_philo **philo, int i_philo, t_fork **forks,
						int i_fork);
void				free_all(t_settings *settings, t_philo *philo,
						t_fork *forks);

#endif
