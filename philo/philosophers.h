/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurado- <ajurado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:04:40 by ajurado-          #+#    #+#             */
/*   Updated: 2024/02/02 12:43:57 by ajurado-         ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				l_fork;
	int				r_fork;
	int				last_eat;
	int				eat_count;
	void			*table;
	pthread_t		thread;
	pthread_mutex_t	*checker_mtx;
}	t_philo;

typedef struct s_table
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	long long		init_time;
	int				dead;
	pthread_mutex_t	checker_mtx;
	pthread_mutex_t	*forks;
	pthread_t		checker;
	t_philo			*philo;
}	t_table;

void		ft_free_all(t_table *table);
int			ft_atoi(const char *str);
long long	ft_get_time(void);
long long	ft_dif_time(long long now);
void		message(t_table *table, int id, char *str);
void		*ft_is_dead(void *table);
int			check_dead(t_table *table);
void		*ft_to_eat(void *philo);

#endif
