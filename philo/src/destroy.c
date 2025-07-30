/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 00:02:59 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/30 12:29:01 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes_lock(t_info *info)
{
	if (!info)
		return ;
	pthread_mutex_destroy(&info->meal_lock);
	pthread_mutex_destroy(&info->print_lock);
	pthread_mutex_destroy(&info->death_lock);
}

void	destroy_mutexes_info(t_info *info, int i)
{
	if (!info)
		return ;
	destroy_mutexes_lock(info);
	if (i <= 0)
		return (free(info->forks));
	while (--i >= 0)
		pthread_mutex_destroy(&info->forks[i]);
	free(info->forks);
}

void	destroy_mutexes_all(t_philo *philo, t_info *info, int i)
{
	while (--i >= 0)
		pthread_join(philo[i].thread, NULL);
	destroy_mutexes_info(info, info->num_philos);
	exit(EXIT_FAILURE);
}
