/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:37:07 by maandria          #+#    #+#             */
/*   Updated: 2024/12/28 15:44:23 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char *av[])
{
	t_table	table;

	if (!init_all(ac, av, &table))
		return (1);
	launch(&table);
	free_value(&table);
	return (0);
}
