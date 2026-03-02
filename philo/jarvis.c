/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jarvis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:47:26 by afournie          #+#    #+#             */
/*   Updated: 2026/03/02 17:28:24 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

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

static void	check_total_meal(t_philo *p, t_settings *settings)
{
	pthread_mutex_lock(&settings->nb_philo_eaten_all_mutex);
	if (settings->nb_philo_eaten_all == settings->nb_philo)
	{
		pthread_mutex_lock(&settings->philo_eat_all_mutex);
		settings->philo_eat_all = true;
		pthread_mutex_unlock(&settings->philo_eat_all_mutex);
	}
	pthread_mutex_unlock(&p->settings->nb_philo_eaten_all_mutex);
}

static void	check_death(t_philo *p, t_settings *p_set, long timestamp)
{
	pthread_mutex_lock(&p->meal_mutex);
	if (timestamp - p->last_meal >= p_set->time_to_die)
	{
		secure_print(p, "died");
		pthread_mutex_lock(&p_set->philo_died_mutex);
		p_set->philo_died = p->id;
		pthread_mutex_unlock(&p_set->philo_died_mutex);
	}
	pthread_mutex_unlock(&p->meal_mutex);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!is_simulation_over(p->settings))
	{
		eat(p);
		sleepy(p);
		think(p);
	}
	return (NULL);
}

static bool	exit_philo_routine(t_philo *p, int nb_philo)
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

void	jarvis(t_settings *settings, t_philo *philo)
{
	int		i;
	size_t	time;

	while (!is_simulation_over(settings))
	{
		i = 0;
		while ((i < settings->nb_philo) && !is_simulation_over(settings))
		{
			time = get_current_time();
			check_death(&philo[i], settings, time);
		}
	}
}
