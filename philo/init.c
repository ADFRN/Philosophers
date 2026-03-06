/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:23:40 by afournie          #+#    #+#             */
/*   Updated: 2026/03/06 10:54:55 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	init_settings(char **argv, t_settings *settings)
{
	settings->nb_philo = ft_atoi(argv[1]);
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]);
	settings->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		settings->nb_max_eat = ft_atoi(argv[5]);
		settings->need_to_check_meal = 1;
	}
	else
	{
		settings->nb_max_eat = 0;
		settings->need_to_check_meal = 0;
	}
	settings->nb_philo_eaten_all = 0;
	settings->philo_died = 0;
	settings->philo_eat_all = 0;
	settings->start_routine = 0;
	settings->start_timestamp = 0;
}

bool	init_philo_forks(t_settings *settings, t_fork **forks)
{
	int	i;

	*forks = malloc(sizeof(t_fork) * settings->nb_philo);
	if (!*forks)
		return (false);
	i = -1;
	while (++i < settings->nb_philo)
	{
		if (pthread_mutex_init(&(*forks)[i].mutex, NULL) != 0)
			return (destroy_mutex(NULL, 0, forks, i), false);
	}
	return (true);
}

bool	init_philo(t_philo **philo, t_fork *fork, t_settings *settings)
{
	int	i;
	int	n;

	n = settings->nb_philo;
	settings->start_timestamp = get_current_time();
	*philo = malloc(sizeof(t_philo) * n);
	if (!*philo)
		return (false);
	i = -1;
	while (++i < n)
	{
		(*philo)[i].settings = settings;
		(*philo)[i].id = i + 1;
		(*philo)[i].thread = 0;
		(*philo)[i].nb_eaten = 0;
		(*philo)[i].last_meal = settings->start_timestamp;
		if (pthread_mutex_init(&(*philo)[i].meal_mutex, NULL) != 0)
			return (destroy_mutex(philo, i, NULL, 0), false);
		(*philo)[i].right_fork = &fork[i];
	}
	i = -1;
	while (++i < n)
		(*philo)[i].left_fork = &fork[(i + n - 1) % n];
	return (true);
}

void	mutex_init(t_settings *settings)
{
	if (pthread_mutex_init(&settings->nb_philo_eaten_all_mutex, NULL) != 0)
		exit(EXIT_FAILURE);
	if (pthread_mutex_init(&settings->philo_died_mutex, NULL) != 0)
		destroy_exit(EXIT_FAILURE, 1, settings->nb_philo_eaten_all_mutex);
	if (pthread_mutex_init(&settings->philo_eat_all_mutex, NULL) != 0)
		destroy_exit(EXIT_FAILURE, 1, settings->nb_philo_eaten_all_mutex,
			settings->philo_died_mutex);
	if (pthread_mutex_init(&settings->print_mutex, NULL) != 0)
		destroy_exit(EXIT_FAILURE, 1, settings->nb_philo_eaten_all_mutex,
			settings->philo_died_mutex, settings->philo_eat_all_mutex);
}
