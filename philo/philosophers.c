/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurado- <ajurado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:04:57 by ajurado-          #+#    #+#             */
/*   Updated: 2024/02/01 17:49:49 by ajurado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_insert_init_data(t_table *table, char **argv, int i)
{
	int	num;

	num = ft_atoi(argv[i]);
	if (num < 0)
		return (0);
	if (i == 1)
	{
		if (num == 0)
			return (0);
		table->n_philo = num;
	}
	else if (i == 2)
		table->t_die = num;
	else if (i == 3)
		table->t_eat = num;
	else if (i == 4)
		table->t_sleep = num;
	else if (i == 5)
		table->n_eat = num;
	return (1);
}

static int	ft_init_data(t_table *table, char **argv)
{
	int	i;

	i = 0;
	table->n_eat = -1;
	while (argv[++i] != 0)
		if (ft_insert_init_data(table, argv, i) == 0)
			return (0);
	return (1);
}

static int	ft_create_philos(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philo)
		return (0);
	i = -1;
	while (++i < table->n_philo)
	{
		table->philo[i].to_check = &table->to_check;
		pthread_mutex_lock(&table->to_check);
		table->philo[i].table = table;
		table->philo[i].id = i + 1;
		table->philo[i].last_eat = 0;
		table->philo[i].eat_count = 0;
		pthread_mutex_unlock(&table->to_check);
		if (pthread_create(&table->philo[i].soul, NULL,
				ft_to_eat, &table->philo[i]) != 0)
			return (0);
	}
	return (1);
}

static int	ft_create_fork(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks)
		return (0);
	i = -1;
	while (++i < table->n_philo)
	{
		if (pthread_mutex_init(&table->forks[i], 0))
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	i = -1;
	if (argc != 5 && argc != 6)
		return (-1);
	table.dead = 0;
	if (ft_init_data(&table, argv) == 0)
		return (-1);
	table.init_time = ft_get_time();
	if (pthread_mutex_init(&table.to_check, 0) != 0)
		return (-1);
	if (ft_create_fork(&table) == 0)
		return (-1);
	if (pthread_create(&table.checker, 0, ft_is_dead, &table) != 0)
		return (-1);
	if (ft_create_philos(&table) == 0)
		return (-1);
	pthread_join(table.checker, NULL);
	ft_free_all(&table);
	return (0);
}
