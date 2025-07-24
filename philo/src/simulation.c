/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:14:42 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/24 05:06:22 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *ptr)
{
	t_philo		*philo;
	t_info		*info;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	philo = (t_philo *)ptr;
	info = philo->info;

	while (get_time_ms() < info->start_time)
		usleep(100);
	if (philo->id % 2 == 0)
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}
	else
	{
		first = philo->l_fork;
		second = philo->r_fork;
	}
	while (1)
	{
		pthread_mutex_lock(&info->death_lock);
		if (info->death
			|| (info->meals_req != -1 && philo->meals_eaten >= info->meals_req))
		{
			pthread_mutex_unlock(&info->death_lock);
			break ;
		}
		pthread_mutex_unlock(&info->death_lock);

		pthread_mutex_lock(first);
		w_action(A_FORK, get_time_ms() - info->start_time, philo->id);
		pthread_mutex_lock(second);
		w_action(A_FORK, get_time_ms() - info->start_time, philo->id);

		pthread_mutex_lock(&info->meal_lock);
		philo->last_meal_time = get_time_ms();
		w_action(A_EAT, philo->last_meal_time - info->start_time, philo->id);
		philo->meals_eaten++;
		pthread_mutex_unlock(&info->meal_lock);

		smart_sleep(info->ms_to_eat);

		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);

		w_action(A_SLEEP, get_time_ms() - info->start_time, philo->id);
		smart_sleep(info->ms_to_sleep);

		w_action(A_THINK, get_time_ms() - info->start_time, philo->id);
	}
	return (NULL);
}

static bool	check_death(t_philo *philo)
{
	long long	now;
	t_info		*info;
	long long	last_meal;

	info = philo->info;
	now = get_time_ms();
	pthread_mutex_lock(&info->meal_lock); // 💡 proteger lectura
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&info->meal_lock);
	if ((now - last_meal) > info->ms_to_die)
	{
		pthread_mutex_lock(&info->death_lock);
		if (!info->death)
		{
			info->death = 1;
			pthread_mutex_unlock(&info->death_lock);
			pthread_mutex_lock(&info->print_lock);
			w_action(A_DEAD, now - info->start_time, philo->id);
			pthread_mutex_unlock(&info->print_lock);
		}
		else
			pthread_mutex_unlock(&info->death_lock);
		return (true);
	}
	return (false);
}

static void	*monitor_routine(void *ptr)
{
	t_philo	*philo;
	t_info	*info;
	int		i;
	int		full;

	philo = (t_philo *)ptr;
	info = philo[0].info;

	while (1)
	{
		i = 0;
		full = 0;
		while (i < info->num_philos)
		{
			if (check_death(&philo[i]))
				return (NULL);

			pthread_mutex_lock(&info->meal_lock);
			if (info->meals_req != -1 && philo[i].meals_eaten >= info->meals_req)
				full++;
			pthread_mutex_unlock(&info->meal_lock);
			i++;
		}
		if (info->meals_req != -1 && full == info->num_philos)
		{
			pthread_mutex_lock(&info->death_lock);
			info->death = 1;
			pthread_mutex_unlock(&info->death_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	simulation(t_philo *philo, t_info *info)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	(*info).start_time = get_time_ms();
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
