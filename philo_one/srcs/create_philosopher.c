/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 10:45:55 by nieyraud          #+#    #+#             */
/*   Updated: 2020/09/30 10:22:28 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void				set_forks(t_philo *philo,
							pthread_mutex_t *mutex_table, int i)
{
	if (mutex_table && philo)
	{
		philo->mutex_right = mutex_table + i;
		philo->mutex_left = mutex_table;
		philo->mutex_left += i + 1 == philo->status->philo_count ? 0 : i + 1;
	}
}

void				create_philosopher(t_philo *philo, int number,
										char **av, t_status *status)
{
	struct timezone tzp;

	philo->ttd = ft_atoi(av[2]);
	philo->tte = ft_atoi(av[3]);
	philo->tts = ft_atoi(av[4]);
	philo->number = number;
	philo->state = number % 2 ? 2 : 4;
	philo->status = status;
	gettimeofday(&philo->timestamp, &tzp);
	philo->last_meal = philo->timestamp;
}

pthread_mutex_t		*init_mutex_table(int length)
{
	pthread_mutex_t	*mutex_table;
	int				i;

	if (!(mutex_table = malloc(sizeof(pthread_mutex_t) * length)))
		return (NULL);
	i = 0;
	while (i < length)
	{
		if (pthread_mutex_init(mutex_table + i, NULL))
			return (NULL);
		i++;
	}
	return (mutex_table);
}

t_status			*init_status(int count)
{
	t_status *status;

	if (count <= 0)
		return (NULL);
	if ((!(status = malloc(sizeof(t_status)))))
		return (NULL);
	status->philo_count = count;
	status->simu_state = 0;
	return (status);
}

t_philo				*init_philosopher(char **av, int ac)
{
	t_philo			*list;
	t_status		*status;
	pthread_mutex_t	*mutex_table;
	int				i;

	i = 0;
	mutex_table = init_mutex_table(ft_atoi(av[1]));
	list = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	status = init_status(ft_atoi(av[1]));
	if (!(g_printing = malloc(sizeof(pthread_mutex_t))))
		return (NULL);
	pthread_mutex_init(g_printing, NULL);
	while (list && i < status->philo_count)
	{
		if (ac == 6)
			(list + i)->count_meal = ft_atoi(av[5]) >= 0 ? ft_atoi(av[5]) : -2;
		else
			(list + i)->count_meal = -1;
		create_philosopher(list + i, i + 1, av, status);
		set_forks(list + i, mutex_table, i);
		i++;
	}
	return (list);
}
