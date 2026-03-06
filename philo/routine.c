/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:37:23 by afournie          #+#    #+#             */
/*   Updated: 2026/03/06 18:17:58 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->settings->nb_philo % 2)
		ft_u_sleep(p->settings->time_to_eat - p->settings->time_to_eat / 10,
			p->settings);
	while (!is_simulation_over(p->settings))
	{
		eat(p);
		sleepy(p);
		think(p);
	}
	return (NULL);
}

bool	exit_philo_routine(t_philo *p, int nb_philo)
{
	pthread_mutex_lock(&p->settings->philo_died_mutex);
	p->settings->philo_died = true;
	pthread_mutex_unlock(&p->settings->philo_died_mutex);
	while (--nb_philo >= 0)
		pthread_join(p[nb_philo].thread, NULL);
	return (false);
}

bool	start_routine(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->settings->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]))
			return (exit_philo_routine(philo, i));
	}
	return (true);
}
