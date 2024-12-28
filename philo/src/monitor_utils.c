/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 21:54:30 by maandria          #+#    #+#             */
/*   Updated: 2024/12/28 21:57:42 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_last_meal(t_table *t, unsigned long int *lm, int i)
{
	pthread_mutex_lock(&(t->check_meal));
	*lm = t->philo[i].last_meal;
	pthread_mutex_unlock(&(t->check_meal));
}

void	watch_out(t_table *table, int i)
{
	pthread_mutex_lock(&(table->printing));
	printf("%lu %d died\n", time_diff(table->first_timestamp,
			get_time()), table->philo[i].philo_id);
	pthread_mutex_unlock(&(table->printing));
	pthread_mutex_lock(&(table->check_meal));
	table->died = 1;
	pthread_mutex_unlock(&(table->check_meal));
}

void	check_nb_eat(t_table *table, int i, int *nb_eat)
{
	pthread_mutex_lock(&(table->check_meal));
	*nb_eat = table->philo[i].x_ate;
	pthread_mutex_unlock(&(table->check_meal));
}

int	addition_full(t_table *table, int i, int nb_eat)
{
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
			return (1);
		}
	}
	return (0);
}
