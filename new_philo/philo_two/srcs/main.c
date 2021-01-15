/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:19 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/15 13:20:27 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

// int	take_a_fork(t_philo *philo)
// {
// 	long			time;
// 	struct timeval	start_t;
// 	struct timezone	tzp;

// 	sem_wait(philo->status->semafork);
// 	if (philo->status->simu_state == -1)
// 		return (1);
// 	gettimeofday(&start_t, &tzp);
// 	time = compare_time(start_t, philo->timestamp);
// 	print_state(time, philo->number, " has taken a fork \n");
// 	sem_wait(philo->status->semafork);
// 	if (philo->status->simu_state == -1)
// 		return (1);
// 	gettimeofday(&start_t, &tzp);
// 	time = compare_time(start_t, philo->timestamp);
// 	print_state(time, philo->number, " has taken a fork \n");
// 	return (0);
// }


int	main_simu(t_philo *list, int nb)
{
	pthread_t	*thread_list;
	int			i;

	thread_list = malloc(sizeof(pthread_t) * (2 * nb));
	if (!thread_list)
		return (0);
	i = 0;
	while (i < nb)
	{
		// pthread_create(&thread_list[i], NULL,
		// 				philosopher_nurse, (void*)(list + i));
		pthread_create(&thread_list[i], NULL,
						philosopher_loop, (void*)(list + i));
		i++;
	}
	list->status->started = 1;
	while (list->status->simu_state != -1 && list->status->simu_state != nb)
		;
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
