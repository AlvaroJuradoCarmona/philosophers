/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurado- <ajurado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:53:55 by ajurado-          #+#    #+#             */
/*   Updated: 2024/01/27 18:27:45 by ajurado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lstclear_philos(t_philo **philo)
{
	t_philo	*next;

	while (*philo)
	{
		next = (*philo)->next;
		free(philo);
		*philo = next;
	}
}

void	free_all(t_data *data)
{
	t_philo	*tmp;

	if (data->message_mtx)
		pthread_mutex_destroy(&data->message_mtx);
	if (data->total_meals_mtx)
		pthread_mutex_destroy(&data->total_meals_mtx);
	if (data->dead_mtx)
		pthread_mutex_destroy(&data->dead_mtx);
	tmp = data->philos;
	while (tmp)
	{
		if (tmp->thread)
			pthread_detach(tmp->thread);
		if (tmp->fork)
			pthread_mutex_destroy(tmp->fork);
		tmp = tmp->next;
	}
	ft_lstclear_philos(&data->philos);
	if (data->philos)
		free(data->philos);
	if (data)
		free(data);
}
