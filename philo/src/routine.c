/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:09:37 by maandria          #+#    #+#             */
/*   Updated: 2024/12/28 18:42:00 by maandria         ###   ########.fr       */
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
	print_task(table, philo->philo_id, "is eating");
	pthread_mutex_lock(&(table->check_meal));
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(table->check_meal));
	smart_sleep(table->time_eat, table);
	pthread_mutex_lock(&(table->check_meal));
	philo->x_ate += 1;
	pthread_mutex_unlock(&(table->check_meal));
	table->state_forks[philo->left_fork_id - 1] = 0;
	pthread_mutex_unlock(&(table->lock_fork[philo->left_fork_id - 1]));
	table->state_forks[philo->right_fork_id - 1] = 0;
	pthread_mutex_unlock(&(table->lock_fork[philo->right_fork_id - 1]));
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
		usleep(10);
		i = 0;
		while (i < table->nb_philo)
		{
			pthread_mutex_lock(&(table->check_meal));
			last_meal = table->philo[i].last_meal;
			pthread_mutex_unlock(&(table->check_meal));
			if (time_diff(last_meal, get_time()) >= table->time_die)
			{
				pthread_mutex_lock(&(table->printing));
				printf("%lu %d died\n", time_diff(table->first_timestamp,
						get_time()), table->philo[i].philo_id);
				pthread_mutex_unlock(&(table->printing));
				pthread_mutex_lock(&(table->check_meal));
				table->died = 1;
				pthread_mutex_unlock(&(table->check_meal));
				break ;
			}
			pthread_mutex_lock(&(table->check_meal));
			nb_eat = table->philo[i].x_ate;
			pthread_mutex_unlock(&(table->check_meal));
			if (table->nb_each_eat != -1 && nb_eat > table->nb_each_eat)
			{
				if (table->philo[i].is_full == 0)
					table->philo[i].is_full = 1;
				if (table->philo[i].is_full == 1)
					table->all_ate += 1;
				if ((int)table->all_ate == table->nb_philo)
				{
					pthread_mutex_lock(&(table->check_meal));
					table->died = 1;
					pthread_mutex_unlock(&(table->check_meal));
					break ;
				}
			}
			i++;
		}
	}
	return (NULL);
}

int	launch(t_table *table)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	table->first_timestamp = get_time();
	pthread_create(&monitor, NULL, monitr, table);
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&(table->check_meal));
		table->philo[i].last_meal = table->first_timestamp;
		pthread_mutex_unlock(&(table->check_meal));
		i++;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_create(&table->philo[i].thread_id, NULL, routine,
			&table->philo[i]);
		i++;
	}
	i = 0;
	pthread_join(monitor, NULL);
	while (i < table->nb_philo)
	{
		pthread_join((table->philo[i].thread_id), NULL);
		i++;
	}
	return (1);
}
