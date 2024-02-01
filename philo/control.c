/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurado- <ajurado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:48:40 by ajurado-          #+#    #+#             */
/*   Updated: 2024/02/01 17:49:49 by ajurado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_checklife(t_table *table, int i_philo)
{
	pthread_mutex_lock(&table->to_check);
	if (ft_dif_time(table->init_time) - table->philo[i_philo].last_eat
		> table->t_die)
	{
		table->dead = 1;
		printf("%lld %d died\n", ft_dif_time(table->init_time),
			table->philo[i_philo].id);
	}
	pthread_mutex_unlock(&table->to_check);
	usleep(300);
}

static int	ft_all_ate(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
	{
		if (table->philo[i].eat_count < table->n_eat)
			return (0);
	}
	return (1);
}

int	check_dead(t_table *table)
{
	int		dead;

	pthread_mutex_lock(&table->to_check);
	dead = table->dead;
	pthread_mutex_unlock(&table->to_check);
	return (dead);
}

void	*ft_is_dead(void *table)
{
	int		i;
	t_table	*aux;

	aux = table;
	usleep(25);
	while (!check_dead(aux))
	{
		i = -1;
		while (++i < aux->n_philo && !check_dead(aux))
			ft_checklife(aux, i);
		if (!check_dead(aux) && aux->n_eat > 0 && ft_all_ate(aux) == 1)
		{
			pthread_mutex_lock(&aux->to_check);
			aux->dead = 1;
			pthread_mutex_unlock(&aux->to_check);
			printf("All philos ate %d times \n", aux->n_eat);
			break ;
		}
	}
	usleep(300);
	return (0);
}
