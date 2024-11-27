/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:09:37 by maandria          #+#    #+#             */
/*   Updated: 2024/11/12 22:09:37 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void eats(t_philo *philo)
{
    t_table *table;

    table = philo->table;
    if (philo->philo_id % 2 == 0)
    {
        pthread_mutex_lock(&(table->lock_fork[philo->left_fork_id]));
        print_task(table, philo->philo_id, "has taken a fork");
        pthread_mutex_lock(&(table->lock_fork[philo->right_fork_id]));
        print_task(table, philo->philo_id, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&(table->lock_fork[philo->right_fork_id]));
        print_task(table, philo->philo_id, "has taken a fork");
        pthread_mutex_lock(&(table->lock_fork[philo->left_fork_id]));
        print_task(table, philo->philo_id, "has taken a fork");
    }
    pthread_mutex_lock(&(table->check_meal));
    print_task(table, philo->philo_id, "is eating");
    philo->last_meal = get_time();
    pthread_mutex_unlock(&(table->check_meal));
    smart_sleep(table->time_eat, table);
    (philo->x_ate)++;
    pthread_mutex_unlock(&(table->lock_fork[philo->left_fork_id]));
    pthread_mutex_unlock(&(table->lock_fork[philo->right_fork_id]));
}

