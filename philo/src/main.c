/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:34:38 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/23 12:50:45 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	struct timeval	tv;

	parse_args(argc, argv);
	if (gettimeofday(&tv, NULL) != 0)
		exit(EXIT_FAILURE);
	w_action(A_FORK, tv.tv_usec, 1);
	w_action(A_EAT, tv.tv_usec, 1);
	w_action(A_SLEEP, tv.tv_usec, 1);
	w_action(A_THINK, tv.tv_usec, 1);
	w_action(A_DEAD, tv.tv_usec, 1);
	return (EXIT_SUCCESS);
}
