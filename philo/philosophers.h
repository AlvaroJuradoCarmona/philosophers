/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurado- <ajurado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:04:40 by ajurado-          #+#    #+#             */
/*   Updated: 2024/01/27 18:43:44 by ajurado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				numphilo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				total_meals;
	pthread_mutex_t	message_mtx;
	pthread_mutex_t	total_meals_mtx;
	pthread_mutex_t	dead_mtx;
	int				eaten_cont;
	int				philo_dead;
	int				init_time;
	t_philo			*philo;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	meal;
	int				last_meal;
	int				num_meals;
	t_data			*data;
	t_philo			*next;
}	t_philo;

int		init_data(int argc, char **argv, t_data *data);
int		valid_args(int argc, char **argv);
long	ft_atol(char *str);
int		init_data(int argc, char **argv, t_data *data);
void	free_all(t_data *data);
void	*routine(void *philo_data);
int		philo_died(t_data *data);
int		get_time(void);
void	print_status(t_philo *philo, char *str);
int		meals_eaten(t_data *data);
int		check_death(t_philo *philo);
void	ft_sleep(int ms);

#endif
