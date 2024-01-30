/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurado- <ajurado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:48:40 by ajurado-          #+#    #+#             */
/*   Updated: 2024/01/27 17:52:43 by ajurado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_status(t_philo *philo, char *str)
{
	if (meals_eaten(philo->data) || philo_died(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->message_mtx);
	printf("%d	%d %s\n", get_time() - philo->data->init_time,
		philo->id, str);
	pthread_mutex_unlock(&philo->data->message_mtx);
}

int	meals_eaten(t_data *data)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->total_meals_mtx);
	if (data->total_meals == 0 && data->eaten_cont == data->numphilo)
		res = 1;
	return (pthread_mutex_unlock(&data->total_meals_mtx), res);
}

int	check_death(t_philo *philo)
{
	if (philo->last_meal + philo->data->time_die < get_time())
	{
		print_status(philo, "died");
		pthread_mutex_lock(&philo->data->dead_mtx);
		philo->data->philo_dead = 1;
		pthread_mutex_unlock(&philo->data->dead_mtx);
		return (1);
	}
	return (0);
}

void	ft_sleep(int ms)
{
	int	initial;

	initial = get_time();
	while (get_time() - initial < ms)
		usleep(50);
}