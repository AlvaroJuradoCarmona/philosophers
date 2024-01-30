/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurado- <ajurado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:34:23 by ajurado-          #+#    #+#             */
/*   Updated: 2024/01/27 18:27:45 by ajurado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*p;

	if (!*lst)
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}

static int	initialize_philo(t_data *data)
{
	int			i;
	t_philo		*aux;

	i = -1;
	data->init_time = get_time();
	while (++i < data->numphilo)
	{
		aux = malloc(sizeof(t_philo));
		if (!aux)
			return (0);
		memset(aux, 0, sizeof(t_philo));
		aux->id = i + 1;
		aux->data = data;
		aux->next = NULL;
		if (pthread_mutex_init(&aux->fork, NULL)
			|| pthread_create(&aux->thread, NULL, &routine, aux))
			return (0);
		ft_lstadd_back(&data->philos, aux);
	}
	return (1);
}

static void	initialize_data(t_data *data, int num, int param)
{
	if (param == 1)
		data->numphilo = num;
	else if (param == 2)
		data->time_die = num;
	else if (param == 3)
		data->time_eat = num;
	else if (param == 4)
		data->time_sleep = num;
	else if (param == 5)
		data->total_meals = num;
}

int	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	data->total_meals = -1;
	while (++i < argc)
		initialize_data(data, (int) atol(argv[i]), i);
	return (pthread_mutex_init(&data->message_mtx, NULL)
		|| pthread_mutex_init(&data->total_meals_mtx, NULL)
		|| pthread_mutex_init(&data->dead_mtx, NULL)
		|| !initialize_philo(data));
}
