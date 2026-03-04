/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:09:09 by afournie          #+#    #+#             */
/*   Updated: 2026/03/04 10:31:08 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	free_settings(t_settings *settings)
{
	pthread_mutex_destroy(&settings->print_mutex);
	pthread_mutex_destroy(&settings->philo_died_mutex);
	pthread_mutex_destroy(&settings->philo_eat_all_mutex);
	pthread_mutex_destroy(&settings->nb_philo_eaten_all_mutex);
	free(settings);
}

void	free_forks(t_fork *forks, t_settings *settings)
{
	int	i;

	i = -1;
	while (++i < settings->nb_philo)
		pthread_mutex_destroy(&forks[i].mutex);
	free(forks);
}

void	free_philos(t_philo *philo, t_settings *settings)
{
	int	i;

	i = -1;
	while (++i < settings->nb_philo)
		pthread_mutex_destroy(&philo[i].meal_mutex);
	free(philo);
}

void	free_all(t_settings *settings, t_philo *philo, t_fork *forks)
{
	int	i;

	i = -1;
	if (philo)
		while (++i < settings->nb_philo)
			pthread_join(philo[i].thread, NULL);
	if (philo)
		free_philos(philo, settings);
	if (forks)
		free_forks(forks, settings);
	if (settings)
		free_settings(settings);
}
