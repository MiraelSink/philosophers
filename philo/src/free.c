/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:16:42 by maandria          #+#    #+#             */
/*   Updated: 2024/12/26 12:48:33 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_value(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&(table->lock_fork[i]));
		i++;
	}
	pthread_mutex_destroy(&table->printing);
	pthread_mutex_destroy(&table->check_meal);
	free(table->state_forks);
	free(table->lock_fork);
	free(table->philo);
}
