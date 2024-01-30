/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurado- <ajurado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:08:03 by ajurado-          #+#    #+#             */
/*   Updated: 2024/01/27 18:36:11 by ajurado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_died(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->dead_mtx);
	if (data->philo_dead)
		res = 1;
	return (pthread_mutex_unlock(&data->dead_mtx), res);
}

static void	check_if_total_meals_eaten(t_philo *philo, t_data *data)
{
	if (philo->num_meals == data->total_meals)
	{
		pthread_mutex_lock(&data->total_meals_mtx);
		data->meals_eaten++;
		pthread_mutex_unlock(&data->total_meals_mtx);
	}
}

static void	philo_routine(t_data *data, t_philo *philo, pthread_mutex_t *f1,
			pthread_mutex_t *f2)
{
	while (!meals_eaten(data) && !philo_died(data))
	{
		pthread_mutex_lock(f1);
		print_status(philo, "has taken a fork");
		if (f1 == f2)
		{
			pthread_mutex_unlock(f1);
			break ;
		}
		pthread_mutex_lock(f2);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		philo->last_meal = get_time();
		ft_sleep(data->time_eat);
		philo->num_meals++;
		check_if_total_meals_eaten(philo, data);
		pthread_mutex_unlock(f1);
		pthread_mutex_unlock(f2);
		print_status(philo, "is sleeping");
		ft_sleep(data->time_sleep);
		print_status(philo, "is thinking");
	}
}

void	*routine(void *philo_data)
{
	t_philo	*philo;
	t_data	*data;
	t_philo	*next_philo;

	philo = (t_philo *) philo_data;
	data = philo->data;
	if (!philo->next)
		next_philo = data->philo;
	else
		next_philo = philo->next;
	if (philo->id % 2)
	{
		ft_sleep(5);
		philo->last_meal = get_time();
		philo_routine(data, philo, &philo->fork, &next_philo->fork);
	}
	else
	{
		philo->last_meal = get_time();
		philo_routine(data, philo, &next_philo->fork, &philo->fork);
	}
	return (NULL);
}