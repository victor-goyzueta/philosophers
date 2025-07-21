/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:41:17 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/07/21 22:44:15 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_number(char *str)
{
	int	i;
	
	if (!str || !*str)
		return (false);
	i = 0;
	while (str[i] && (str[i] >= 9 && str[i] <= 13 || str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

long	ft_atol(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (sign * result);
}

bool	is_validate(char *arg)
{
	if (!arg || !*arg)
		return (false);
	while (arg)
	{
		if (!is_number(arg) || (ft_atol(arg) < 0 || ft_atol > INT_MAX))
			return (false);
		arg++;
	}
	return (true);
}

void	parse_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 || argc != 6)
	{
		write(STDERR_FILENO, ERROR1, 36);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (argv[++i])
	{
		if (!is_validate(argv[i]))
		{
			write(STDERR_FILENO, ERROR2, 45);
			exit(EXIT_FAILURE);
		}
	}
}
