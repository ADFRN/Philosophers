/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:23:48 by afournie          #+#    #+#             */
/*   Updated: 2026/02/10 10:31:35 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

bool	init_philo(t_philo **philo, t_fork *fork, t_settings *settings)
{
	int	i;
	int	n;

	n = settings->nb_philo;
	*philo = malloc(sizeof(t_philo) * n);
	if (!*philo)
		return (false);
	i = -1;
	while (++i < n)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].thread = 0;
		(*philo)[i].nb_eaten = 0;
		(*philo)[i].last_meal = current_time_ms();
		if (pthread_mutex_init(&(*philo)[i].meal_mutex, NULL) != 0)
			return (destroy_mutex(philo, i, NULL, 0), false);
		(*philo)[i].right_fork = &fork[i];
		(*philo)[i].settings = settings;
	}
	i = -1;
	while (++i < n)
		(*philo)[i].left_fork = &fork[(i + n - 1) % n];
	return (true);
}
