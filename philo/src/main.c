/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:34:38 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/24 17:49:04 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philo;

	parse_args(argc, argv);
	init_info(&info, argv);
	init_philo(&philo, &info);
	simulation(philo, &info);
	free(philo);
	exit(EXIT_SUCCESS);
}
