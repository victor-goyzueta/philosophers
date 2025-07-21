/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:29:47 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/21 22:50:14 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

# define ORANGE		"\001\033[1;33m\002"
# define YELLOW		"\001\033[0;33m\002"
# define PURPLE		"\001\033[0;35m\002"
# define BLUE		"\001\033[0;34m\002"
# define RED		"\001\033[0;31m\002"
# define WHITE		"\001\033[0m\002"

# define FORK		ORANGE "%lld %d has taken a fork\n" WHITE
# define EAT		YELLOW "%lld %d is eating\n" WHITE
# define SLEEP		PURPLE "%lld %d is sleeping\n" WHITE
# define THINK		BLUE "%lld %d is thinking\n" WHITE
# define DEAD		RED "%lld %d died\n" WHITE

# define USAGE \
	"Usage: ./philo <num_philos> <time_to_die> <time_to_eat> " \
	"<time_to_sleep> [meals_required]\n"
# define ERROR1		"Error: Invalid number of arguments\n"
# define ERROR2		"Error: Arguments must be positive intergers\n"

typedef enum e_action
{
	A_FORK,
	A_EAT,
	A_SLEEP,
	A_THINK,
	A_DEAD,
}	t_action;

void	parse_args(int argc, char **argv);

#endif
