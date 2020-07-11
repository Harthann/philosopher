/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 10:45:55 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/11 09:19:12 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void				meal_set(int *meals, int value, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		meals[i] = value;
		i++;
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
	philo->state = 4;
	philo->status = status;
	gettimeofday(&philo->timestamp, &tzp);
	philo->status->last_meal[number - 1] = philo->timestamp;
}

t_status			*init_status(int count, t_philo *list)
{
	t_status *status;

	if (count <= 0)
		return (NULL);
	if ((!(status = malloc(sizeof(t_status)))))
		return (NULL);
	status->philo_count = count;
	list = 0;
	status->simu_state = 0;
	if (!(status->last_meal = malloc(sizeof(struct timeval) * count)))
	{
		free(status);
		return (NULL);
	}
	return (status);
}

t_philo				*init_philosopher(char **av, int ac)
{
	t_philo			*list;
	t_status		*status;
	sem_t			*tm;
	int				i;

	i = 0;
	if (!(list = malloc(sizeof(t_philo) * ft_atoi(av[1]))))
		return (NULL);
	if (!(status = init_status(ft_atoi(av[1]), list)))
		return (NULL);
	status->fork_count = status->philo_count;
	tm = sem_open("/semafork", O_CREAT, 0777, 0);
	if (SEM_FAILED == tm)
		return (NULL);
	while (i < status->philo_count)
	{
		sem_post(tm);
		(list + i)->semafork = tm;
		if (ac == 6)
			(list + i)->count_meal = ft_atoi(av[5]);
		else
			(list + i)->count_meal = -1;
		create_philosopher(list + i, i + 1, av, status);
		i++;
	}
	// sem_close(tm);
	return (list);
}
