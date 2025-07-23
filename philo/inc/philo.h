/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:29:47 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/23 13:20:53 by vgoyzuet         ###   ########.fr       */
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

# define FORK		"%lld %d has taken a fork\n"
# define EAT		"%lld %d is eating\n"
# define SLEEP		"%lld %d is sleeping\n"
# define THINK		"%lld %d is thinking\n"
# define DEAD		"%lld %d died\n"

# define ERROR1		"Error: Arguments must be positive intergers\n"

typedef enum e_action
{
	A_FORK,
	A_EAT,
	A_SLEEP,
	A_THINK,
	A_DEAD,
}	t_action;

void	parse_args(int argc, char **argv);

/*write_utils*/
void	w_action(t_action action, long long time, int id);

/*ft_utils*/
size_t	ft_strlen(char *str);
long	ft_atol(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
