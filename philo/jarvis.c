/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jarvis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:47:26 by afournie          #+#    #+#             */
/*   Updated: 2026/02/10 10:22:21 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	mutex_init(t_settings *settings, t_philo *philos)
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

void	routine(t_settings *settings, t_philo *philos)
{
}

void	jarvis(void)
{
	// check who can eat
	// check who starving
	// let philo eat
}
