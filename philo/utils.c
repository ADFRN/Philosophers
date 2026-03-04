/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:04:45 by afournie          #+#    #+#             */
/*   Updated: 2026/03/04 11:42:55 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_atoi(const char *str)
{
	int		nbr;
	int		sign;
	size_t	i;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

bool	is_simulation_over(t_settings *settings)
{
	pthread_mutex_lock(&settings->philo_died_mutex);
	if (settings->philo_died)
	{
		pthread_mutex_unlock(&settings->philo_died_mutex);
		return (true);
	}
	pthread_mutex_unlock(&settings->philo_died_mutex);
	pthread_mutex_lock(&settings->philo_eat_all_mutex);
	if (settings->philo_eat_all)
	{
		pthread_mutex_unlock(&settings->philo_eat_all_mutex);
		return (true);
	}
	pthread_mutex_unlock(&settings->philo_eat_all_mutex);
	return (false);
}

void	secure_print(t_philo *p, const char *status)
{
	size_t	timestamp;

	timestamp = get_current_time();
	pthread_mutex_lock(&p->settings->print_mutex);
	pthread_mutex_lock(&p->settings->philo_died_mutex);
	pthread_mutex_lock(&p->settings->philo_eat_all_mutex);
	if (!p->settings->philo_died && !p->settings->philo_eat_all)
		printf("%ld %d %s\n", timestamp - p->settings->start_timestamp, p->id,
			status);
	pthread_mutex_unlock(&p->settings->philo_eat_all_mutex);
	pthread_mutex_unlock(&p->settings->philo_died_mutex);
	pthread_mutex_unlock(&p->settings->print_mutex);
}

void	ft_u_sleep(size_t timeTo, t_settings *settings)
{
	size_t	sttime;

	sttime = get_current_time();
	while (!is_simulation_over(settings) && ((get_current_time()
				- sttime) < timeTo))
		usleep(500);
}
