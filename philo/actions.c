/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:08:29 by afournie          #+#    #+#             */
/*   Updated: 2026/02/04 17:38:59 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	eat(t_settings *settings)
{
	take_fork(settings);
	printf("timestamp - nb philo - is eating");
	usleep(settings->time_to_eat);
	release_fork(settings);
}

void	sleep(t_settings *settings)
{
	printf("timestamp - nb philo - is sleeping");
	usleep(settings->time_to_sleep);
}

void	think(t_settings *settings)
{
	printf("timestamp - nb philo - is thinking");
}

void	take_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	printf("timestamp - nb philo - has taken fork");
	pthread_mutex_unlock(&fork->mutex);
}

void	release_fork(t_fork *fork)
{
	printf("timestamp - nb philo - has released fork");
}
