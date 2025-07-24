/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:14:42 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/24 04:14:24 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *ptr)
{
	t_philo		*philo;
	t_info		*info;

	philo = (t_philo *)ptr;
	info = philo->info;

	// Evitar deadlock: los filósofos pares esperan un poco
	while (get_time_ms() < info->start_time)
		usleep(100);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&info->death_lock);
		if (info->death)
		{
			pthread_mutex_unlock(&info->death_lock);
			break ;
		}
		pthread_mutex_unlock(&info->death_lock);

		// Pick up forks
		pthread_mutex_lock(philo->l_fork);
		w_action(A_FORK, get_time_ms() - info->start_time, philo->id);
		pthread_mutex_lock(philo->r_fork);
		w_action(A_FORK, get_time_ms() - info->start_time, philo->id);
		
		// Eating
		pthread_mutex_lock(&info->meal_lock);
		philo->last_meal_time = get_time_ms();
		w_action(A_EAT, philo->last_meal_time - info->start_time, philo->id);
		pthread_mutex_unlock(&info->meal_lock);
		smart_sleep(info->ms_to_eat);
		philo->meals_eaten++;

		// Drop forks
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);

		// Sleeping
		w_action(A_SLEEP, get_time_ms() - info->start_time, philo->id);
		smart_sleep(info->ms_to_sleep);

		// Thinking
		w_action(A_THINK, get_time_ms() - info->start_time, philo->id);
	}
	return (NULL);
}

static bool	check_death(t_philo *philo)
{
	long long	now;
	t_info		*info;

	info = philo->info;
	now = get_time_ms();

	pthread_mutex_lock(&info->death_lock);
	if ((now - philo->last_meal_time) > info->ms_to_die)
	{
		pthread_mutex_unlock(&info->death_lock);
		pthread_mutex_lock(&info->print_lock);
		w_action(A_DEAD, now - info->start_time, philo->id);
		pthread_mutex_unlock(&info->print_lock);
		info->death = 1;
		return (true);
	}
	pthread_mutex_unlock(&info->death_lock);
	return (false);
}

static void	*monitor_routine(void *ptr)
{
	t_philo	*philo;
	t_info	*info;
	int		i;

	philo = (t_philo *)ptr;
	info = philo[0].info;

	while (1)
	{
		i = 0;
		while (i < info->num_philos)
		{
			if (check_death(&philo[i]))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	simulation(t_philo *philo, t_info *info)
{
	int			i;
	pthread_t	monitor;

	// info->start_time = get_time_ms() + 100;
	i = 0;
	while (i < info->num_philos)
	{
		philo[i].last_meal_time = info->start_time;
		if (pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]))
			destroy_mutexes_all(philo, info, i);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, philo))
		destroy_mutexes_all(philo, info, i);
	i = 0;
	while (i < info->num_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return ;
}
