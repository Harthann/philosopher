/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:19 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/02 12:45:01 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void __attribute__((destructor)) lock();

void		lock(void)
{
	write(2, "Program ended\n", 15);
	read(0, NULL, 1);
}

void		take_a_fork(t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timezone tzp;

	sem_wait(philo->status->semafork);
	if (!is_alive(philo))
		return ;
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " has taken a fork \n");
	if (!is_alive(philo))
		return ;
	sem_wait(philo->status->semafork);
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " has taken a fork \n");
}

int			philosopher_loop(void *philosopher)
{
	t_philo *philo;
	int		ret;

	philo = philosopher;
	if (philo->number % 2)
		ret = philosopher_thinking(philo);
	else
		ret = philosopher_sleeping(philo);
	return(ret);
}

int			child_killer(pid_t *pid_list, int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		kill(pid_list[i], SIGQUIT);
		i++;
	}
	free(pid_list);
	return (0);
}


int			main_simu(t_philo *list, int nb)
{
	int			i;
	pid_t		*pid_list;
	int			status;

	status = 0;
	if (!(pid_list = malloc(sizeof(pid_t) * nb)))
		return (0);
	i = 0;
	while (i < nb)
	{
		if (!(pid_list[i] = fork())) {
			// i = philosopher_loop(list + i);
			printf("addres of status from childs : [%p]\n", list->status);
			// sem_close(list->status->semafork);
			// sem_close(g_semaprint);
			// free(list->status);
			// free(list);
			free(pid_list);
			return (i);
		}
		i++;
	}
	i = 0;
	printf("addres of status from childs : [%p]\n", list->status);
	while(i != nb)
	{
		waitpid(0, &status, 0);
		if (WEXITSTATUS(status) == 255)
			return (child_killer(pid_list, nb));
		i++;
	}
	free(pid_list);
	return (0);
}

int			main(int ac, char **av)
{
	t_philo *list;
	int		ret;

	if (ac != 5 && ac != 6)
		return (1);
	if (!(list = init_philosopher(av, ac)) || check_validity(list))
	{
		ft_free(list);
		write(1, "initialisation failed!\n", 24);
		return (1);
	}
	ret = main_simu(list, ft_atoi(av[1]));
	ft_free(list);
	if (ret == 0 || ret != -1) {
		sem_unlink("/my_semaprint");
		sem_unlink("/my_semafork");
	}
	return (ret);
}
