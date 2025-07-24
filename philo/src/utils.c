/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:07:01 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/24 03:01:03 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*get_message(char *color, char *msg)
{
	size_t	len;
	char	*message;

	len = ft_strlen(color) + ft_strlen(msg) + ft_strlen(WHITE);
	message = ft_calloc(len, sizeof(char));
	if (!message)
		return (NULL);
	message = ft_strjoin(message, color);
	if (!message)
		return (NULL);
	message = ft_strjoin(message, msg);
	if (!message)
		return (NULL);
	message = ft_strjoin(message, WHITE);
	if (!message)
		return (NULL);
	return (message);
}

void	w_action(t_action action, long long tv, int id)
{
	char	*message;

	if (action < 0 || action > 4)
		return ;
	message = NULL;
	if (action == A_FORK)
		message = get_message(ORANGE, FORK);
	else if (action == A_EAT)
		message = get_message(YELLOW, EAT);
	else if (action == A_SLEEP)
		message = get_message(PURPLE, SLEEP);
	else if (action == A_THINK)
		message = get_message(BLUE, THINK);
	else if (action == A_DEAD)
		message = get_message(RED, DEAD);
	if (!message)
		exit(EXIT_FAILURE);
	printf(message, tv, id);
	return (free(message));
}

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	smart_sleep(long long duration_ms)
{
	long long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < duration_ms)
		usleep(100); 
}
