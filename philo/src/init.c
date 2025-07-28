/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:35:10 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/28 12:06:49 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_info *info)
{
	int	i;

	if (pthread_mutex_init(&info->meal_lock, NULL))
		return (1);
	if (pthread_mutex_init(&info->print_lock, NULL))
	{
		pthread_mutex_destroy(&info->meal_lock);
		return (1);
	}
	if (pthread_mutex_init(&info->death_lock, NULL))
	{
		pthread_mutex_destroy(&info->meal_lock);
		pthread_mutex_destroy(&info->print_lock);
		return (1);
	}
	info->forks = ft_calloc(info->num_philos, sizeof(pthread_mutex_t));
	if (!info->forks)
		return (destroy_mutexes_lock(info), 1);
	i = -1;
	while (++i < info->num_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (destroy_mutexes_info(info, i), 1);
	}
	return (0);
}

void	init_info(t_info *info, char **argv)
{
	(*info).num_philos = (int)ft_atol(argv[1]);
	if ((*info).num_philos > PHILO_MAX)
	{
		write(STDERR_FILENO,
			"Error: The number of philosophers should not exceed 200\n", 57);
		exit(EXIT_FAILURE);
	}
	(*info).ms_to_die = (int)ft_atol(argv[2]);
	(*info).ms_to_eat = (int)ft_atol(argv[3]);
	(*info).ms_to_sleep = (int)ft_atol(argv[4]);
	(*info).meals_req = -1;
	if (argv[5])
		(*info).meals_req = (int)ft_atol(argv[5]);
	(*info).death = false;
	(*info).all_ate = false;
	if (init_mutexes(info))
		exit(EXIT_FAILURE);
}

void	init_philo(t_philo **philo, t_info *info)
{
	int	i;

	if (!philo)
	{
		if (info)
			destroy_mutexes_info(info, info->num_philos);
		exit(EXIT_FAILURE);
	}
	*philo = ft_calloc(info->num_philos, sizeof(t_philo));
	if (!*philo)
	{
		destroy_mutexes_info(info, info->num_philos);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < info->num_philos)
	{
		(*philo)[i].info = info;
		(*philo)[i].id = i + 1;
		(*philo)[i].meals_eaten = 0;
		(*philo)[i].l_fork = &info->forks[i];
		(*philo)[i].r_fork = &info->forks[(i + 1) % info->num_philos];
		i++;
	}
}
