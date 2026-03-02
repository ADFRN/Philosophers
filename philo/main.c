/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 11:58:59 by afournie          #+#    #+#             */
/*   Updated: 2026/03/02 17:17:33 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static void	init_settings(char **argv, t_settings *settings)
{
	settings->nb_philo = ft_atoi(argv[1]);
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]);
	settings->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		settings->nb_eat_by_philo = ft_atoi(argv[5]);
	settings->start_timestamp = get_current_time();
}

int	main(int argc, char **argv)
{
	t_settings	*settings;
	t_philo		*philos;
	t_fork		*forks;

	if (argc < 5)
		return (printf("Argument required"), 1);
	if (argc > 6)
		return (printf("Too many args"), 1);
	settings = malloc(sizeof(t_settings));
	if (!settings)
		return (EXIT_FAILURE);
	init_settings(argv, settings);
	if (!init_philo_forks(settings, &forks) || !init_philo(&philos, forks,
			settings))
		return (EXIT_FAILURE);
	start_routine(philos);
	jarvis(settings, philos);
	return (EXIT_SUCCESS);
}
