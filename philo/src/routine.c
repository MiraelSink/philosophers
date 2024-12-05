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

#include <philo.h>

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

void    sleeping(unsigned int id, t_table *table)
{
    print_task(table, id, "is sleeping");
    smart_sleep(table->time_sleep, table);
}

void    *routine(void *void_routine)
{
    unsigned int    i;
    t_philo         *philo;
    t_table         *table;

    i = 0;
    philo = (t_philo *)void_routine;
    table = philo->table;
    while(!(table->died))
    {
        print_task(table, philo->philo_id, "is thinking");
        eats(philo);
        if (table->all_ate)
            break ;
        sleeping(philo->philo_id, table);
        i++;
    }
    return (NULL);
}

int launch(t_table *table)
{
    unsigned int    i;
    t_philo         *philo;

    i = 0;
    philo = table->philo;
    table->first_timestamp = get_time();
    while (i < table->nb_philo)
    {
        if (pthread_create((philo[i].thread_id), NULL, routine, &(philo[i])))
            return (1);
        philo->last_meal = get_time();
        i++;
    }
    i = -1;
    while (++i < table->nb_philo)
        pthread_join(*(philo[i].thread_id), NULL);
    pthread_mutex_destroy(&(table->printing));
    return (0);
}
