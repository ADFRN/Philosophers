/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:08:29 by afournie          #+#    #+#             */
/*   Updated: 2026/03/02 17:35:25 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	eat(t_philo *philo)
{
	take_fork(philo);
	secure_print(philo, "is eating");
	usleep(philo->settings->time_to_eat * 1000);
	release_fork(philo);
}

void	sleepy(t_philo *philo)
{
	secure_print(philo, "is sleeping");
	usleep(philo->settings->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	secure_print(philo, "is sleeping");
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		secure_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mutex);
		secure_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		secure_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		secure_print(philo, "has taken a fork");
	}
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}
