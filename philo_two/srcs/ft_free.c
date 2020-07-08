/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 15:31:27 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/08 11:46:29 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_free(t_philo *list)
{
	free(list->status->count_meal);
	free(list->status->last_meal);
	free(list->status);
	free(list);
}
