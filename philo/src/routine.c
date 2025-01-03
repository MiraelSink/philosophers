/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:09:37 by maandria          #+#    #+#             */
/*   Updated: 2024/12/29 00:46:27 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eats(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (philo->philo_id % 2 == 0)
		eats_even(table, philo);
	else
		eats_odd(table, philo);
}

void	*routine(void *void_routine)
{
	unsigned int	i;
	t_philo			*philo;
	t_table			*table;

	i = 0;
	philo = (t_philo *)void_routine;
	table = philo->table;
	if (table->nb_philo == 1)
	{
		print_task(table, philo->philo_id, "has taken a fork");
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		usleep(500);
	while (check_die(table) != 1)
	{
		eats(philo);
		sleeping(philo->philo_id, table);
		print_task(table, philo->philo_id, "is thinking");
		if (table->nb_philo % 2)
			smart_sleep((table->time_eat * 2 - table->time_sleep), table);
		i++;
	}
	return (NULL);
}

int	check_die(t_table *table)
{
	int	die;

	pthread_mutex_lock(&(table->check_meal));
	die = table->died;
	pthread_mutex_unlock(&(table->check_meal));
	return (die);
}

void	*monitr(void *arg)
{
	t_table				*table;
	unsigned long int	last_meal;
	int					nb_eat;
	int					i;

	table = (t_table *)arg;
	i = 0;
	while (check_die(table) != 1)
	{
		usleep(5);
		i = -1;
		while (++i < table->nb_philo)
		{
			check_last_meal(table, &last_meal, i);
			if (time_diff(last_meal, get_time()) >= table->time_die)
			{
				watch_out(table, i);
				break ;
			}
			check_nb_eat(table, i, &nb_eat);
			if (addition_full(table, i, nb_eat))
				break ;
		}
	}
	return (NULL);
}

int	launch(t_table *table)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	table->first_timestamp = get_time();
	while (++i < table->nb_philo)
	{
		pthread_mutex_lock(&(table->check_meal));
		table->philo[i].last_meal = table->first_timestamp;
		pthread_mutex_unlock(&(table->check_meal));
	}
	pthread_create(&monitor, NULL, monitr, table);
	i = -1;
	while (++i < table->nb_philo)
	{
		pthread_create(&table->philo[i].thread_id, NULL, routine,
			&table->philo[i]);
	}
	i = -1;
	pthread_join(monitor, NULL);
	while (++i < table->nb_philo)
		pthread_join((table->philo[i].thread_id), NULL);
	return (1);
}
