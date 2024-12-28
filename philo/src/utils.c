/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:13 by maandria          #+#    #+#             */
/*   Updated: 2024/12/28 21:20:29 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ph_atoi(char *str)
{
	int	nb;
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == '\t')
		i++;
	if (str[i])
		return (0);
	return (nb * sign);
}

void	print_task(t_table *table, unsigned int id, char *str)
{
	pthread_mutex_lock(&(table->printing));
	if (check_die(table) == 0)
	{
		printf("%lu ", get_time() - table->first_timestamp);
		printf("%u ", id);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(table->printing));
	return ;
}

void	take_time_value(t_table *table, char **av)
{
	table->time_die = ph_atoi(av[2]);
	table->time_eat = ph_atoi(av[3]);
	table->time_sleep = ph_atoi(av[4]);
}

void	eats_even(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&(table->lock_fork[philo->left_fork_id - 1]));
	table->state_forks[philo->left_fork_id - 1] = 1;
	print_task(table, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(table->lock_fork[philo->right_fork_id - 1]));
	table->state_forks[philo->right_fork_id - 1] = 1;
	print_task(table, philo->philo_id, "has taken a fork");
}

void	eats_odd(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&(table->lock_fork[philo->right_fork_id - 1]));
	table->state_forks[philo->right_fork_id - 1] = 1;
	print_task(table, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(table->lock_fork[philo->left_fork_id - 1]));
	table->state_forks[philo->left_fork_id - 1] = 1;
	print_task(table, philo->philo_id, "has taken a fork");
}
