/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 08:53:03 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/09 10:18:30 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	fork_dec(sem_t *semafork, int *fork_count, t_philo *philo)
{
	long			time;
	struct timeval	start_t;
	struct timezone tzp;

	*fork_count -= 1;
	sem_wait(semafork);
	gettimeofday(&start_t, &tzp);
	time = compare_time(start_t, philo->timestamp);
	print_state(time, philo->number, " has taken a fork \n");
}

void	fork_inc(sem_t *semafork, int *fork_count)
{
	sem_post(semafork);
	*fork_count += 1;
}
