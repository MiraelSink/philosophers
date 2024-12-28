/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:03:03 by maandria          #+#    #+#             */
/*   Updated: 2024/12/28 17:03:03 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	w_philo(int code)
{
	if (code == 1)
		write(2, "Error: wrong number of philosophers\n", 36);
	if (code == 2)
		write(2, "Error: wrong time\n", 18);
	if (code == 3)
		write(2, "Error: wrong number of each to eat\n", 36);
	return (0);
}
