/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurado- <ajurado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:04:57 by ajurado-          #+#    #+#             */
/*   Updated: 2024/01/27 18:29:04 by ajurado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_philos_states(t_data *data)
{
	t_philo	*aux;

	aux = data->philo;
	while (!check_death(aux) && !meals_eaten(data))
	{
		if (aux->next)
			aux = aux->next;
		else
			aux = data->philo;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6 && !valid_args(argc, argv))
		return (-1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	memset(data, 0, sizeof(t_data));
	if (!init_data(argc, argv, data))
		return (free_all(data), -1);
	check_philos_states(data);
	while (data->philo)
	{
		pthread_join(data->philo->thread, NULL);
		pthread_mutex_destroy(&data->philo->fork);
		data->philo = data->philo->next;
	}
	if (data->total_meals == 0
		|| (!data->philo_dead && data->eaten_cont == data->numphilo))
		printf("All philos have eaten %d times\n", data->total_meals);
	return (free_all(data), 0);
}
