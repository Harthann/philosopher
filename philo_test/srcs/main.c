/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:19 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/13 13:46:03 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	take_a_fork(t_philo *philo)
{
	// struct timeval	start_t;

	pthread_mutex_lock(philo->mutex_left); // fork mutex

	// pthread_mutex_unlock(&philo->action); // unlock/lock to activate death check
	// pthread_mutex_lock(&philo->action);
	print_state(philo->timestamp, philo->number, " has taken a fork \n");

	pthread_mutex_lock(philo->mutex_right);

	// pthread_mutex_unlock(&philo->action);
	// pthread_mutex_lock(&philo->action);
	print_state(philo->timestamp, philo->number, " has taken a fork \n");
	return (0);
}

void	*philosopher_nurse(void *philosopher)
{
	t_philo			*philo;
	long			time;
	struct timeval	start_t;

	philo = (t_philo*)philosopher;
	// wait_start(*philo);
	while (1)
	{
		pthread_mutex_lock(&philo->action);
		gettimeofday(&start_t, NULL);
		// print_state(philo->last_meal, philo->number, " NURSE ENTERED LIFE CHECKING\n");

		time = compare_time(start_t, philo->last_meal);
		if (time > philo->ttd)
		{
			print_state(philo->timestamp, philo->number, " died\n");
			pthread_mutex_lock(g_printing);
			philo->status->simu_state = -1;
			break ;
		}
		pthread_mutex_unlock(&philo->action);
		usleep(philo->ttd);
	}
	return (0);
}

int	main_simu(t_philo *list, int nb)
{
	pthread_t	*thread_list;
	int			i;

	thread_list = malloc(sizeof(pthread_t) * (2 * nb));
	if (!thread_list)
		return (0);
	i = 0;
	pthread_mutex_lock(&g_start);
	while (i < nb)
	{
		pthread_create(&thread_list[i], NULL,
						philosopher_nurse, (void*)(list + i));
		pthread_create(&thread_list[i + nb], NULL,
						philosopher_loop, (void*)(list + i));
		i++;
	}
	pthread_mutex_unlock(&g_start);
	usleep(1000);
	list->status->started = 1;
	while (list->status->simu_state != -1 && list->status->simu_state != nb)
		;
	printf("Leaving loop\n");
	free(thread_list);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*list;

	if (ac != 5 && ac != 6)
		return (1);
	list = init_philosopher(av, ac);
	if (!list || check_validity(list))
	{
		write(1, "initialisation failed!\n", 24);
		return (1);
	}
	main_simu(list, ft_atoi(av[1]));
	ft_free(list);
	return (0);
}
