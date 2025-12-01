/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotakagi <yotakagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:08:30 by yotakagi          #+#    #+#             */
/*   Updated: 2025/12/01 12:16:52 by yotakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static const char	*valid_input(const char *str, int *error)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		*error = print_error("positive number only");
	if (!is_digit(*str))
		*error = print_error("The input is not correct");
	if (*error)
		return (NULL);
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		*error = print_error("The value is too big,INT_MAX is the limits");
	return (number);
}

static long	ft_atol(const char *str, int *error)
{
	long	num;

	num = 0;
	str = valid_input(str, error);
	if (*error)
		return (-1);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		*error = print_error("The value is too big,INT_MAX is the limits");
	return (num);
}

int	parse_input(t_table *table, char **av)
{
	int	err;

	err = 0;
	table->philo_nbr = ft_atol(av[1], &err);
	table->time_to_die = ft_atol(av[2], &err) * 1000;
	table->time_to_eat = ft_atol(av[3], &err) * 1000;
	table->time_to_sleep = ft_atol(av[4], &err) * 1000;
	table->nbr_limit_meals = -1;
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5], &err);
	if (err)
		return (1);
	if (table->philo_nbr <= 0 || table->time_to_die < 60000
		|| table->time_to_eat < 60000 || table->time_to_sleep < 60000)
		return (print_error("Invalid input arguments"));
	return (0);
}
