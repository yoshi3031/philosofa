/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* monitor.c                                          :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: yotakagi <yotakagi@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/11/21 15:20:31 by yotakagi          #+#    #+#             */
/* Updated: 2025/12/01 14:00:00 by yotakagi         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1000;
	if (elapsed >= t_to_die)
		return (true);
	return (false);
}

static bool	check_simulation_state(t_table *table)
{
	int	i;
	int	full_count;

	i = -1;
	full_count = 0;
	while (++i < table->philo_nbr)
	{
		if (philo_died(table->philos + i))
		{
			write_status(DIED, table->philos + i);
			set_bool(&table->table_mutex, &table->end_simulation, true);
			return (true);
		}
		if (table->nbr_limit_meals != -1
			&& get_bool(&table->philos[i].philo_mutex, &table->philos[i].full))
			full_count++;
	}
	if (table->nbr_limit_meals != -1 && full_count == table->philo_nbr)
	{
		set_bool(&table->table_mutex, &table->end_simulation, true);
		return (true);
	}
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr))
		usleep(100);
	while (!simulation_finished(table))
	{
		if (check_simulation_state(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
