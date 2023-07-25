/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romartin <romartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 10:37:28 by robin             #+#    #+#             */
/*   Updated: 2023/07/24 19:57:53 by romartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	long long int	last_meal;
	int				left_fork;
	int				right_fork;
	int				nb_meal;
	struct s_list	*list;
	pthread_t		ph;
}	t_philo;

typedef struct s_list
{
	int					nb_philo;
	int					time_to_sleep;
	int					time_to_eat;
	int					time_to_die;
	int					nb_of_meal;
	int					all_eat;
	int					died;
	int					meal;
	long long			start;
	long long			time;
	t_philo				philo[250];
	pthread_mutex_t		fork[250];
	pthread_mutex_t		writing;
	pthread_mutex_t		die;
	pthread_mutex_t		check_meal;
	pthread_mutex_t		m_time;
	pthread_t			thread_time;
}	t_list;

int			ft_atoi(const char *str);
void		init_mutex(t_list *list);
int			full_digit(char **argv, int len);
void		is_dead(t_list *list, t_philo *philo);
void		*philo_life(void *void_philo);
void		time_to_sleep(t_philo *phil);
void		check_die(t_list *list);
void		ft_print(t_philo *philo, char *str);
void		*timestamp(void *param);
long long	get_time(t_list *list);
void		ft_break(t_list *list);
void		ft_time_to_eat(long long time, t_list *list);
void		atribution_four(t_list *list, char **av);
void		atribution_five(t_list *list, char **av);
void		init_philo(t_list *list);
void		create_thread(t_list *list);
#endif