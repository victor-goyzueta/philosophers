/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:29:47 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/24 20:09:10 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
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

typedef struct s_info
{
	int				num_philos;
	int				ms_to_die;
	int				ms_to_eat;
	int				ms_to_sleep;
	int				meals_req;
	bool			death;
	bool			all_ate;
	long long		start_time;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	*forks;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_info			*info;
}	t_philo;

/*main*/
void		parse_args(int argc, char **argv);
void		init_info(t_info *info, char **argv);
void		init_philo(t_philo **philo, t_info *info);
void		simulation(t_philo *philo, t_info *info);

/*routines*/
void		*philo_routine(void *ptr);

/*destroy*/
void		destroy_mutexes_lock(t_info *info);
void		destroy_mutexes_info(t_info *info, int i);
void		destroy_mutexes_all(t_philo *philo, t_info *info, int i);

/*utils*/
void		w_action(t_action action, long long tv, int id);;
long long	get_time_ms(void);
void		wait_action(long long duration_ms, t_philo *philo);
bool		is_simulation_running(t_philo *philo);

/*ft_utils*/
size_t		ft_strlen(char *str);
long		ft_atol(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t num, size_t size);
char		*ft_strjoin(char const *s1, char const *s2);

#endif
