/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:17:39 by afournie          #+#    #+#             */
/*   Updated: 2026/02/10 10:21:31 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	destroy_mutex(t_philo **philo, int i_philo, t_fork **forks, int i_fork)
{
	if (*philo)
	{
		while (--i_philo >= 0)
			pthread_mutex_destroy(&(*philo)[i_philo].meal_mutex);
		free(*philo);
	}
	if (*forks)
	{
		while (--i_fork >= 0)
			pthread_mutex_destroy(&(*forks)[i_fork].mutex);
		free(*forks);
	}
}

void	destroy_exit(int exit_code, int nb_mutex, ...)
{
	pthread_mutex_t	*current_mutex;
	va_list			all_mutex;
	int				i;

	va_start(all_mutex, nb_mutex);
	i = -1;
	while (++i < nb_mutex)
	{
		current_mutex = va_arg(all_mutex, pthread_mutex_t *);
		pthread_mutex_destroy(current_mutex);
	}
	va_end(all_mutex);
	exit(exit_code);
}
