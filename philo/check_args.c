/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:27:08 by afournie          #+#    #+#             */
/*   Updated: 2026/03/04 11:33:30 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	check_args(int ac)
{
	if (ac < 5)
		return (printf("Argument required"), 1);
	if (ac > 6)
		return (printf("Too many args"), 1);
	return (0);
}
