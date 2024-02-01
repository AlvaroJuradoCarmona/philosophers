/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurado- <ajurado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:08:03 by ajurado-          #+#    #+#             */
/*   Updated: 2024/02/01 17:53:05 by ajurado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	to_wait(t_table *table, int time)
{
	int	wait_init;

	wait_init = ft_dif_time(table->init_time);
	while (ft_dif_time(table->init_time) - wait_init < time)
		usleep(10);
}

static void	ft_eating(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->forks[philo->right_f]);
	message(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&table->forks[philo->left_f]);
	message(table, philo->id, "has taken a fork");
	if (!check_dead(table))
	{
		pthread_mutex_lock(&table->to_check);
		philo->last_eat = ft_dif_time(table->init_time);
		philo->eat_count++;
		pthread_mutex_unlock(&table->to_check);
		message(table, philo->id, "is eating");
		to_wait(table, table->t_eat);
	}
	pthread_mutex_unlock(&table->forks[philo->right_f]);
	pthread_mutex_unlock(&table->forks[philo->left_f]);
}

void	*ft_to_eat(void *philo)
{
	t_table	*table;
	t_philo	*aux;

	aux = philo;
	table = aux->table;
	usleep(25);
	aux->right_f = aux->id - 1;
	if (aux->id == table->n_philo)
		aux->left_f = 0;
	else
		aux->left_f = aux->id;
	if (aux->id % 2 != 0)
		usleep(250);
	while (!check_dead(table))
	{
		ft_eating(aux, table);
		if (!check_dead(table))
		{
			message(table, aux->id, "is sleeping");
			usleep(table->t_sleep * 1000);
		}
		if (!check_dead(table))
			message(table, aux->id, "is thinking");
	}
	return (0);
}
