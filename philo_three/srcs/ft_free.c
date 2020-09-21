/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 15:31:27 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/11 10:07:32 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_free(t_philo *list)
{
	sem_close(list->semafork);
	sem_unlink("/semafork");
	free(list->status->last_meal);
	free(list->status);
	free(list);
}