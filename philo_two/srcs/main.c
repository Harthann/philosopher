/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:19 by nieyraud          #+#    #+#             */
/*   Updated: 2020/09/30 11:49:10 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		take_a_fork(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timezone tzp;

	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	sem_wait(philo->semafork);
	if (!is_alive(philo))
		return ;
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " has taken a fork \n");
	if (!is_alive(philo))
		return ;
	sem_wait(philo->semafork);
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " has taken a fork \n");
}

void		*philosopher_loop(void *philosopher)
{
	t_philo *philo;

	philo = philosopher;
	philo->semafork = sem_open("semafork", O_WRONLY);//, O_CREAT, 0644, philo->status->philo_count);
	if (philo->number % 2)
		philosopher_thinking(philo);
	else
		philosopher_sleeping(philo);
	if (!philo->count_meal)
		philo->status->simu_state += 1;
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
	while (list->status->simu_state != -1 && list->status->simu_state != nb)
		;
	free(thread_list);
	return (0);
}

int			main(int ac, char **av)
{
	t_philo *list;

	if (ac != 5 && ac != 6)
		return (1);
	if (!(list = init_philosopher(av, ac)) || check_validity(list))
	{
		write(1, "initialisation failed!\n", 24);
		return (1);
	}
	main_simu(list, ft_atoi(av[1]));
	ft_free(list);
	while (1)
		;
	return (0);
}
