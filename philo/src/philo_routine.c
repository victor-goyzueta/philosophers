/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:22:43 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/28 18:05:56 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	select_forks(t_philo *philo,
					pthread_mutex_t **first, pthread_mutex_t **second, bool par)
{
	if (par)
	{
		*first = philo->r_fork;
		*second = philo->l_fork;
		usleep(100);
	}
	else
	{
		*first = philo->l_fork;
		*second = philo->r_fork;
	}
}

void	*single_philo_case(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(philo->l_fork);
	print_action(A_FORK, get_time_ms() - info->start_time, philo->id);
	while (is_simulation_running(philo))
		usleep(100);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

bool	grab_forks(t_philo *philo, t_info *info,
					pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	if (!is_simulation_running(philo))
	{
		pthread_mutex_unlock(first);
		return (false);
	}
	print_action(A_FORK, get_time_ms() - info->start_time, philo->id);
	pthread_mutex_lock(second);
	if (!is_simulation_running(philo))
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		return (false);
	}
	print_action(A_FORK, get_time_ms() - info->start_time, philo->id);
	if (!is_simulation_running(philo))
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		return (false);
	}
	return (true);
}

bool	eating(t_philo *philo, t_info *info,
					pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(&info->meal_lock);
	philo->last_meal_time = get_time_ms();
	if (!is_simulation_running(philo))
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(&info->meal_lock);
		return (false);
	}
	print_action(A_EAT, philo->last_meal_time - info->start_time, philo->id);
	philo->meals_eaten++;
	pthread_mutex_unlock(&info->meal_lock);
	wait_action(info->ms_to_eat, philo);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	return (true);
}

bool	sleeping(t_philo *philo, t_info *info)
{
	if (!is_simulation_running(philo))
		return (false);
	print_action(A_SLEEP, get_time_ms() - info->start_time, philo->id);
	wait_action(info->ms_to_sleep, philo);
	return (true);
}
