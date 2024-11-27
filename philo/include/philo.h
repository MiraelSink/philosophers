/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:15:14 by maandria          #+#    #+#             */
/*   Updated: 2024/11/25 23:03:32 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_table t_table;

typedef struct	s_philo
{
	unsigned int	philo_id;
	unsigned int	x_ate;
	unsigned int 	left_fork_id;
	unsigned int	right_fork_id;
	long long		last_meal;
	pthread_t		*thread_id;
	t_table			*table;
}	t_philo;

struct s_table
{
	unsigned int		nb_philo;
	unsigned int		time_die;
	unsigned int		time_eat;
	unsigned int		time_sleep;
	unsigned int		nb_each_eat;
	unsigned int		died;
	unsigned int		all_ate;
	unsigned int 		*fork;
	unsigned long int 	first_timestamp;
	pthread_mutex_t 	*lock_fork;
	pthread_mutex_t 	check_meal;
	pthread_mutex_t		printing;
	t_philo				*philo;
};

unsigned int		ph_atoi(char *str);
unsigned long int	get_time(void);
unsigned long int	time_diff(unsigned long int past, unsigned long int present);
void				free_value(t_table *table);
void				smart_sleep(unsigned long int time, t_table *table);
void				print_task(t_table *table, unsigned int id, char *str);
int					init_all(char **av, t_table *table);
int					init_value(char **av, t_table *table);
int 				init_philosophers(t_table *table);

#endif
