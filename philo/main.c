/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 11:58:59 by afournie          #+#    #+#             */
/*   Updated: 2026/03/04 11:33:41 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int ac, char **av)
{
	t_settings	*settings;
	t_philo		*philos;
	t_fork		*forks;

	if (check_args(ac))
		return (EXIT_FAILURE);
	if (ft_atoi(av[1]) == 1)
	{
		usleep(ft_atoi(av[2]));
		printf("%d 1 died", ft_atoi(av[2]));
		return (EXIT_SUCCESS);
	}
	settings = malloc(sizeof(t_settings));
	if (!settings)
		return (EXIT_FAILURE);
	init_settings(av, settings);
	mutex_init(settings);
	if (!init_philo_forks(settings, &forks) || !init_philo(&philos, forks,
			settings))
		return (free_settings(settings), free_forks(forks, settings),
			EXIT_FAILURE);
	start_routine(philos);
	jarvis(settings, philos);
	free_all(settings, philos, forks);
	return (EXIT_SUCCESS);
}
