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
    // if (philo->philo_id % 2 == 0)
    // {
        if (!pthread_mutex_lock(&(table->lock_fork[philo->left_fork_id - 1])))
        {
            pthread_mutex_lock(&(table->lock_fork[philo->right_fork_id - 1]));
            print_task(table, philo->philo_id, "has taken a fork");
            print_task(table, philo->philo_id, "has taken a fork");
        }
    // }
    // else
    // {
    //     if (!pthread_mutex_lock(&(table->lock_fork[philo->right_fork_id - 1])))
    //     {
    //         pthread_mutex_lock(&(table->lock_fork[philo->left_fork_id - 1]));
    //         print_task(table, philo->philo_id, "has taken a fork");
    //         print_task(table, philo->philo_id, "has taken a fork");
    //     }
    // }
    pthread_mutex_lock(&(table->check_meal));
    print_task(table, philo->philo_id, "is eating");
    philo->last_meal = get_time();
    pthread_mutex_unlock(&(table->check_meal));
    smart_sleep(table->time_eat, table);
    (philo->x_ate)++;
    pthread_mutex_unlock(&(table->lock_fork[philo->left_fork_id - 1]));
    pthread_mutex_unlock(&(table->lock_fork[philo->right_fork_id - 1]));
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
    if (philo->philo_id % 2 == 0)
        usleep(1000);
    while(!(table->died))
    {
        eats(philo);
        if (table->all_ate)
            break ;
        sleeping(philo->philo_id, table);
        print_task(table, philo->philo_id, "is thinking");
        // usleep(500);
        smart_sleep(((table->time_die) - (table->time_sleep + table->time_eat + 10)), table);
        i++;
    }
    return (NULL);
}

void    monitor(t_table *t, t_philo *p)
{
    int i;

    while (!(t->all_ate))
    {
        i = -1;
        while(++i < t->nb_philo && !(t->died))
        {
            pthread_mutex_lock(&(t->check_meal));
            // if (time_diff(p[i].last_meal, get_time()) > (t->time_die + 50))
            // {
            //     print_task(t, i, "died");
            //     t->died = 1;
            // }
            pthread_mutex_unlock(&(t->check_meal));
            usleep(10);
        }
        if (t->died)
            break ;
        i = 0;
        while ((t->nb_each_eat != -1) && (i < t->nb_philo) && (p[i].x_ate >= t->nb_each_eat))
            i++;
        if (i == t->nb_philo)
            t->all_ate = 1;
    }
}

int launch(t_table *table)
{
    int    i;
    t_philo         *philo;

    i = 0;
    philo = table->philo;
    table->first_timestamp = get_time();
    while (i < table->nb_philo)
    {
        if (pthread_create(&(philo[i].thread_id), NULL, routine, &(philo[i])))
            return (1);
        pthread_mutex_lock(&(table->check_meal));
        philo->last_meal = get_time();
        pthread_mutex_unlock(&(table->check_meal));
        i++;
    }
    monitor(table, philo);
    i = -1;
    while (++i < table->nb_philo)
        pthread_join((philo[i].thread_id), NULL);
    pthread_mutex_destroy(&(table->printing));
    return (0);
}
