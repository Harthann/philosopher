/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:19 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/16 08:27:30 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	argument_validity(int ac, char **av)
{
	int	ret;

	ret = 0;
	if (ft_atoi(av[1]) <= 1)
		ret += write(2, "Not enough philosopher to start simulation\n", 44);
	if (ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		ret += write(2, "Times can't be negative or equal to zero\n", 41);
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		ret += write(2,
				"Philosophers can't eat a negative number of meal\n", 49);
	return (ret);
}

void	child_killer(pid_t *pid_list, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		kill(pid_list[i], SIGQUIT);
		i++;
	}
	free(pid_list);
}

int	main_simu(t_philo *list, int nb)
{
	int		i;
	pid_t	*pid_list;
	int		status;

	status = 0;
	pid_list = malloc(sizeof(pid_t) * nb);
	if (!pid_list)
		return (0);
	i = 0;
	while (i < nb)
	{
		pid_list[i] = fork();
		if (!pid_list[i])
			return (philosopher_loop(list + i));
		i++;
	}
	i = 0;
	while (i != nb)
	{
		sem_wait(list->status->finished_meal);
		i++;
	}
	child_killer(pid_list, nb);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*list;

	if (ac != 5 && ac != 6)
		return (0);
	if (argument_validity(ac, av))
		return (0);
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
