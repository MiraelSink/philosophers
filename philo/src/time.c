/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:50:09 by maandria          #+#    #+#             */
/*   Updated: 2024/12/28 16:23:33 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long int	get_time(void)
{
	struct timeval	tv;
	long int		gt;

	if (gettimeofday(&tv, NULL))
		return (0);
	gt = (tv.tv_sec * (1000)) + (tv.tv_usec / 1000);
	return (gt);
}

long int	time_diff(long int past, long int present)
{
	return (present - past);
}

void	smart_sleep(long int time, t_table *table)
{
	unsigned long int	i;

	i = get_time();
	while (check_die(table) != 1)
	{
		if (time_diff(i, get_time()) > time)
			break ;
		usleep(5);
	}
}
