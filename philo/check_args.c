/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurado- <ajurado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:04:49 by ajurado-          #+#    #+#             */
/*   Updated: 2024/01/27 16:56:59 by ajurado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(char *str)
{
	long	num;
	int		i;
	int		sign;

	num = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i])
		return (-1);
	return (num * sign);
}

static int	is_valid_arg(char *str, int param)
{
	long	num;
	int		valid;

	num = ft_atol(str);
	if (param == 1)
		valid = num > 0;
	valid = num >= 0;
	return (valid && num <= INT_MAX);
}

int	valid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (argc > i++)
	{
		if (!is_valid_arg(argv[i], i))
			return (0);
	}
	return (1);
}
