/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romartin <romartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:43:26 by romartin          #+#    #+#             */
/*   Updated: 2023/07/24 16:53:54 by romartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

int	full_digit(char **argv, int len)
{
	int	i;
	int	a;

	i = 1;
	a = 0;
	while (i <= len)
	{
		a = 0;
		while (argv[i][a])
		{
			if ((argv[i][a] < '0' || argv[i][a] > '9'))
				return (1);
			a++;
		}
		i++;
	}
	return (0);
}

static int	ft_white(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r'))
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				sign;
	int				ret;

	ret = 0;
	sign = 1;
	i = ft_white(str);
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		ret = ret * 10 + (str[i] - 48);
		i++;
	}
	return (ret * sign);
}
