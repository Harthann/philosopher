/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 15:31:27 by nieyraud          #+#    #+#             */
/*   Updated: 2020/09/30 11:47:00 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_free(t_philo *list)
{
	free(list->status);
	sem_unlink("semaprint");
	sem_unlink("semafork");
	free(list);
}
