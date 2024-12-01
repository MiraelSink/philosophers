/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:14:25 by maandria          #+#    #+#             */
/*   Updated: 2024/11/29 21:53:01 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_mutex(t_table *table)
{
	int i;

	i = table->nb_philo;
	while (i >= 0)
	{
		if (pthread_mutex_init(&(table->lock_fork[i - 1]), NULL))
			return (1);
		i--;
	}
	if (pthread_mutex_init(&(table->printing), NULL))
		return (1);
	if (pthread_mutex_init(&(table->check_meal), NULL))
		return (1);
	return (0);
}

int	init_value(char **av, t_table *table)
{
	table->nb_philo = ph_atoi(av[1]);
	table->philo = malloc(sizeof(t_philo) * table->nb_philo);
	table->time_die = ph_atoi(av[2]);
	table->time_eat = ph_atoi(av[3]);
	table->time_sleep = ph_atoi(av[4]);
	table->all_ate = 0;
	table->died = 0;
	return (0);
}

int	init_philosophers(t_table *table)
{
	unsigned int i;

	i = table->nb_philo;
	while ( i > 0)
	{
		table->philo[i - 1].philo_id = i;
		table->philo[i - 1].x_ate = 0;
		table->philo[i - 1].left_fork_id = i;
		if (i == 1)
			table->philo[i - 1].right_fork_id = table->nb_philo;
		else
			table->philo[i - 1].right_fork_id = i - 1;
		table->philo[i - 1].last_meal = 0;
		table->philo[i - 1].table = table;
		i--;
	}
	return (0);
}

int	init_all(char **av, t_table *table)
{
	init_value(av, table);
	if (table->nb_philo < 2 || table->time_die < 0 || table->time_eat < 0
		|| table->time_sleep < 0 || table->nb_philo > 200)
		return (1);
	if (av[5])
	{
		table->nb_each_eat = ph_atoi(av[5]);
		if (table->nb_each_eat <= 0)
			return (1);
	}
	else
		table->nb_each_eat = -1;
	// if (init_mutex(table))
	// 	return (2);
	init_philosophers(table);
	return (0);
}
