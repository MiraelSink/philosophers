/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:15:14 by maandria          #+#    #+#             */
/*   Updated: 2024/12/28 18:38:10 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	unsigned int	philo_id;
	int				x_ate;
	int				is_full;
	unsigned int	left_fork_id;
	unsigned int	right_fork_id;
	long long		last_meal;
	pthread_t		thread_id;
	t_table			*table;
}	t_philo;

struct s_table
{
	int					nb_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					nb_each_eat;
	int					died;
	unsigned int		all_ate;
	unsigned int		*state_forks;
	unsigned long int	first_timestamp;
	pthread_mutex_t		*lock_fork;
	pthread_mutex_t		check_meal;
	pthread_mutex_t		printing;
	t_philo				*philo;
};

int					ph_atoi(char *str);
long int			get_time(void);
long int			time_diff(long int past, long int present);
void				free_value(t_table *table);
void				sleeping(unsigned int id, t_table *table);
void				eats_odd(t_table *table, t_philo *philo);
void				eats_even(t_table *table, t_philo *philo);
void				take_time_value(t_table *table, char **av);
void				smart_sleep(long int time, t_table *table);
void				print_task(t_table *table, unsigned int id, char *str);
int					init_all(int ac, char **av, t_table *table);
int					init_value(int ac, char **av, t_table *table);
int					init_philosophers(t_table *table);
int					check_die(t_table *table);
int					launch(t_table *table);
int					w_philo(int code);

#endif
