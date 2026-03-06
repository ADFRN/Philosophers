/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:08:29 by afournie          #+#    #+#             */
/*   Updated: 2026/03/06 18:05:49 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	eat(t_philo *philo)
{
	long time;

	take_fork(philo);
	time = get_current_time();
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = time;
	philo->nb_eaten++;
	secure_print(philo, "is eating");
	if (philo->settings->need_to_check_meal
		&& philo->nb_eaten == philo->settings->nb_max_eat)
	{
		pthread_mutex_lock(&philo->settings->nb_philo_eaten_all_mutex);
		philo->settings->nb_philo_eaten_all++;
		if (philo->settings->nb_philo_eaten_all == philo->settings->nb_philo)
		{
			pthread_mutex_lock(&philo->settings->philo_eat_all_mutex);
			philo->settings->philo_eat_all = true;
			pthread_mutex_unlock(&philo->settings->philo_eat_all_mutex);
		}
		pthread_mutex_unlock(&philo->settings->nb_philo_eaten_all_mutex);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_u_sleep(philo->settings->time_to_eat, philo->settings);
	release_fork(philo);
}

void	sleepy(t_philo *philo)
{
	secure_print(philo, "is sleeping");
	ft_u_sleep(philo->settings->time_to_sleep, philo->settings);
}

void	think(t_philo *philo)
{
	secure_print(philo, "is thinking");
	if (philo->settings->nb_philo % 2)
		ft_u_sleep(philo->settings->time_to_sleep, philo->settings);
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
