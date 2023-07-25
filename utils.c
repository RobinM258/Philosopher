/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romartin <romartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:46:42 by romartin          #+#    #+#             */
/*   Updated: 2023/07/25 14:45:43 by romartin         ###   ########.fr       */
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

int	check_death(t_list *list)
{
	pthread_mutex_lock(&(list->die));
	if (list->died)
	{
		pthread_mutex_unlock(&(list->die));
		return (1);
	}
	pthread_mutex_unlock(&(list->die));
	return (0);
}

void	*timestamp(void *param)
{
	t_list			*list;
	struct timeval	t;

	list = (t_list *)param;
	while (1)
	{
		gettimeofday(&t, NULL);
		pthread_mutex_lock(&(list->m_time));
		list->time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
		pthread_mutex_unlock(&(list->m_time));
		usleep(500);
	}
	return (NULL);
}

long long	get_time(t_list *list)
{
	long long	ret;

	pthread_mutex_lock(&(list->m_time));
	ret = list->time;
	pthread_mutex_unlock(&(list->m_time));
	return (ret);
}

void	ft_time_to_eat(long long time, t_list *list)
{
	long long	past;

	past = get_time(list);
	while (get_time(list) - past < time)
		usleep(500);
}
