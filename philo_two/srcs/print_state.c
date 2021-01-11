/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:36 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/11 10:25:27 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_strcpy(char *dest, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
}

void	add_numb(char *str, long nb)
{
	int		i;
	long	tmp;

	tmp = nb;
	i = 0;
	while (tmp > 9)
	{
		tmp /= 10;
		i++;
	}
	while (i)
	{
		str[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	str[i] = nb % 10 + '0';
}

void	print_state(long timestamp, int number, char *str)
{
	char	to_print[4080];

	sem_wait(g_semaprint);
	memset(to_print, 0, 4080);
	add_numb(to_print, timestamp);
	to_print[ft_strlen(to_print)] = ' ';
	add_numb(to_print + ft_strlen(to_print), number);
	ft_strcpy(to_print + ft_strlen(to_print), str);
	write(1, to_print, ft_strlen(to_print));
	sem_post(g_semaprint);
}
