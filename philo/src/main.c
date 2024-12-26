/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:37:07 by maandria          #+#    #+#             */
/*   Updated: 2024/12/26 12:48:40 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char *av[])
{
	t_table table;

	if (!init_all(ac, av, &table))
		return (1);
	launch(&table);
	free_value(&table);
	return (0);
}
// {
// 	if (ac == 5 || ac == 6)
// 	{
// 		t_table			table;
// 		unsigned int	i;

// 		init_all(av, &table);
// 		i = 0;
// 		table.first_timestamp = get_time();
// 		while (i < table.nb_philo)
// 		{
// 			printf("philo %u\n", table.philo[i].philo_id);
// 			printf("fork on his left : %u\t", table.philo[i].left_fork_id);
// 			printf("fork on his right :%u\n", table.philo[i].right_fork_id);
// 			printf("ate %u time\n", table.philo[i].x_ate);
// 			printf("------------------------------------\n");
// 			i++;
// 		}
// 		i = 0;
// 		while (i < table.nb_philo)
// 		{
// 			printf("id of philo : %u\n", table.philo[i].philo_id);
// 			i++;
// 		}
// 		printf("time to die : %u\n", table.time_die);
// 		printf("time to eat : %u\n", table.time_eat);
// 		printf("time to sleep : %u\n", table.time_sleep);
// 		if (ac == 6)
// 			printf("number of time each one should eat : %u\n", table.nb_each_eat);
// 		printf("time start from : %lu\n", time_diff(table.first_timestamp, table.first_timestamp));
// 		smart_sleep(table.time_die, &table);
// 		printf("time end at : %lu\n", time_diff(table.first_timestamp, get_time()));
// 		free_value(&table);
// 	}
// 	return (0);
// }
