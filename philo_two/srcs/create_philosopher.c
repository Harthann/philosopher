/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 10:45:55 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/09 09:42:49 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

t_status			*init_status(int count, t_philo *list, int ac, char *str)
{
	t_status *status;

	if ((!(status = malloc(sizeof(t_status)))))
		return (NULL);
	status->philo_count = count;
	list = 0;
	status->simu_state = 0;
	if (!(status->count_meal = malloc(sizeof(int) * count)))
		return (NULL);
	if (ac == 6)
		meal_set(status->count_meal, ft_atoi(str), sizeof(int));
	else
		meal_set(status->count_meal, -1, count);
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
	if (!(status = init_status(ft_atoi(av[1]), list, ac, av[5])))
		return (NULL);
	status->fork_count = status->philo_count;
	tm = sem_open("/semafork", O_CREAT, 0644, status->fork_count);
	if (SEM_FAILED == tm)
		return (NULL);
	while (i < status->philo_count)
	{
		create_philosopher(list + i, i + 1, av, status);
		i++;
	}
	sem_close(tm);
	return (list);
}
