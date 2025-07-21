/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:49:10 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/21 14:59:41 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_action action, long long time, int id)
{
	if (action < 0 || action > 4)
		return ;
	if (action == A_FORK)
		printf(FORK, time, id);
	else if (action == A_EAT)
		printf(EAT, time, id);
	else if (action == A_SLEEP)
		printf(SLEEP, time, id);
	else if (action == A_THINK)
		printf(THINK, time, id);
	else if (action == A_DEAD)
		printf(DEAD, time, id);
}
