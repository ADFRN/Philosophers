/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jarvis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:47:26 by afournie          #+#    #+#             */
/*   Updated: 2026/03/06 17:31:09 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	check_total_meal(t_philo *p, t_settings *settings)
{
	pthread_mutex_lock(&settings->nb_philo_eaten_all_mutex);
	if (settings->nb_max_eat == p->nb_eaten)
	{
		pthread_mutex_lock(&settings->philo_eat_all_mutex);
		settings->philo_eat_all = true;
		pthread_mutex_unlock(&settings->philo_eat_all_mutex);
	}
	pthread_mutex_unlock(&p->settings->nb_philo_eaten_all_mutex);
}

void	check_death(t_philo *p, t_settings *p_set, long timestamp)
{
	pthread_mutex_lock(&p->meal_mutex);
	if (timestamp - p->last_meal >= p_set->time_to_die)
	{
		printf("%d tmp: %ld\n",p->id, (timestamp - p->last_meal));
		secure_print(p, "died");
		pthread_mutex_lock(&p_set->philo_died_mutex);
		p_set->philo_died = p->id;
		pthread_mutex_unlock(&p_set->philo_died_mutex);
	}
	pthread_mutex_unlock(&p->meal_mutex);
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
			i++;
		}
		usleep(500);
	}
}
