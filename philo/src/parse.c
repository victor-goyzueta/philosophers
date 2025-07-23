/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:41:17 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/23 13:22:53 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_spacetab(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

static bool	is_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	while (str[i] && is_spacetab(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		i++;
	}
	while (str[i] && is_spacetab(str[i]))
		i++;
	if (str[i])
		return (false);
	return (true);
}

void	parse_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		write(STDERR_FILENO, "Error: Usage: ./philo <num_philos>", 35);
		write(STDERR_FILENO, " <time_to_die> <time_to_eat> ", 30);
		write(STDERR_FILENO, "<time_to_sleep> [meals_required]\n", 34);
		exit(EXIT_FAILURE);
	}
	i = 1;
	while (argv[i])
	{
		if (!is_number(argv[i])
			|| (ft_atol(argv[i]) < 1 || ft_atol(argv[i]) > INT_MAX))
		{
			write(STDERR_FILENO, ERROR1, 45);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
