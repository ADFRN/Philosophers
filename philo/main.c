/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 11:58:59 by afournie          #+#    #+#             */
/*   Updated: 2026/02/10 12:09:49 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static t_settings	init_settings(char **argv, t_settings *settings)
{
	settings->nb_philo = ft_atoi(argv[1]);
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]);
	settings->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		settings->nb_eat_by_philo = ft_atoi(argv[5]);
	settings->start_timestamp = current_time_ms();
	return (*settings);
}



int	main(int argc, char **argv)
{
	t_settings	*settings;
	t_philo		*philos;

	if (argc < 5)
		return (printf("Argument required"), 1);
	if (argc > 6)
		return (printf("Too many args"), 1);
	settings = malloc(sizeof(t_settings));
	if (!settings)
		return (EXIT_FAILURE);
	init_settings(argv, settings);
	init_philo(settings, philos);
	return (EXIT_SUCCESS);
}
