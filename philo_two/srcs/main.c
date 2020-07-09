/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:19 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/09 10:21:17 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		take_a_fork(t_philo *philo)
{
	while (is_alive(philo) && !philo->status->simu_state
			&& philo->status->fork_count < 2)
		usleep(50);
	if (is_alive(philo) && !philo->status->simu_state)
		fork_dec(philo->semafork, &philo->status->fork_count, philo);
	while (is_alive(philo) && !philo->status->simu_state
			&& philo->status->fork_count < 1)
		usleep(50);
	if (is_alive(philo) && !philo->status->simu_state)
		fork_dec(philo->semafork, &philo->status->fork_count, philo);
	else
		fork_inc(philo->semafork, &philo->status->fork_count);
}

void		*philosopher_loop(void *philosopher)
{
	t_philo *philo;

	philo = philosopher;
	if (SEM_FAILED == (philo->semafork = sem_open("/semafork", 0)))
		return ((void*)-1);
	while (philo->state != 3 && !philo->status->simu_state)
	{
		if (philo->state == 2 || philo->state == 4)
			philosopher_thinking(philo);
		else if (philo->state == 0)
			philosopher_eating(philo);
		else if (philo->state == 1)
		{
			fork_inc(philo->semafork, &philo->status->fork_count);
			fork_inc(philo->semafork, &philo->status->fork_count);
			philosopher_sleeping(philo);
		}
	}
	sem_close(philo->semafork);
	return (NULL);
}

int			main_simu(t_philo *list, int nb)
{
	pthread_t	*thread_list;
	int			i;

	if (!(thread_list = malloc(sizeof(pthread_t) * nb)))
		return (0);
	i = 0;
	while (i < nb)
	{
		pthread_create(&thread_list[i], NULL,
						philosopher_loop, (void*)(list + i));
		i++;
	}
	while (i >= 0)
	{
		pthread_join(thread_list[i], NULL);
		i--;
	}
	free(thread_list);
	return (0);
}

int			main(int ac, char **av)
{
	t_philo *list;

	if (ac != 5 && ac != 6)
		return (1);
	if (!(list = init_philosopher(av, ac)))
	{
		write(1, "initialisation failed!\n", 24);
		return (1);
	}
	main_simu(list, ft_atoi(av[1]));
	ft_free(list);
	return (0);
}
