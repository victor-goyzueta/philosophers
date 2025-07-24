/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:34:38 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/24 05:04:54 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philo;

	parse_args(argc, argv);
	init_info(&info, argv);
	philo = ft_calloc(info.num_philos, sizeof(t_philo));
	if (!philo)
	{
		destroy_mutexes_info(&info, 0);
		exit(EXIT_FAILURE);
	}
	init_philo(philo, &info);
	simulation(philo, &info);
	free(philo);
	exit(EXIT_SUCCESS);
}
