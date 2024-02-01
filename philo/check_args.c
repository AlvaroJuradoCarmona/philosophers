/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurado- <ajurado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:04:49 by ajurado-          #+#    #+#             */
/*   Updated: 2024/02/01 17:53:05 by ajurado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || sign == -1)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (num > INT_MAX)
		return (-1);
	return (sign * num);
}

long long	ft_get_time(void)
{
	struct timeval	time;
	long long		now;

	gettimeofday(&time, NULL);
	now = (long long)time.tv_sec * 1000 + time.tv_usec / 1000;
	return (now);
}

long long	ft_dif_time(long long time)
{
	return (ft_get_time() - time);
}

void	message(t_table *table, int id, char *str)
{
	printf("%lld %d %s\n", ft_dif_time(table->init_time), id, str);
}
