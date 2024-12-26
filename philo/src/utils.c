/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:13 by maandria          #+#    #+#             */
/*   Updated: 2024/12/26 12:48:52 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned int	ph_atoi(char *str)
{
	unsigned int	nb;
	int				i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] < '0' && str[i] >'9')
			return (0);
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb);
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
