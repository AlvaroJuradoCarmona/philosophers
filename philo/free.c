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

static void	ft_lstclear_philos(t_philo **philo)
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
	aux = data->philo;
	while (aux)
	{
		if (aux->thread)
			pthread_detach(&aux->thread);
		if (aux->fork)
			pthread_mutex_destroy(&aux->fork);
		aux = aux->next;
	}
	ft_lstclear_philos(&data->philo);
	if (data->philo)
		free(data->philo);
	if (data)
		free(data);
}
