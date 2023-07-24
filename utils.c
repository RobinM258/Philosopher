/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romartin <romartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:46:42 by romartin          #+#    #+#             */
/*   Updated: 2023/07/24 18:12:28 by romartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_break(t_list *list)
{
	int	i;

	i = 0;
	while (++i < list->nb_philo)
		pthread_mutex_destroy(&list->fork[i]);
	pthread_mutex_unlock(&(list->writing));
	pthread_mutex_destroy(&(list->writing));
	pthread_mutex_destroy(&list->check_meal);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_time_to_eat(long long time)
{
	long long	past;

	past = timestamp();
	while (1)
	{
		if (timestamp() - past >= time)
			break ;
		usleep(time / 10);
	}
}

void	ft_print(t_philo *philo, char *str)
{
	if (philo->list->died != 1)
		printf("%lli %d %s", (timestamp()
				- philo->list->start), philo->id, str);
}
