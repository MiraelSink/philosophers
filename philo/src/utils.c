/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:13 by maandria          #+#    #+#             */
/*   Updated: 2024/12/28 17:33:39 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ph_atoi(char *str)
{
	int	nb;
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (str[i] == 32 || str[i] == '\t')
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nb = nb * 10 + (str[i] - 48);
		else
			return (-1);
		i++;
	}
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
