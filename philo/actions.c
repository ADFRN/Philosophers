/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:08:29 by afournie          #+#    #+#             */
/*   Updated: 2026/03/04 11:17:55 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	eat(t_philo *philo)
{
	take_fork(philo);
	secure_print(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_current_time();
	philo->nb_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_u_sleep(philo->settings->time_to_eat, philo->settings);
	release_fork(philo);
}

void	sleepy(t_philo *philo)
{
	secure_print(philo, "is sleeping");
	ft_u_sleep(philo->settings->time_to_eat, philo->settings);
}

void	think(t_philo *philo)
{
	secure_print(philo, "is thinking");
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
