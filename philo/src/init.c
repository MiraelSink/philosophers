/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:14:25 by maandria          #+#    #+#             */
/*   Updated: 2024/12/26 12:48:37 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_mutex(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->state_forks[i] = 0;
		pthread_mutex_init(&(table->lock_fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&table->printing, NULL);
	pthread_mutex_init(&table->check_meal, NULL);
	return (1);
}

int	init_value(int ac, char **av, t_table *table)
{
	table->nb_philo = ph_atoi(av[1]);
	if (table->nb_philo <= 0)
	{
		write(2, "Error: wrong number of philosophers\n", 36);
		return (0);
	}
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philo)
		return (0);
	table->time_die = ph_atoi(av[2]);
	table->time_eat = ph_atoi(av[3]);
	table->time_sleep = ph_atoi(av[4]);
	if (table->time_die <= 0 || table->time_eat <= 0 || table->time_sleep <= 0)
	{
		write(2, "Error: wrong time\n", 18);
		return (0);
	}
	table->nb_each_eat = -1;
	if (ac == 6)
	{
		table->nb_each_eat = ph_atoi(av[5]);
		if (table->nb_each_eat <= 0)
		{
			write(2, "Error: wrong number of each to eat\n", 36);
			return (0);
		}
	}
	table->all_ate = 0;
	table->died = 0;
	return (1);
}

int	init_philosophers(t_table *table)
{
	unsigned int i;

	i = table->nb_philo;
	while ( i > 0)
	{
		table->philo[i - 1].is_full = 0;
		table->philo[i - 1].philo_id = i;
		table->philo[i - 1].x_ate = 0;
		table->philo[i - 1].left_fork_id = i;
		if (i == 1)
			table->philo[i - 1].right_fork_id = table->nb_philo;
		else
			table->philo[i - 1].right_fork_id = i - 1;
		table->philo[i - 1].last_meal = 0;
		table->philo[i - 1].last_meal = table->first_timestamp;
		table->philo[i - 1].table = table;
		i--;
	}
	return (0);
}

int	init_all(int ac, char **av, t_table *table)
{
	if (ac != 5 && ac != 6)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		write(2, "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep"
			"[number_of_time_each_philosopher_must_eat]\n", 119);
		return (0);
	}
	if (init_value(ac, av, table) == 0)
		return (0);
	table->lock_fork = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	table->state_forks = malloc(sizeof(unsigned int) * table->nb_philo);
	if (!init_mutex(table))
		return (0);
	init_philosophers(table);
	return (1);
}
